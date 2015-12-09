#ifndef __RANK_FILTER__
#define __RANK_FILTER__


#include <deque>
#include <cassert>
#include <functional>
#include <iostream>

#include <boost/container/set.hpp>
#include <boost/container/node_allocator.hpp>

#include <vigra/multi_array.hxx>


namespace rank_filter
{

template<class I1,
         class I2>
inline void lineRankOrderFilter1D(const I1& src_begin, const I1& src_end,
        I2& dest_begin, I2& dest_end,
        size_t half_length, double rank)
{
    // Types in use.
    using T1 = typename std::iterator_traits<I1>::value_type;
    using T2 = typename std::iterator_traits<I2>::value_type;

    // Will ignore boundaries initially.
    // Then will try adding reflection.

    // Rank must be in the range 0 to 1
    assert((0 <= rank) && (rank <= 1));

    const size_t rank_pos = round(rank * (2 * half_length));

    // The position of the
    size_t window_begin = 0;

    // Lengths.
    const typename std::iterator_traits<I1>::difference_type src_size = src_end - src_begin;
    const typename std::iterator_traits<I2>::difference_type dest_size = dest_end - dest_begin;

    typedef boost::container::multiset< T1,
            std::less<T1>,
            boost::container::node_allocator<T1>,
            boost::container::tree_assoc_options< boost::container::tree_type<boost::container::scapegoat_tree> >::type> multiset;

    typedef std::deque< typename multiset::iterator > deque;

    multiset sorted_window;
    deque window_iters;

    // Get the initial sorted window.
    // Include the reflection.
    for (size_t j = half_length; j > 0; j--)
    {
        window_iters.push_back(sorted_window.insert(src_begin[window_begin + j]));
    }
    for (size_t j = 0; j <= half_length; j++)
    {
        window_iters.push_back(sorted_window.insert(src_begin[window_begin + j]));
    }

    typename multiset::iterator rank_point = sorted_window.begin();

    for (size_t i = 0; i < rank_pos; i++)
    {
        rank_point++;
    }

    typename multiset::iterator prev_iter;
    T1 prev_value;
    T1 next_value;
    while ( window_begin < src_size )
    {
        dest_begin[window_begin] = *rank_point;

        prev_iter = window_iters.front();
        prev_value = *prev_iter;
        window_iters.pop_front();

        window_begin++;

        if ( window_begin < (src_size - half_length) )
        {
            next_value = src_begin[window_begin + half_length];
        }
        else
        {
            next_value = *(window_iters[window_iters.size() + 2*src_size - 2*(window_begin + half_length) - 2]);
        }

        if ( ( *rank_point < prev_value ) && ( *rank_point <= next_value ) )
        {
            sorted_window.erase(prev_iter);
            window_iters.push_back(sorted_window.insert(next_value));
        }
        else if ( ( *rank_point >= prev_value ) && ( *rank_point > next_value ) )
        {
            if ( rank_point == prev_iter )
            {
                window_iters.push_back(sorted_window.insert(next_value));
                rank_point--;

                sorted_window.erase(prev_iter);
            }
            else
            {
                sorted_window.erase(prev_iter);
                window_iters.push_back(sorted_window.insert(next_value));
            }
        }
        else if ( ( *rank_point < prev_value ) && ( *rank_point > next_value ) )
        {
            sorted_window.erase(prev_iter);
            window_iters.push_back(sorted_window.insert(next_value));

            rank_point--;
        }
        else if ( ( *rank_point >= prev_value ) && ( *rank_point <= next_value ) )
        {
            if (rank_point == prev_iter)
            {
                window_iters.push_back(sorted_window.insert(next_value));
                rank_point++;

                sorted_window.erase(prev_iter);
            }
            else
            {
                sorted_window.erase(prev_iter);
                window_iters.push_back(sorted_window.insert(next_value));

                rank_point++;
            }
        }
    }
}

template<unsigned int N,
        class T1, class S1,
        class T2, class S2,
        typename std::enable_if<(N == 1), int>::type = 0>
inline void lineRankOrderFilterND(const vigra::MultiArrayView <N, T1, S1> &src,
        vigra::MultiArrayView <N, T2, S2> dest,
        unsigned long half_length, double rank, unsigned int axis = 0)
{
    typename vigra::MultiArrayView <N, T1, S1>::const_iterator src_begin = src.begin();
    typename vigra::MultiArrayView <N, T1, S1>::const_iterator src_end = src.end();
    typename vigra::MultiArrayView <N, T2, S2>::iterator dest_begin = dest.begin();
    typename vigra::MultiArrayView <N, T2, S2>::iterator dest_end = dest.end();

    lineRankOrderFilter1D(src_begin, src_end, dest_begin, dest_end, half_length, rank);
}

template<unsigned int N,
        class T1, class S1,
        class T2, class S2,
        typename std::enable_if<(N > 1), int>::type = 0>
inline void lineRankOrderFilterND(const vigra::MultiArrayView <N, T1, S1> &src,
        vigra::MultiArrayView <N, T2, S2> dest,
        unsigned long half_length, double rank, unsigned int axis = 0)
{
    typename vigra::MultiArrayView<N, T1, S1>::difference_type transposed_axes;

    for (unsigned int i = 0; i < N; i++)
    {
        transposed_axes[i] = i;
    }

    std::swap(transposed_axes[0], transposed_axes[axis]);

    vigra::MultiArray<N, T1> src_transposed(src.transpose(transposed_axes));

    vigra::MultiArrayView<N, T2, S2> dest_transposed(dest.transpose(transposed_axes));


    typename vigra::MultiArrayView<N - 1, T1, S1>::difference_type pos;
    pos = 0;

    bool done = false;
    bool carry = true;
    while (!done)
    {
        lineRankOrderFilterND(src_transposed.bindOuter(pos), dest_transposed.bindOuter(pos), half_length, rank, 0);

        carry = true;
        for (unsigned int i = 0; ( carry && (i < (N - 1)) ); i++)
        {
            if ( (++pos[i]) < src_transposed.shape(i + 1) )
            {
                carry = false;
            }
            else
            {
                pos[i] = 0;
                carry = true;
            }
        }

        done = carry;
    }
}

template<unsigned int N,
        class T1, class S1,
        class T2, class S2>
inline void lineRankOrderFilter(const vigra::MultiArrayView <N, T1, S1> &src,
        vigra::MultiArrayView <N, T2, S2> dest,
        unsigned long half_length, double rank, unsigned int axis = 0)
{
    lineRankOrderFilterND(src, dest, half_length, rank, axis);
}

}

