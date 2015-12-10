#ifndef __RANK_FILTER__
#define __RANK_FILTER__


#include <iostream>

#include <vigra/multi_array.hxx>

#include "rank_filter_base.hxx"


namespace rank_filter
{

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
