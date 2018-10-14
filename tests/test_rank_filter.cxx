#define BOOST_TEST_MODULE RankFilterModule
#include <boost/test/included/unit_test.hpp>

#include <boost/array.hpp>


#include "rank_filter.hxx"



struct RankFilterFixture
{
    public:

        static const unsigned long size = 10;

        boost::array<double, size> array_1;
        boost::array<double, size> reverse_array_1;

        boost::array<double, size> expected_result_1;
        boost::array<double, size> result_1;

        boost::array<double, size>::iterator array_1_begin;
        boost::array<double, size>::iterator array_1_end;

        boost::array<double, size>::iterator reverse_array_1_begin;
        boost::array<double, size>::iterator reverse_array_1_end;

        boost::array<double, size>::iterator result_1_begin;
        boost::array<double, size>::iterator result_1_end;

    public:

        RankFilterFixture()
        {
            for (int i = 0; i < size; i++)
            {
                array_1[i] = i;
            }

            for (int i = 0; i < size; i++)
            {
                reverse_array_1[i] = size - i - 1;
            }

            expected_result_1.fill(0);
            result_1.fill(0);

            array_1_begin = array_1.begin();
            array_1_end = array_1.end();
            reverse_array_1_begin = reverse_array_1.begin();
            reverse_array_1_end = reverse_array_1.end();

            result_1_begin = result_1.begin();
            result_1_end = result_1.end();
        };

        ~RankFilterFixture()
        {
        };
};



BOOST_AUTO_TEST_SUITE( RankFilterSuite )


BOOST_FIXTURE_TEST_CASE(test_rank_filter_1, RankFilterFixture)
{
    expected_result_1 = array_1;

    rank_filter::lineRankOrderFilter1D(array_1_begin, array_1_end, result_1_begin, result_1_end, 0, 0.5);

    BOOST_CHECK_EQUAL(expected_result_1, result_1);
}

BOOST_FIXTURE_TEST_CASE(test_rank_filter_2, RankFilterFixture)
{
    expected_result_1 = reverse_array_1;

    rank_filter::lineRankOrderFilter1D(reverse_array_1_begin, reverse_array_1_end, result_1_begin, result_1_end, 0, 0.5);

    BOOST_CHECK_EQUAL(expected_result_1, result_1);
}

BOOST_FIXTURE_TEST_CASE(test_rank_filter_3, RankFilterFixture)
{
    expected_result_1 = array_1;
    expected_result_1[0] = expected_result_1[1];
    expected_result_1[expected_result_1.size()  - 1] = expected_result_1[expected_result_1.size() - 2];

    rank_filter::lineRankOrderFilter1D(array_1_begin, array_1_end, result_1_begin, result_1_end, 1, 0.5);

    BOOST_CHECK_EQUAL(expected_result_1, result_1);
}

BOOST_FIXTURE_TEST_CASE(test_rank_filter_4, RankFilterFixture)
{
    expected_result_1 = reverse_array_1;
    expected_result_1[0] = expected_result_1[1];
    expected_result_1[expected_result_1.size()  - 1] = expected_result_1[expected_result_1.size() - 2];

    rank_filter::lineRankOrderFilter1D(reverse_array_1_begin, reverse_array_1_end, result_1_begin, result_1_end, 1, 0.5);

    BOOST_CHECK_EQUAL(expected_result_1, result_1);
}

BOOST_FIXTURE_TEST_CASE(test_rank_filter_5, RankFilterFixture)
{
    expected_result_1 = array_1;
    expected_result_1[0] = expected_result_1[1];
    expected_result_1[expected_result_1.size()  - 1] = expected_result_1[expected_result_1.size() - 2];

    rank_filter::lineRankOrderFilter1D(array_1_begin, array_1_end, result_1_begin, result_1_end, 2, 0.5);

    BOOST_CHECK_EQUAL(expected_result_1, result_1);
}

BOOST_FIXTURE_TEST_CASE(test_rank_filter_6, RankFilterFixture)
{
    expected_result_1 = reverse_array_1;
    expected_result_1[0] = expected_result_1[1];
    expected_result_1[expected_result_1.size()  - 1] = expected_result_1[expected_result_1.size() - 2];

    rank_filter::lineRankOrderFilter1D(reverse_array_1_begin, reverse_array_1_end, result_1_begin, result_1_end, 2, 0.5);

    BOOST_CHECK_EQUAL(expected_result_1, result_1);
}

BOOST_FIXTURE_TEST_CASE(test_rank_filter_7, RankFilterFixture)
{
    expected_result_1 = array_1;
    expected_result_1[0] = expected_result_1[1] = expected_result_1[2];
    expected_result_1[expected_result_1.size()  - 1] = expected_result_1[expected_result_1.size() - 2] = expected_result_1[expected_result_1.size() - 3];

    rank_filter::lineRankOrderFilter1D(array_1_begin, array_1_end, result_1_begin, result_1_end, 3, 0.5);

    BOOST_CHECK_EQUAL(expected_result_1, result_1);
}

BOOST_FIXTURE_TEST_CASE(test_rank_filter_8, RankFilterFixture)
{
    expected_result_1 = reverse_array_1;
    expected_result_1[0] = expected_result_1[1] = expected_result_1[2];
    expected_result_1[expected_result_1.size()  - 1] = expected_result_1[expected_result_1.size() - 2] = expected_result_1[expected_result_1.size() - 3];

    rank_filter::lineRankOrderFilter1D(reverse_array_1_begin, reverse_array_1_end, result_1_begin, result_1_end, 3, 0.5);

    BOOST_CHECK_EQUAL(expected_result_1, result_1);
}

BOOST_FIXTURE_TEST_CASE(test_rank_filter_9, RankFilterFixture)
{
    for (size_t i = 0; i < array_1.size(); i++)
    {
        expected_result_1[i] = (i < 5) ? array_1[5] : array_1[4];
    }

    rank_filter::lineRankOrderFilter1D(array_1_begin, array_1_end, result_1_begin, result_1_end, size - 1, 0.5);

    BOOST_CHECK_EQUAL(expected_result_1, result_1);
}


BOOST_AUTO_TEST_SUITE_END()
