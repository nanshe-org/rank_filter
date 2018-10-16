from rank_filter cimport lineRankOrderFilter1D_floating_inplace

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

    cdef numpy.ndarray out_swap

    assert ((half_length + 1) <= (<object>image).shape[axis]), \
            "Window must be no bigger than the image."

    assert (0.0 <= rank <= 1.0), \
            "The rank must be between 0.0 and 1.0."

    if out is None:
        out = numpy.PyArray_NewCopy(image, numpy.NPY_CORDER)
    else:
        assert (image.descr.type_num == out.descr.type_num), \
                "Both `image` and `out` must have the same type."
        assert numpy.PyArray_SAMESHAPE(image, out), \
                "Both `image` and `out` must have the same shape."
        if numpy.PyArray_CopyInto(out, image) == -1:
            raise RuntimeError("Unable to copy `image` to `out`.")

    out_swap = numpy.PyArray_SwapAxes(out, axis, out.ndim - 1)
    out_swap = numpy.PyArray_GETCONTIGUOUS(out_swap)

    out_strip_indices = numpy.ndindex((<object>out_swap).shape[:-1])

    if out.descr.type_num == numpy.NPY_FLOAT32:
        for idx in out_strip_indices:
            lineRankOrderFilter1D_floating_inplace[float](
                out_swap[idx], half_length, rank
            )
    elif out.descr.type_num == numpy.NPY_FLOAT64:
        for idx in out_strip_indices:
            lineRankOrderFilter1D_floating_inplace[double](
                out_swap[idx], half_length, rank
            )
    else:
        raise TypeError(
            "Only `float32` and `float64` are supported for `image` and `out`."
        )

    out_swap = numpy.PyArray_SwapAxes(out_swap, out.ndim - 1, axis)
    if numpy.PyArray_CopyInto(out, out_swap) == -1:
        raise RuntimeError("Unable to copy `out` to `out_swap`.")

    return(out)
