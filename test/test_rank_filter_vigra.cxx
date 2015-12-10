#define BOOST_TEST_MODULE RankFilterModule
#include <boost/test/included/unit_test.hpp>


#include "rank_filter.hxx"


struct RankFilterFixture
{
    public:

        const unsigned long size = 10;


        vigra::MultiArray< 1, double >::difference_type size_1;

        vigra::MultiArray< 1, double > array_1;
        vigra::MultiArray< 1, double > reverse_array_1;

        vigra::MultiArray< 1, double > expected_result_1;
        vigra::MultiArray< 1, double > result_1;


        vigra::MultiArray< 2, double >::difference_type size_2;

        vigra::MultiArray< 2, double > array_2;
        vigra::MultiArray< 2, double > reverse_array_2;

        vigra::MultiArray< 2, double > expected_result_2;
        vigra::MultiArray< 2, double > result_2;

    public:

        RankFilterFixture() : size_1(size), array_1(size_1), reverse_array_1(size_1), expected_result_1(size_1), result_1(size_1),
        size_2(size, size), array_2(size_2), reverse_array_2(size_2), expected_result_2(size_2), result_2(size_2)
        {
            for (int i = 0; i < array_1.shape(0); i++)
            {
                array_1[i] = i;
            }

            for (int i = 0; i < reverse_array_1.shape(0); i++)
            {
                reverse_array_1[i] = reverse_array_1.shape(0) - i - 1;
            }


            for (int i = 0; i < array_2.shape(0); i++)
            {
                for (int j = 0; j < array_2.shape(1); j++)
                {
                    array_2(i, j) = array_2.shape(1)*i + j;
                }
            }

            for (int i = 0; i < reverse_array_2.shape(0); i++)
            {
                for (int j = 0; j < reverse_array_2.shape(1); j++)
                {
                    reverse_array_2(i, j) = reverse_array_2.shape(1) * (reverse_array_2.shape(0) - i - 1) + (reverse_array_2.shape(1) - j - 1);
                }
            }
        };

        ~RankFilterFixture()
        {
        };
};



BOOST_AUTO_TEST_SUITE( RankFilterSuite )


BOOST_FIXTURE_TEST_CASE(test_rank_filter_1, RankFilterFixture)
{
    expected_result_1 = array_1;

    result_1 = 0;

    rank_filter::lineRankOrderFilter(array_1, result_1, 0, 0.5);

    BOOST_CHECK_EQUAL(expected_result_1, result_1);
}

BOOST_FIXTURE_TEST_CASE(test_rank_filter_2, RankFilterFixture)
{
    expected_result_1 = reverse_array_1;

    result_1 = 0;

    rank_filter::lineRankOrderFilter(reverse_array_1, result_1, 0, 0.5);

    BOOST_CHECK_EQUAL(expected_result_1, result_1);
}

BOOST_FIXTURE_TEST_CASE(test_rank_filter_3, RankFilterFixture)
{
    expected_result_1 = array_1;
    expected_result_1[0] = expected_result_1[1];
    expected_result_1[expected_result_1.size()  - 1] = expected_result_1[expected_result_1.size() - 2];

    result_1 = 0;

    rank_filter::lineRankOrderFilter(array_1, result_1, 1, 0.5);

    BOOST_CHECK_EQUAL(expected_result_1, result_1);
}

BOOST_FIXTURE_TEST_CASE(test_rank_filter_4, RankFilterFixture)
{
    expected_result_1 = reverse_array_1;
    expected_result_1[0] = expected_result_1[1];
    expected_result_1[expected_result_1.size()  - 1] = expected_result_1[expected_result_1.size() - 2];

    result_1 = 0;

    rank_filter::lineRankOrderFilter(reverse_array_1, result_1, 1, 0.5);

    BOOST_CHECK_EQUAL(expected_result_1, result_1);
}

BOOST_FIXTURE_TEST_CASE(test_rank_filter_5, RankFilterFixture)
{
    expected_result_1 = array_1;
    expected_result_1[0] = expected_result_1[1];
    expected_result_1[expected_result_1.size()  - 1] = expected_result_1[expected_result_1.size() - 2];

    result_1 = 0;

    rank_filter::lineRankOrderFilter(array_1, result_1, 2, 0.5);

    BOOST_CHECK_EQUAL(expected_result_1, result_1);
}

BOOST_FIXTURE_TEST_CASE(test_rank_filter_6, RankFilterFixture)
{
    expected_result_1 = reverse_array_1;
    expected_result_1[0] = expected_result_1[1];
    expected_result_1[expected_result_1.size()  - 1] = expected_result_1[expected_result_1.size() - 2];

    result_1 = 0;

    rank_filter::lineRankOrderFilter(reverse_array_1, result_1, 2, 0.5);

    BOOST_CHECK_EQUAL(expected_result_1, result_1);
}

BOOST_FIXTURE_TEST_CASE(test_rank_filter_7, RankFilterFixture)
{
    expected_result_1 = array_1;
    expected_result_1[0] = expected_result_1[1] = expected_result_1[2];
    expected_result_1[expected_result_1.size()  - 1] = expected_result_1[expected_result_1.size() - 2] = expected_result_1[expected_result_1.size() - 3];

    result_1 = 0;

    rank_filter::lineRankOrderFilter(array_1, result_1, 3, 0.5);

    BOOST_CHECK_EQUAL(expected_result_1, result_1);
}

BOOST_FIXTURE_TEST_CASE(test_rank_filter_8, RankFilterFixture)
{
    expected_result_1 = reverse_array_1;
    expected_result_1[0] = expected_result_1[1] = expected_result_1[2];
    expected_result_1[expected_result_1.size()  - 1] = expected_result_1[expected_result_1.size() - 2] = expected_result_1[expected_result_1.size() - 3];

    result_1 = 0;

    rank_filter::lineRankOrderFilter(reverse_array_1, result_1, 3, 0.5);

    BOOST_CHECK_EQUAL(expected_result_1, result_1);
}

