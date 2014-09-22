#ifndef __RANK_FILTER__
#define __RANK_FILTER__


#include <list>
#include <set>
#include <cmath>
#include <cassert>
#include <iostream>
#include <iterator>

#include <vigra/multi_array.hxx>
#include <vigra/linear_algebra.hxx>

template <class T1, class S1,
          class T2, class S2>
inline void lineRankOrderFilter(const vigra::MultiArrayView<1, T1, S1> & src,
                                vigra::MultiArrayView<1, T2, S2> dest,
                                unsigned long half_length, double rank)
{
    // Will ignore boundaries initially.
    // Then will try adding reflection.

    // Rank must be in the range 0 to 1
    assert((0 <= rank) && (rank <= 1));

    const int rank_pos = round(rank * (2*half_length));

    // The position of the
    typename vigra::MultiArrayView<1, T1, S1>::difference_type_1 window_begin(0);
    std::multiset<T1> sorted_window;
    std::list< typename std::multiset<T1>::iterator > window_iters;

    // Get the initial sorted window.
    // Include the reflection.
    for (typename vigra::MultiArrayView<1, T1, S1>::difference_type_1 j(half_length); j > 0; j--)
    {
        window_iters.push_back(sorted_window.insert(src[window_begin + j]));
    }
    for (typename vigra::MultiArrayView<1, T1, S1>::difference_type_1 j(0); j <= half_length; j++)
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


#endif //__RANK_FILTER__
