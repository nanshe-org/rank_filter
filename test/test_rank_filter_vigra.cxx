#define BOOST_TEST_MODULE RankFilterVigraModule
#include <boost/test/included/unit_test.hpp>

#define __ASSERT_MACROS_DEFINE_VERSIONS_WITHOUT_UNDERSCORES 0

#include "rank_filter_vigra.hxx"


struct RankFilterVigraFixture
{
    public:

        static const unsigned long size = 10;


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

        RankFilterVigraFixture() : size_1(size), array_1(size_1), reverse_array_1(size_1), expected_result_1(size_1), result_1(size_1),
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

        ~RankFilterVigraFixture()
        {
        };
};



BOOST_AUTO_TEST_SUITE( RankFilterVigraSuite )


BOOST_FIXTURE_TEST_CASE(test_rank_filter_vigra_1, RankFilterVigraFixture)
{
    expected_result_1 = array_1;

    result_1 = 0;

    rank_filter::lineRankOrderFilter(array_1, result_1, 0, 0.5);

    BOOST_CHECK_EQUAL(expected_result_1, result_1);
}

BOOST_FIXTURE_TEST_CASE(test_rank_filter_vigra_2, RankFilterVigraFixture)
{
    expected_result_1 = reverse_array_1;

    result_1 = 0;

    rank_filter::lineRankOrderFilter(reverse_array_1, result_1, 0, 0.5);

    BOOST_CHECK_EQUAL(expected_result_1, result_1);
}

BOOST_FIXTURE_TEST_CASE(test_rank_filter_vigra_3, RankFilterVigraFixture)
{
    expected_result_1 = array_1;
    expected_result_1[0] = expected_result_1[1];
    expected_result_1[expected_result_1.size()  - 1] = expected_result_1[expected_result_1.size() - 2];

    result_1 = 0;

    rank_filter::lineRankOrderFilter(array_1, result_1, 1, 0.5);

    BOOST_CHECK_EQUAL(expected_result_1, result_1);
}

BOOST_FIXTURE_TEST_CASE(test_rank_filter_vigra_4, RankFilterVigraFixture)
{
    expected_result_1 = reverse_array_1;
    expected_result_1[0] = expected_result_1[1];
    expected_result_1[expected_result_1.size()  - 1] = expected_result_1[expected_result_1.size() - 2];

    result_1 = 0;

    rank_filter::lineRankOrderFilter(reverse_array_1, result_1, 1, 0.5);

    BOOST_CHECK_EQUAL(expected_result_1, result_1);
}

BOOST_FIXTURE_TEST_CASE(test_rank_filter_vigra_5, RankFilterVigraFixture)
{
    expected_result_1 = array_1;
    expected_result_1[0] = expected_result_1[1];
    expected_result_1[expected_result_1.size()  - 1] = expected_result_1[expected_result_1.size() - 2];

    result_1 = 0;

    rank_filter::lineRankOrderFilter(array_1, result_1, 2, 0.5);

    BOOST_CHECK_EQUAL(expected_result_1, result_1);
}

BOOST_FIXTURE_TEST_CASE(test_rank_filter_vigra_6, RankFilterVigraFixture)
{
    expected_result_1 = reverse_array_1;
    expected_result_1[0] = expected_result_1[1];
    expected_result_1[expected_result_1.size()  - 1] = expected_result_1[expected_result_1.size() - 2];

    result_1 = 0;

    rank_filter::lineRankOrderFilter(reverse_array_1, result_1, 2, 0.5);

    BOOST_CHECK_EQUAL(expected_result_1, result_1);
}

BOOST_FIXTURE_TEST_CASE(test_rank_filter_vigra_7, RankFilterVigraFixture)
{
    expected_result_1 = array_1;
    expected_result_1[0] = expected_result_1[1] = expected_result_1[2];
    expected_result_1[expected_result_1.size()  - 1] = expected_result_1[expected_result_1.size() - 2] = expected_result_1[expected_result_1.size() - 3];

    result_1 = 0;

    rank_filter::lineRankOrderFilter(array_1, result_1, 3, 0.5);

    BOOST_CHECK_EQUAL(expected_result_1, result_1);
}

BOOST_FIXTURE_TEST_CASE(test_rank_filter_vigra_8, RankFilterVigraFixture)
{
    expected_result_1 = reverse_array_1;
    expected_result_1[0] = expected_result_1[1] = expected_result_1[2];
    expected_result_1[expected_result_1.size()  - 1] = expected_result_1[expected_result_1.size() - 2] = expected_result_1[expected_result_1.size() - 3];

    result_1 = 0;

    rank_filter::lineRankOrderFilter(reverse_array_1, result_1, 3, 0.5);

    BOOST_CHECK_EQUAL(expected_result_1, result_1);
}

