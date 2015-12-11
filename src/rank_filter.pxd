cimport cython


cdef extern from "rank_filter_base.hxx" namespace "rank_filter":
    void lineRankOrderFilter1D[I1, I2](const I1& src_begin,
                                       const I1& src_end,
                                       I2& dest_begin,
                                       I2& dest_end,
                                       size_t half_length,
                                       double rank) nogil
