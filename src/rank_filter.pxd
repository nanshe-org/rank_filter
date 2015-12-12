cimport cython
from cython cimport floating


cdef extern from "rank_filter_base.hxx" namespace "rank_filter":
    void lineRankOrderFilter1D[I1, I2](const I1& src_begin,
                                       const I1& src_end,
                                       I2& dest_begin,
                                       I2& dest_end,
                                       size_t half_length,
                                       double rank) nogil


@cython.boundscheck(False)
@cython.initializedcheck(False)
@cython.nonecheck(False)
cdef inline void lineRankOrderFilter1D_floating(floating[:] src, floating[:] dest, size_t half_length, double rank) nogil:
    cdef floating* src_begin = &src[0]
    cdef floating* src_end = &src[-1] + 1
    cdef floating* dest_begin = &dest[0]
    cdef floating* dest_end = &dest[-1] + 1

    lineRankOrderFilter1D(src_begin, src_end, dest_begin, dest_end, half_length, rank)
