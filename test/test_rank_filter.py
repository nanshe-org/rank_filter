#!/usr/bin/env python


import itertools
import sys
import unittest

import numpy

import rank_filter


if sys.version_info.major >= 3:
    xrange = range


class TestRankFilter(unittest.TestCase):
    def setUp(self):
        self.size = 10


        self.size_1 = (self.size,)

        self.array_1 = numpy.zeros(self.size_1, dtype=float)
        self.reverse_array_1 = numpy.zeros(self.size_1, dtype=float)

        self.expected_result_1 = numpy.zeros(self.size_1, dtype=float)
        self.result_1 = numpy.zeros(self.size_1, dtype=float)


        self.size_2 = (self.size, self.size,)

        self.array_2 = numpy.zeros(self.size_2, dtype=float)
        self.reverse_array_2 = numpy.zeros(self.size_2, dtype=float)

        self.expected_result_2 = numpy.zeros(self.size_2, dtype=float)
        self.result_2 = numpy.zeros(self.size_2, dtype=float)


        for i, in itertools.product(*[xrange(_) for _ in self.array_1.shape]):
            self.array_1[i] = i

        for i, in itertools.product(*[xrange(_) for _ in self.reverse_array_1.shape]):
            self.reverse_array_1[i] = self.reverse_array_1.shape[0] - i - 1

        for i, j in itertools.product(*[xrange(_) for _ in self.array_2.shape]):
            self.array_2[i] = self.array_2.shape[1]*i + j

        for i, j in itertools.product(*[xrange(_) for _ in self.reverse_array_2.shape]):
            self.reverse_array_2[i] = self.reverse_array_2.shape[1]*(self.reverse_array_2.shape[0] - i - 1) +\
                                      (self.reverse_array_2.shape[1] - j - 1)


    def tearDown(self):
        del self.size_1

        del self.array_1
        del self.reverse_array_1

        del self.expected_result_1
        del self.result_1


        del self.size_2

        del self.array_2
        del self.reverse_array_2

        del self.expected_result_2
        del self.result_2


    def test_rank_filter_1(self):
        self.expected_result_1[:] = self.array_1

        self.result_1[:] = 0

        rank_filter.lineRankOrderFilter(self.array_1, 0, 0.5, out=self.result_1)

        assert((self.expected_result_1 == self.result_1).all())


    def test_rank_filter_2(self):
        self.expected_result_1[:] = self.reverse_array_1

        self.result_1[:] = 0

        rank_filter.lineRankOrderFilter(self.reverse_array_1, 0, 0.5, out=self.result_1)

        assert((self.expected_result_1 == self.result_1).all())


    def test_rank_filter_3(self):
        self.expected_result_1[:] = self.array_1
        self.expected_result_1[0] = self.expected_result_1[1]
        self.expected_result_1[-1] = self.expected_result_1[-2]

        self.result_1[:] = 0

        rank_filter.lineRankOrderFilter(self.array_1, 1, 0.5, out=self.result_1)

        assert((self.expected_result_1 == self.result_1).all())


    def test_rank_filter_4(self):
        self.expected_result_1[:] = self.reverse_array_1
        self.expected_result_1[0] = self.expected_result_1[1]
        self.expected_result_1[-1] = self.expected_result_1[-2]

        self.result_1[:] = 0

        rank_filter.lineRankOrderFilter(self.reverse_array_1, 1, 0.5, out=self.result_1)

        assert((self.expected_result_1 == self.result_1).all())


    def test_rank_filter_5(self):
        self.expected_result_1[:] = self.array_1
        self.expected_result_1[0] = self.expected_result_1[1]
        self.expected_result_1[-1] = self.expected_result_1[-2]

        self.result_1[:] = 0

        rank_filter.lineRankOrderFilter(self.array_1, 2, 0.5, out=self.result_1)

        assert((self.expected_result_1 == self.result_1).all())


    def test_rank_filter_6(self):
        self.expected_result_1[:] = self.reverse_array_1
        self.expected_result_1[0] = self.expected_result_1[1]
        self.expected_result_1[-1] = self.expected_result_1[-2]

        self.result_1[:] = 0

        rank_filter.lineRankOrderFilter(self.reverse_array_1, 2, 0.5, out=self.result_1)

        assert((self.expected_result_1 == self.result_1).all())


    def test_rank_filter_7(self):
        self.expected_result_1[:] = self.array_1
        self.expected_result_1[0] = self.expected_result_1[1] = self.expected_result_1[2]
        self.expected_result_1[-1] = self.expected_result_1[-2] = self.expected_result_1[-3]

        self.result_1[:] = 0

        rank_filter.lineRankOrderFilter(self.array_1, 3, 0.5, out=self.result_1)

        assert((self.expected_result_1 == self.result_1).all())


    def test_rank_filter_8(self):
        self.expected_result_1[:] = self.reverse_array_1
        self.expected_result_1[0] = self.expected_result_1[1] = self.expected_result_1[2]
        self.expected_result_1[-1] = self.expected_result_1[-2] = self.expected_result_1[-3]

        self.result_1[:] = 0

        rank_filter.lineRankOrderFilter(self.reverse_array_1, 3, 0.5, out=self.result_1)

        assert((self.expected_result_1 == self.result_1).all())


    def test_rank_filter_9(self):
        self.expected_result_1[:] = self.array_1
        self.expected_result_1[0] = self.expected_result_1[1] = self.expected_result_1[2]
        self.expected_result_1[-1] = self.expected_result_1[-2] = self.expected_result_1[-3]

        self.result_1[:] = 0

        rank_filter.lineRankOrderFilter(self.array_1, 3, 0.5, 0, out=self.result_1)

        assert((self.expected_result_1 == self.result_1).all())


    def test_rank_filter_10(self):
        self.expected_result_1[:] = self.reverse_array_1
        self.expected_result_1[0] = self.expected_result_1[1] = self.expected_result_1[2]
        self.expected_result_1[-1] = self.expected_result_1[-2] = self.expected_result_1[-3]

        self.result_1[:] = 0

        rank_filter.lineRankOrderFilter(self.reverse_array_1, 3, 0.5, 0, out=self.result_1)

        assert((self.expected_result_1 == self.result_1).all())


    def test_rank_filter_11(self):
        self.expected_result_2[:] = self.array_2

        self.result_2[:] = 0

        rank_filter.lineRankOrderFilter(self.array_2, 0, 0.5, out=self.result_2)

        assert((self.expected_result_2 == self.result_2).all())


    def test_rank_filter_12(self):
        self.expected_result_2[:] = self.reverse_array_2

        self.result_2[:] = 0

        rank_filter.lineRankOrderFilter(self.reverse_array_2, 0, 0.5, out=self.result_2)

        assert((self.expected_result_2 == self.result_2).all())


    def test_rank_filter_13(self):
        self.expected_result_1[:] = self.array_1
        self.expected_result_1[0] = self.expected_result_1[1]
        self.expected_result_1[-1] = self.expected_result_1[-2]

        self.result_1[:] = 0

        rank_filter.lineRankOrderFilter(self.array_1, 1, 0.5, 0, out=self.result_1)

        assert((self.expected_result_1 == self.result_1).all())


    def test_rank_filter_14(self):
        self.expected_result_2[:] = self.reverse_array_2
        self.expected_result_2[0] = self.expected_result_2[1]
        self.expected_result_2[-1] = self.expected_result_2[-2]

        self.result_2[:] = 0

        rank_filter.lineRankOrderFilter(self.reverse_array_2, 1, 0.5, 0, out=self.result_2)

        assert((self.expected_result_2 == self.result_2).all())


    def test_rank_filter_15(self):
        self.expected_result_2[:] = self.array_2
        self.expected_result_2[..., 0] = self.expected_result_2[..., 1]
        self.expected_result_2[..., -1] = self.expected_result_2[..., -2]

        self.result_2[:] = 0

        rank_filter.lineRankOrderFilter(self.array_2, 1, 0.5, -1, out=self.result_2)

        assert((self.expected_result_2 == self.result_2).all())


    def test_rank_filter_16(self):
        self.expected_result_2[:] = self.reverse_array_2
        self.expected_result_2[..., 0] = self.expected_result_2[..., 1]
        self.expected_result_2[..., -1] = self.expected_result_2[..., -2]

        self.result_2[:] = 0

        rank_filter.lineRankOrderFilter(self.reverse_array_2, 1, 0.5, -1, out=self.result_2)

        assert((self.expected_result_2 == self.result_2).all())


    def test_rank_filter_17(self):
        self.expected_result_2[:] = self.reverse_array_2
        self.expected_result_2[..., 0] = self.expected_result_2[..., 1]
        self.expected_result_2[..., -1] = self.expected_result_2[..., -2]

        self.result_2 = self.reverse_array_2

        rank_filter.lineRankOrderFilter(self.result_2, 1, 0.5, -1, out=self.result_2)

        assert((self.expected_result_2 == self.result_2).all())


    def test_rank_filter_18(self):
        for i in xrange(len(self.array_1)):
            self.expected_result_1[i] = self.array_1[5] if (i < 5) else self.array_1[4]

        self.result_1[:] = 0

        rank_filter.lineRankOrderFilter(self.array_1, len(self.array_1) - 1, 0.5, out=self.result_1)

        assert((self.expected_result_1 == self.result_1).all())


if __name__ == "__main__":
    unittest.main()