BOOST_FIXTURE_TEST_CASE(test_rank_filter_9, RankFilterFixture)
{
    expected_result_1 = array_1;
    expected_result_1[0] = expected_result_1[1] = expected_result_1[2];
    expected_result_1[expected_result_1.size()  - 1] = expected_result_1[expected_result_1.size() - 2] = expected_result_1[expected_result_1.size() - 3];

    result_1 = 0;

    rank_filter::lineRankOrderFilter(array_1.insertSingletonDimension(0), result_1.insertSingletonDimension(0), 3, 0.5, 1);

    BOOST_CHECK_EQUAL(expected_result_1, result_1);
}

BOOST_FIXTURE_TEST_CASE(test_rank_filter_10, RankFilterFixture)
{
    expected_result_1 = reverse_array_1;
    expected_result_1[0] = expected_result_1[1] = expected_result_1[2];
    expected_result_1[expected_result_1.size()  - 1] = expected_result_1[expected_result_1.size() - 2] = expected_result_1[expected_result_1.size() - 3];

    result_1 = 0;

    rank_filter::lineRankOrderFilter(reverse_array_1.insertSingletonDimension(0), result_1.insertSingletonDimension(0), 3, 0.5, 1);

    BOOST_CHECK_EQUAL(expected_result_1, result_1);
}

BOOST_FIXTURE_TEST_CASE(test_rank_filter_11, RankFilterFixture)
{
    expected_result_2 = array_2;

    result_2 = 0;

    rank_filter::lineRankOrderFilter(array_2, result_2, 0, 0.5);

    BOOST_CHECK_EQUAL(expected_result_2, result_2);
}

BOOST_FIXTURE_TEST_CASE(test_rank_filter_12, RankFilterFixture)
{
    expected_result_2 = reverse_array_2;

    result_2 = 0;

    rank_filter::lineRankOrderFilter(reverse_array_2, result_2, 0, 0.5);

    BOOST_CHECK_EQUAL(expected_result_2, result_2);
}

BOOST_FIXTURE_TEST_CASE(test_rank_filter_13, RankFilterFixture)
{
    expected_result_2 = array_2;
    expected_result_2.bindInner(0) = expected_result_2.bindInner(1);
    expected_result_2.bindInner(expected_result_2.shape(0) - 1) = expected_result_2.bindInner(expected_result_2.shape(0) - 2);

    result_2 = 0;

    rank_filter::lineRankOrderFilter(array_2, result_2, 1, 0.5);

    BOOST_CHECK_EQUAL(expected_result_2, result_2);
}

BOOST_FIXTURE_TEST_CASE(test_rank_filter_14, RankFilterFixture)
{
    expected_result_2 = reverse_array_2;
    expected_result_2.bindInner(0) = expected_result_2.bindInner(1);
    expected_result_2.bindInner(expected_result_2.shape(0) - 1) = expected_result_2.bindInner(expected_result_2.shape(0) - 2);

    result_2 = 0;

    rank_filter::lineRankOrderFilter(reverse_array_2, result_2, 1, 0.5);

    BOOST_CHECK_EQUAL(expected_result_2, result_2);
}

BOOST_FIXTURE_TEST_CASE(test_rank_filter_15, RankFilterFixture)
{
    expected_result_2 = array_2;
    expected_result_2.bindOuter(0) = expected_result_2.bindOuter(1);
    expected_result_2.bindOuter(expected_result_2.shape(0) - 1) = expected_result_2.bindOuter(expected_result_2.shape(0) - 2);

    result_2 = 0;

    rank_filter::lineRankOrderFilter(array_2, result_2, 1, 0.5, 1);

    BOOST_CHECK_EQUAL(expected_result_2, result_2);
}

BOOST_FIXTURE_TEST_CASE(test_rank_filter_16, RankFilterFixture)
{
    expected_result_2 = reverse_array_2;
    expected_result_2.bindOuter(0) = expected_result_2.bindOuter(1);
    expected_result_2.bindOuter(expected_result_2.shape(0) - 1) = expected_result_2.bindOuter(expected_result_2.shape(0) - 2);

    result_2 = 0;

    rank_filter::lineRankOrderFilter(reverse_array_2, result_2, 1, 0.5, 1);

    BOOST_CHECK_EQUAL(expected_result_2, result_2);
}

BOOST_FIXTURE_TEST_CASE(test_rank_filter_17, RankFilterFixture)
{
    expected_result_2 = reverse_array_2;
    expected_result_2.bindOuter(0) = expected_result_2.bindOuter(1);
    expected_result_2.bindOuter(expected_result_2.shape(0) - 1) = expected_result_2.bindOuter(expected_result_2.shape(0) - 2);

    result_2 = reverse_array_2;

    rank_filter::lineRankOrderFilter(result_2, result_2, 1, 0.5, 1);

    BOOST_CHECK_EQUAL(expected_result_2, result_2);
}

BOOST_FIXTURE_TEST_CASE(test_rank_filter_18, RankFilterFixture)
{
    for (size_t i = 0; i < array_1.size(); i++)
    {
        expected_result_1[i] = (i < 5) ? array_1[5] : array_1[4];
    }

    result_1 = 0;

    rank_filter::lineRankOrderFilter(array_1, result_1, size - 1, 0.5, 1);

    BOOST_CHECK_EQUAL(expected_result_1, result_1);
}


BOOST_AUTO_TEST_SUITE_END()
