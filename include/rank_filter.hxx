#ifndef __RANK_FILTER__
#define __RANK_FILTER__


#include <deque>
#include <cassert>
#include <functional>
#include <iostream>
#include <iterator>

#include <boost/array.hpp>
#include <boost/container/set.hpp>
#include <boost/container/node_allocator.hpp>
#include <boost/math/special_functions/round.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits.hpp>


namespace rank_filter
{

template<class I1,
         class I2>
inline void lineRankOrderFilter1D(const I1& src_begin, const I1& src_end,
        I2& dest_begin, I2& dest_end,
        size_t half_length, double rank)
{
    // Types in use.
    typedef typename std::iterator_traits<I1>::value_type T1;
    typedef typename std::iterator_traits<I2>::value_type T2;
    typedef typename std::iterator_traits<I1>::difference_type I1_diff_t;
    typedef typename std::iterator_traits<I2>::difference_type I2_diff_t;

    // Establish common types to work with source and destination values.
    BOOST_STATIC_ASSERT((boost::is_same<T1, T2>::value));
    typedef T1 T;
    typedef typename boost::common_type<I1_diff_t, I2_diff_t>::type I_diff_t;

    // Define container types that will be used.
    typedef boost::container::multiset< T,
            std::less<T>,
            boost::container::node_allocator<T>,
            boost::container::tree_assoc_options< boost::container::tree_type<boost::container::scapegoat_tree> >::type> multiset;
    typedef std::deque< typename multiset::iterator > deque;

    // Lengths.
    const I_diff_t src_size = std::distance(src_begin, src_end);
    const I_diff_t dest_size = std::distance(dest_begin, dest_end);

    // Ensure the result will fit.
    assert(src_size <= dest_size);

    // Window length cannot exceed input data with reflection.
    assert((half_length + 1) <= src_size);

    // Rank must be in the range 0 to 1.
    assert((0 <= rank) && (rank <= 1));

    // Track values in window both in sorted and sequential order.
    multiset sorted_window;
    deque window_iters(2 * half_length + 1);

    // Iterators in source and destination
    I1 src_pos = src_begin;
    I1 dest_pos = dest_begin;

    // Get the initial window in sequential order with reflection
    // Insert elements in order to the multiset for sorting.
    // Store all multiset iterators into the deque in sequential order.
    std::deque<T> window_init(2 * half_length + 1);
    window_init[half_length] = *(src_pos++);
    for (I_diff_t j = 1; j < half_length + 1; j++)
    {
        window_init[half_length - j] = *src_pos;
        window_init[half_length + j] = *src_pos;
        src_pos++;
    }
    for (I_diff_t j = 0; j < 2 * half_length + 1; j++)
    {
        window_iters[j] = sorted_window.insert(window_init.front());
        window_init.pop_front();
    }

    // Window position corresponding to this rank.
    const I_diff_t rank_pos = static_cast<I_diff_t>(boost::math::round(rank * (2 * half_length)));
    typename multiset::iterator rank_point = sorted_window.begin();

    // Move our selection point to the corresponding rank.
    for (I_diff_t i = 0; i < rank_pos; i++)
    {
        rank_point++;
    }

    // Roll window forward one value at a time.
    typename multiset::iterator prev_iter;
    T prev_value;
    T next_value;
    I_diff_t window_begin = 0;
    while ( window_begin < src_size )
    {
        *(dest_pos++) = *rank_point;

        prev_iter = window_iters.front();
        prev_value = *prev_iter;
        window_iters.pop_front();

        window_begin++;

	// Determine next value to add to window.
	// Handle special cases like reflection at the end.
        if ( window_begin == src_size )
        {
            next_value = prev_value;
        }
        else if ( src_pos != src_end )
        {
            next_value = *(src_pos++);
        }
        else
        {
            next_value = *(window_iters[(2 * (src_size - (window_begin + 1)))]);
        }

	// Remove old value and add new value to the window.
	// Handle special cases where `rank_pos` may have an adjusted position
	// due to where the old and new values are inserted.
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

}


namespace std
{
    template <class T, size_t N>
    ostream& operator<<(ostream& out, const boost::array<T, N>& that)
    {
        out << "{ ";
        for (unsigned int i = 0; i < (N - 1); i++)
        {
            out << that[i] << ", ";
        }
        out << that[N - 1] << " }";

        return(out);
    }
}


#endif //__RANK_FILTER__