namespace vigra {

template <unsigned int N, class T, class S, typename std::enable_if<(N == 1), int>::type = 0>
std::ostream& println(std::ostream& out, const vigra::MultiArrayView<N, T, S>& array, unsigned int indent=0)
{
    for (unsigned int i = 0; i < indent; i++)
    {
        out << " ";
    }
    out << "{ ";

    for (unsigned int i = 0; i < (array.shape(0) - 1); i++)
    {
        out << array[i] << ", ";
    }
    out << array[array.shape(0) - 1] << " }";

    return(out);
}


template <unsigned int N, class T, class S, typename std::enable_if<(N > 1), int>::type = 0>
std::ostream& println(std::ostream& out, const vigra::MultiArrayView<N, T, S>& array, unsigned int indent=0)
{
    for (unsigned int i = 0; i < indent; i++)
    {
        out << " ";
    }
    out << "{" << std::endl;

    for (unsigned int i = 0; i < (array.shape(0) - 1); i++)
    {
        println(out, array.bindOuter(i), indent+1);
        out << ", " << std::endl;
    }
    println(out, array.bindOuter(array.shape(0) - 1), indent+1);
    out << std::endl;

    for (unsigned int i = 0; i < indent; i++)
    {
        out << " ";
    }
    out << "}";

    return(out);
}

template <unsigned int N, class T, class S>
std::ostream& operator<<(std::ostream& out, const vigra::MultiArrayView<N, T, S>& array)
{
    return(println(out, array));
}

}


#endif //__RANK_FILTER__
