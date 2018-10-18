from rank_filter cimport lineRankOrderFilter1D_floating_inplace_loop

cimport cython

cimport numpy
import numpy

include "version.pxi"

numpy.import_array()


@cython.boundscheck(False)
def lineRankOrderFilter(numpy.ndarray a not None,
                        size_t half_length,
                        double rank,
                        int axis=-1,
                        numpy.ndarray out=None):
    """
        Runs a linear rank filter kernel along one dimension of an array.

        Args:
            a(numpy.ndarray):          array to run the rank filter over.

            half_length(size_t):       half the window size for the kernel.

            rank(double):              quantile to use from ``0.0`` to ``1.0``.

            axis(int):                 which axis to direct and run the kernel
                                       over defaults to the last one
                                       (e.g. ``-1``).

            out(numpy.ndarray):        where to store the results to. Creates a
                                       new array if not specified. If it is the
                                       same as a, it will run in-place.

        Returns:
            out(numpy.ndarray):        result of running the linear rank filter.
    """

    cdef int a_type_num = numpy.PyArray_TYPE(a)
    cdef int out_type_num

    cdef numpy.ndarray out_swap

    if -a.ndim <= axis < 0:
        axis += a.ndim
    elif not (0 <= axis < a.ndim):
        raise ValueError("`axis` needs to be within `a.ndim`")

    if not ((half_length + 1) <= <size_t>(a.shape[axis])):
        raise ValueError("Window must be no bigger than `a.shape[axis]`.")

    if not (0.0 <= rank <= 1.0):
        raise ValueError("The rank must be between 0.0 and 1.0.")

    if out is None:
        out = numpy.PyArray_NewCopy(a, numpy.NPY_CORDER)
        out_type_num = a_type_num
    else:
        out_type_num = numpy.PyArray_TYPE(out)
        if a_type_num != out_type_num:
            raise TypeError("Both `a` and `out` must have the same type.")
        if not numpy.PyArray_SAMESHAPE(a, out):
            raise ValueError("Both `a` and `out` must have the same shape.")
        if numpy.PyArray_CopyInto(out, a) == -1:
            raise RuntimeError("Unable to copy `a` to `out`.")

    out_swap = numpy.PyArray_SwapAxes(out, axis, out.ndim - 1)
    out_swap = numpy.PyArray_GETCONTIGUOUS(out_swap)

    cdef numpy.npy_intp out_swap_size = numpy.PyArray_SIZE(out_swap)
    cdef numpy.npy_intp out_swap_step = out_swap.shape[out.ndim - 1]
    if out_type_num == numpy.NPY_FLOAT32:
        lineRankOrderFilter1D_floating_inplace_loop[float](
            <float*>(out_swap.data), out_swap_size, out_swap_step,
            half_length, rank
        )
    elif out_type_num == numpy.NPY_FLOAT64:
        lineRankOrderFilter1D_floating_inplace_loop[double](
            <double*>(out_swap.data), out_swap_size, out_swap_step,
            half_length, rank
        )
    else:
        raise TypeError(
            "Only `float32` and `float64` are supported for `a` and `out`."
        )

    out_swap = numpy.PyArray_SwapAxes(out_swap, out.ndim - 1, axis)
    if numpy.PyArray_CopyInto(out, out_swap) == -1:
        raise RuntimeError("Unable to copy `out_swap` to `out`.")

    return(out)
