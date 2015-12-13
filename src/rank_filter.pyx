from rank_filter cimport lineRankOrderFilter1D_floating

import cython

import itertools

import numpy

include "version.pxi"


@cython.boundscheck(False)
def lineRankOrderFilter(image, int half_length, float rank, int axis=-1, out=None):
    """
        Runs a linear rank filter kernel along one dimension of an array.

        Args:
            image(numpy.ndarray):      array to run the rank filter over.

            half_window_size(int):     half the window size for the kernel.

            rank(float):               quantile to use from ``0.0`` to ``1.0``.

            axis(int):                 which axis to direct and run the kernel
                                       over defaults to the last one
                                       (e.g. ``-1``).

            out(numpy.ndarray):        where to store the results to. Creates a
                                       new array if not specified. If it is the
                                       same as image, it will run in-place.

        Returns:
            out(numpy.ndarray):        result of running the linear rank filter.
    """

    assert (half_length >= 0), \
            "Window must be non-negative."
    assert ((half_length + 1) <= image.shape[axis]), \
            "Window must be no bigger than the image."

    if out is None:
        out = image.copy()
    else:
        assert (image.dtype == out.dtype), \
                "Both `image` and `out` must have the same type."
        out[...] = image

    lineRankOrderFilter1D = None
    if out.dtype.type == numpy.float32:
        lineRankOrderFilter1D = lambda a1, a2: \
            lineRankOrderFilter1D_floating[cython.float](
                a1, a2, half_length, rank
            )
    elif out.dtype.type == numpy.float64:
        lineRankOrderFilter1D = lambda a1, a2: \
            lineRankOrderFilter1D_floating[cython.double](
                a1, a2, half_length, rank
            )
    else:
        raise TypeError(
            "Only `float32` and `float64` are supported for `image` and `out`."
        )

    out_swap = out.swapaxes(axis, -1).copy()
    out_strip = None

    for each_slice in itertools.product(*[
        xrange(_) for _ in out_swap.shape[:-1]
    ]):
        out_strip = out_swap[each_slice]
        lineRankOrderFilter1D(out_strip, out_strip)

    out_swap = out_swap.swapaxes(-1, axis).copy()
    out[...] = out_swap


    return(out)
