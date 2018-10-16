cimport cython
from cython cimport floating

cimport numpy


cdef extern from "rank_filter.hxx" namespace "rank_filter":
    void lineRankOrderFilter1D[I1, I2](const I1& src_begin,
                                       const I1& src_end,
                                       I2& dest_begin,
                                       I2& dest_end,
                                       size_t half_length,
                                       double rank) nogil


@cython.boundscheck(False)
@cython.initializedcheck(False)
@cython.nonecheck(False)
cdef inline void lineRankOrderFilter1D_floating_inplace(floating* a_begin,
                                                        size_t a_len,
                                                        size_t half_length,
                                                        double rank) nogil:
    cdef floating* a_end = a_begin + a_len

    lineRankOrderFilter1D(
        a_begin, a_end, a_begin, a_end, half_length, rank
    )


@cython.boundscheck(False)
@cython.initializedcheck(False)
@cython.nonecheck(False)
cdef inline void lineRankOrderFilter1D_floating_inplace_loop(floating* out_data,
                                                             numpy.npy_intp out_size,
                                                             numpy.npy_intp out_step,
                                                             size_t half_length,
                                                             double rank) nogil:
    cdef numpy.npy_intp i

    cdef floating* out_begin = out_data
    cdef floating* out_end = out_data + out_step
    for i from 0 <= i < out_size by out_step:
        lineRankOrderFilter1D(
            out_begin, out_end, out_begin, out_end, half_length, rank
        )
        out_begin += out_step
        out_end += out_step
