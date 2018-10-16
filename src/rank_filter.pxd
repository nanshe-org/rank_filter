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
cdef inline bint ndindex(const numpy.npy_intp[:] shape,
                         numpy.npy_intp[:] pos) nogil:
    cdef Py_ssize_t i = shape.shape[0]
    while i > 0:
        i -= 1
        pos[i] += 1

        if pos[i] < shape[i]:
            return False
        elif i > 0:
            pos[i] = 0

    return True
