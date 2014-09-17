#ifndef __RANK_FILTER__
#define __RANK_FILTER__


#include <list>
#include <set>
#include <cmath>
#include <cassert>
#include <iostream>
#include <iterator>
#include <type_traits>
#include <utility>

#include <vigra/multi_array.hxx>
#include <vigra/linear_algebra.hxx>

namespace vigra
{

template<unsigned int N,
        class T1, class S1,
        class T2, class S2,
        typename std::enable_if<(N == 1), int>::type = 0>
inline void lineRankOrderFilterND(const vigra::MultiArrayView <N, T1, S1> &src,
        vigra::MultiArrayView <N, T2, S2> dest,
        unsigned int half_length, float rank, unsigned int axis = N - 1)
{
    // Will ignore boundaries initially.
    // Then will try adding reflection.

    // Rank must be in the range 0 to 1
    assert((0 <= rank) && (rank <= 1));

    const int rank_pos = round(rank * (2 * half_length));

    // The position of the
    typename vigra::MultiArrayView<N, T1, S1>::difference_type_1 window_begin(0);
    std::multiset<T1> sorted_window;
    std::list< typename std::multiset<T1>::iterator > window_iters;

    // Get the initial sorted window.
    // Include the reflection.
    for (typename vigra::MultiArrayView<N, T1, S1>::difference_type_1 j(half_length); j > 0; j--)
    {
        window_iters.push_back(sorted_window.insert(src[window_begin + j]));
    }
    for (typename vigra::MultiArrayView<N, T1, S1>::difference_type_1 j(0); j <= half_length; j++)
    {
        window_iters.push_back(sorted_window.insert(src[window_begin + j]));
    }

    typename std::multiset<T1>::iterator rank_point = sorted_window.begin();

    for (int i = 0; i < rank_pos; i++)
    {
        rank_point++;
    }

    while ( window_begin < src.size() )
    {
        dest[window_begin] = *rank_point;

        typename std::multiset<T1>::iterator prev_iter(window_iters.front());
        T1 prev_value = *prev_iter;
        window_iters.pop_front();

        window_begin++;

        T1 next_value;
        if ( window_begin < (src.size() - half_length) )
        {
            next_value = src[window_begin + half_length];
        }
        else
        {
            next_value = src[2 * src.size() - (window_begin + half_length + 2)];
        }

        if ( ( *rank_point < *prev_iter ) && ( *rank_point <= next_value ) )
        {
            sorted_window.erase(prev_iter);
            window_iters.push_back(sorted_window.insert(next_value));
        }
        else if ( ( *rank_point >= *prev_iter ) && ( *rank_point > next_value ) )
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
        else if ( ( *rank_point < *prev_iter ) && ( *rank_point > next_value ) )
        {
            sorted_window.erase(prev_iter);
            window_iters.push_back(sorted_window.insert(next_value));

            rank_point--;
        }
        else if ( ( *rank_point >= *prev_iter ) && ( *rank_point <= next_value ) )
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
        typename std::enable_if<(N > 1), int>::type = 0>
inline void lineRankOrderFilterND(const vigra::MultiArrayView <N, T1, S1> &src,
        vigra::MultiArrayView <N, T2, S2> dest,
        unsigned int half_length, float rank, unsigned int axis = N - 1)
{
    typename vigra::MultiArrayView<N, T1, S1>::difference_type transposed_axes;

    for (unsigned int i = 0; i < N; i++)
    {
        transposed_axes[i] = i;
    }

    std::swap(transposed_axes[N - 1], transposed_axes[axis]);

    vigra::MultiArray<N, T1> src_transposed(src.transpose(transposed_axes));

    vigra::MultiArrayView<N, T1, S1> dest_transposed(dest.transpose(transposed_axes));


    typename vigra::MultiArrayView<N - 1, T1, S1>::difference_type pos;
    pos = 0;

    bool done = false;

    while (!done)
    {
        lineRankOrderFilterND(src_transposed.bindInner(pos), dest_transposed.bindInner(pos), half_length, rank);

        bool carry = true;
        for (unsigned int i = 0; ( carry && (i < (N - 1)) ); i++)
        {
            if ( (++pos[N - (i + 2)]) < src_transposed.shape(N - (i + 2)) )
            {
                carry = false;
            }
            else
            {
                pos[N - (i + 2)] = 0;
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
        unsigned int half_length, float rank, unsigned int axis = N - 1)
{
    lineRankOrderFilterND(src, dest, half_length, rank, axis);
}

}


#endif //__RANK_FILTER__
