from rank_filter cimport lineRankOrderFilter1D_floating_inplace, ndindex

cimport cython

cimport numpy
import numpy

include "version.pxi"

numpy.import_array()


@cython.boundscheck(False)
def lineRankOrderFilter(numpy.ndarray image not None,
                        size_t half_length,
                        double rank,
                        int axis=-1,
                        numpy.ndarray out=None):
    """
        Runs a linear rank filter kernel along one dimension of an array.

        Args:
            image(numpy.ndarray):      array to run the rank filter over.

            half_length(size_t):       half the window size for the kernel.

            rank(double):              quantile to use from ``0.0`` to ``1.0``.

            axis(int):                 which axis to direct and run the kernel
                                       over defaults to the last one
                                       (e.g. ``-1``).

            out(numpy.ndarray):        where to store the results to. Creates a
                                       new array if not specified. If it is the
                                       same as image, it will run in-place.

        Returns:
            out(numpy.ndarray):        result of running the linear rank filter.
    """

    cdef int image_type_num = numpy.PyArray_TYPE(image)
    cdef int out_type_num

    cdef numpy.ndarray out_swap

    if -image.ndim <= axis < 0:
        axis += image.ndim
    elif not (0 <= axis < image.ndim):
        raise IndexError("`axis` needs to be within `image.ndim`")

    assert ((half_length + 1) <= image.shape[axis]), \
            "Window must be no bigger than the image."

    assert (0.0 <= rank <= 1.0), \
            "The rank must be between 0.0 and 1.0."

    if out is None:
        out = numpy.PyArray_NewCopy(image, numpy.NPY_CORDER)
        out_type_num = image_type_num
    else:
        out_type_num = numpy.PyArray_TYPE(out)
        assert (image_type_num == out_type_num), \
                "Both `image` and `out` must have the same type."
        assert numpy.PyArray_SAMESHAPE(image, out), \
                "Both `image` and `out` must have the same shape."
        if numpy.PyArray_CopyInto(out, image) == -1:
            raise RuntimeError("Unable to copy `image` to `out`.")

    out_swap = numpy.PyArray_SwapAxes(out, axis, out.ndim - 1)
    out_swap = numpy.PyArray_GETCONTIGUOUS(out_swap)

    cdef numpy.npy_intp axis_len = out.shape[axis]
    cdef numpy.npy_intp idx_len = out_swap.ndim
    cdef numpy.npy_intp[::1] out_swap_shape = <numpy.npy_intp[:idx_len]>(
        out_swap.shape
    )
    cdef numpy.npy_intp[::1] idx = numpy.PyArray_ZEROS(
        1, &idx_len, numpy.NPY_INTP, 0
    )
    cdef numpy.npy_intp[::1] out_swap_shape_1 = out_swap_shape[:-1]
    cdef numpy.npy_intp[::1] idx_1 = idx[:-1]
    cdef numpy.npy_intp* idx_ptr = &idx[0]
    cdef void* out_strip
    cdef bint stop = False
    if out_type_num == numpy.NPY_FLOAT32:
        while not stop:
            out_strip = numpy.PyArray_GetPtr(out_swap, idx_ptr)
            lineRankOrderFilter1D_floating_inplace[float](
                <float[:axis_len]>(<float*>out_strip), half_length, rank
            )
            stop = ndindex(out_swap_shape_1, idx_1)
    elif out_type_num == numpy.NPY_FLOAT64:
        while not stop:
            out_strip = numpy.PyArray_GetPtr(out_swap, idx_ptr)
            lineRankOrderFilter1D_floating_inplace[double](
                <double[:axis_len]>(<double*>out_strip), half_length, rank
            )
            stop = ndindex(out_swap_shape_1, idx_1)
    else:
        raise TypeError(
            "Only `float32` and `float64` are supported for `image` and `out`."
        )

    out_swap = numpy.PyArray_SwapAxes(out_swap, out.ndim - 1, axis)
    if numpy.PyArray_CopyInto(out, out_swap) == -1:
        raise RuntimeError("Unable to copy `out` to `out_swap`.")

    return(out)
