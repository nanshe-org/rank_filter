#define BOOST_TEST_MODULE RankFilterBaseModule
#include <boost/test/included/unit_test.hpp>

#include <boost/array.hpp>


#include "rank_filter_base.hxx"



struct RankFilterBaseFixture
{
    public:

        static constexpr unsigned long size = 10;

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

        RankFilterBaseFixture()
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

        ~RankFilterBaseFixture()
        {
        };
};



BOOST_AUTO_TEST_SUITE( RankFilterBaseSuite )


BOOST_FIXTURE_TEST_CASE(test_rank_filter_base_1, RankFilterBaseFixture)
{
    expected_result_1 = array_1;

    rank_filter::lineRankOrderFilter1D(array_1_begin, array_1_end, result_1_begin, result_1_end, 0, 0.5);

    BOOST_CHECK_EQUAL(expected_result_1, result_1);
}

BOOST_FIXTURE_TEST_CASE(test_rank_filter_base_2, RankFilterBaseFixture)
{
    expected_result_1 = reverse_array_1;

    rank_filter::lineRankOrderFilter1D(reverse_array_1_begin, reverse_array_1_end, result_1_begin, result_1_end, 0, 0.5);

    BOOST_CHECK_EQUAL(expected_result_1, result_1);
}

BOOST_FIXTURE_TEST_CASE(test_rank_filter_base_3, RankFilterBaseFixture)
{
    expected_result_1 = array_1;
    expected_result_1[0] = expected_result_1[1];
    expected_result_1[expected_result_1.size()  - 1] = expected_result_1[expected_result_1.size() - 2];

    rank_filter::lineRankOrderFilter1D(array_1_begin, array_1_end, result_1_begin, result_1_end, 1, 0.5);

    BOOST_CHECK_EQUAL(expected_result_1, result_1);
}

BOOST_FIXTURE_TEST_CASE(test_rank_filter_base_4, RankFilterBaseFixture)
{
    expected_result_1 = reverse_array_1;
    expected_result_1[0] = expected_result_1[1];
    expected_result_1[expected_result_1.size()  - 1] = expected_result_1[expected_result_1.size() - 2];

    rank_filter::lineRankOrderFilter1D(reverse_array_1_begin, reverse_array_1_end, result_1_begin, result_1_end, 1, 0.5);

    BOOST_CHECK_EQUAL(expected_result_1, result_1);
}

BOOST_FIXTURE_TEST_CASE(test_rank_filter_base_5, RankFilterBaseFixture)
{
    expected_result_1 = array_1;
    expected_result_1[0] = expected_result_1[1];
    expected_result_1[expected_result_1.size()  - 1] = expected_result_1[expected_result_1.size() - 2];

    rank_filter::lineRankOrderFilter1D(array_1_begin, array_1_end, result_1_begin, result_1_end, 2, 0.5);

    BOOST_CHECK_EQUAL(expected_result_1, result_1);
}

BOOST_FIXTURE_TEST_CASE(test_rank_filter_base_6, RankFilterBaseFixture)
{
    expected_result_1 = reverse_array_1;
    expected_result_1[0] = expected_result_1[1];
    expected_result_1[expected_result_1.size()  - 1] = expected_result_1[expected_result_1.size() - 2];

    rank_filter::lineRankOrderFilter1D(reverse_array_1_begin, reverse_array_1_end, result_1_begin, result_1_end, 2, 0.5);

    BOOST_CHECK_EQUAL(expected_result_1, result_1);
}

BOOST_FIXTURE_TEST_CASE(test_rank_filter_base_7, RankFilterBaseFixture)
{
    expected_result_1 = array_1;
    expected_result_1[0] = expected_result_1[1] = expected_result_1[2];
    expected_result_1[expected_result_1.size()  - 1] = expected_result_1[expected_result_1.size() - 2] = expected_result_1[expected_result_1.size() - 3];

    rank_filter::lineRankOrderFilter1D(array_1_begin, array_1_end, result_1_begin, result_1_end, 3, 0.5);

    BOOST_CHECK_EQUAL(expected_result_1, result_1);
}

BOOST_FIXTURE_TEST_CASE(test_rank_filter_base_8, RankFilterBaseFixture)
{
    expected_result_1 = reverse_array_1;
    expected_result_1[0] = expected_result_1[1] = expected_result_1[2];
    expected_result_1[expected_result_1.size()  - 1] = expected_result_1[expected_result_1.size() - 2] = expected_result_1[expected_result_1.size() - 3];

    rank_filter::lineRankOrderFilter1D(reverse_array_1_begin, reverse_array_1_end, result_1_begin, result_1_end, 3, 0.5);

    BOOST_CHECK_EQUAL(expected_result_1, result_1);
}

BOOST_FIXTURE_TEST_CASE(test_rank_filter_base_9, RankFilterBaseFixture)
{
    for (size_t i = 0; i < array_1.size(); i++)
    {
        expected_result_1[i] = (i < 5) ? array_1[5] : array_1[4];
    }

    rank_filter::lineRankOrderFilter1D(array_1_begin, array_1_end, result_1_begin, result_1_end, size - 1, 0.5);

    BOOST_CHECK_EQUAL(expected_result_1, result_1);
}


BOOST_AUTO_TEST_SUITE_END()