BOOST_FIXTURE_TEST_CASE(test_rank_filter_vigra_9, RankFilterVigraFixture)
{
    expected_result_1 = array_1;
    expected_result_1[0] = expected_result_1[1] = expected_result_1[2];
    expected_result_1[expected_result_1.size()  - 1] = expected_result_1[expected_result_1.size() - 2] = expected_result_1[expected_result_1.size() - 3];

    result_1 = 0;

    rank_filter::lineRankOrderFilter(array_1.insertSingletonDimension(0), result_1.insertSingletonDimension(0), 3, 0.5, 1);

    BOOST_CHECK_EQUAL(expected_result_1, result_1);
}

BOOST_FIXTURE_TEST_CASE(test_rank_filter_vigra_10, RankFilterVigraFixture)
{
    expected_result_1 = reverse_array_1;
    expected_result_1[0] = expected_result_1[1] = expected_result_1[2];
    expected_result_1[expected_result_1.size()  - 1] = expected_result_1[expected_result_1.size() - 2] = expected_result_1[expected_result_1.size() - 3];

    result_1 = 0;

    rank_filter::lineRankOrderFilter(reverse_array_1.insertSingletonDimension(0), result_1.insertSingletonDimension(0), 3, 0.5, 1);

    BOOST_CHECK_EQUAL(expected_result_1, result_1);
}

BOOST_FIXTURE_TEST_CASE(test_rank_filter_vigra_11, RankFilterVigraFixture)
{
    expected_result_2 = array_2;

    result_2 = 0;

    rank_filter::lineRankOrderFilter(array_2, result_2, 0, 0.5);

    BOOST_CHECK_EQUAL(expected_result_2, result_2);
}

BOOST_FIXTURE_TEST_CASE(test_rank_filter_vigra_12, RankFilterVigraFixture)
{
    expected_result_2 = reverse_array_2;

    result_2 = 0;

    rank_filter::lineRankOrderFilter(reverse_array_2, result_2, 0, 0.5);

    BOOST_CHECK_EQUAL(expected_result_2, result_2);
}

BOOST_FIXTURE_TEST_CASE(test_rank_filter_vigra_13, RankFilterVigraFixture)
{
    expected_result_2 = array_2;
    expected_result_2.bindInner(0) = expected_result_2.bindInner(1);
    expected_result_2.bindInner(expected_result_2.shape(0) - 1) = expected_result_2.bindInner(expected_result_2.shape(0) - 2);

    result_2 = 0;

    rank_filter::lineRankOrderFilter(array_2, result_2, 1, 0.5);

    BOOST_CHECK_EQUAL(expected_result_2, result_2);
}

BOOST_FIXTURE_TEST_CASE(test_rank_filter_vigra_14, RankFilterVigraFixture)
{
    expected_result_2 = reverse_array_2;
    expected_result_2.bindInner(0) = expected_result_2.bindInner(1);
    expected_result_2.bindInner(expected_result_2.shape(0) - 1) = expected_result_2.bindInner(expected_result_2.shape(0) - 2);

    result_2 = 0;

    rank_filter::lineRankOrderFilter(reverse_array_2, result_2, 1, 0.5);

    BOOST_CHECK_EQUAL(expected_result_2, result_2);
}

BOOST_FIXTURE_TEST_CASE(test_rank_filter_vigra_15, RankFilterVigraFixture)
{
    expected_result_2 = array_2;
    expected_result_2.bindOuter(0) = expected_result_2.bindOuter(1);
    expected_result_2.bindOuter(expected_result_2.shape(0) - 1) = expected_result_2.bindOuter(expected_result_2.shape(0) - 2);

    result_2 = 0;

    rank_filter::lineRankOrderFilter(array_2, result_2, 1, 0.5, 1);

    BOOST_CHECK_EQUAL(expected_result_2, result_2);
}

BOOST_FIXTURE_TEST_CASE(test_rank_filter_vigra_16, RankFilterVigraFixture)
{
    expected_result_2 = reverse_array_2;
    expected_result_2.bindOuter(0) = expected_result_2.bindOuter(1);
    expected_result_2.bindOuter(expected_result_2.shape(0) - 1) = expected_result_2.bindOuter(expected_result_2.shape(0) - 2);

    result_2 = 0;

    rank_filter::lineRankOrderFilter(reverse_array_2, result_2, 1, 0.5, 1);

    BOOST_CHECK_EQUAL(expected_result_2, result_2);
}

BOOST_FIXTURE_TEST_CASE(test_rank_filter_vigra_17, RankFilterVigraFixture)
{
    expected_result_2 = reverse_array_2;
    expected_result_2.bindOuter(0) = expected_result_2.bindOuter(1);
    expected_result_2.bindOuter(expected_result_2.shape(0) - 1) = expected_result_2.bindOuter(expected_result_2.shape(0) - 2);

    result_2 = reverse_array_2;

    rank_filter::lineRankOrderFilter(result_2, result_2, 1, 0.5, 1);

    BOOST_CHECK_EQUAL(expected_result_2, result_2);
}

BOOST_FIXTURE_TEST_CASE(test_rank_filter_vigra_18, RankFilterVigraFixture)
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
