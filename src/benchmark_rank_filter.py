#!/usr/bin/env python

from __future__ import division

import sys
import timeit

import numpy

from rank_filter import lineRankOrderFilter


def benchmark():
    input_array = numpy.random.normal(size=(100, 101, 102))
    output_array = numpy.empty_like(input_array)

    lineRankOrderFilter(input_array, 25, 0.5, 0, output_array)

def main(*argv):
    times = 10

    avg_time = timeit.timeit(
        "benchmark()",
        setup="from __main__ import benchmark",
        number=times
    ) / times

    print(
        "Of " + repr(times) + " trials," +
        " the average runtime = " + repr(avg_time) + "s."
    )

    return(0)


if __name__ == "__main__":
    sys.exit(main(*sys.argv))
