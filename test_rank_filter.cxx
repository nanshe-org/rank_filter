#include "vigra/unittest.hxx"

#include "rank_filter.hxx"

class RankFilterTest
{
private:

    const unsigned long size = 10;

    vigra::MultiArray< 1, double > array;
    vigra::MultiArray< 1, double > reverse_array;

    vigra::MultiArray< 1, double > expected_result;
    vigra::MultiArray< 1, double > result;

public:

    RankFilterTest() : array(size), reverse_array(size), expected_result(size), result(size)
    {
        for (int i = 0; i < array.size(); i++)
        {
            array[i] = i;
        }

        for (int i = 0; i < reverse_array.size() ; i++)
        {
            reverse_array[i] = reverse_array.size() - i - 1;
        }
    };

    ~RankFilterTest()
    {
    };

    void test_rank_filter_1()
    {
        expected_result = array;

        result = 0;

        lineRankOrderFilter(array, result, 0, 0.5);

        should(expected_result == result);
    };

    void test_rank_filter_2()
    {
        expected_result = reverse_array;

        result = 0;

        lineRankOrderFilter(reverse_array, result, 0, 0.5);

        should(expected_result == result);
    };

    void test_rank_filter_3()
    {
        expected_result = array;
        expected_result[0] = expected_result[1];
        expected_result[expected_result.size()  - 1] = expected_result[expected_result.size() - 2];

//        expected_result[0] = 1; expected_result[1] = 1; expected_result[2] = 2; expected_result[3] = 3;
//        expected_result[4] = 4; expected_result[5] = 5; expected_result[6] = 6; expected_result[7] = 7;
//        expected_result[8] = 8; expected_result[9] = 8;

        result = 0;

        lineRankOrderFilter(array, result, 1, 0.5);

        should(expected_result == result);
    };

    void test_rank_filter_4()
    {
        expected_result = reverse_array;
        expected_result[0] = expected_result[1];
        expected_result[expected_result.size()  - 1] = expected_result[expected_result.size() - 2];

//        expected_result[9] = 1; expected_result[8] = 1; expected_result[7] = 2; expected_result[6] = 3;
//        expected_result[5] = 4; expected_result[4] = 5; expected_result[3] = 6; expected_result[2] = 7;
//        expected_result[1] = 8; expected_result[0] = 8;

        result = 0;

        lineRankOrderFilter(reverse_array, result, 1, 0.5);

        should(expected_result == result);
    };

    void test_rank_filter_5()
    {
        expected_result = array;
        expected_result[0] = expected_result[1];
        expected_result[expected_result.size()  - 1] = expected_result[expected_result.size() - 2];

//        expected_result[0] = 1; expected_result[1] = 1; expected_result[2] = 2; expected_result[3] = 3;
//        expected_result[4] = 4; expected_result[5] = 5; expected_result[6] = 6; expected_result[7] = 7;
//        expected_result[8] = 8; expected_result[9] = 8;

        result = 0;

        lineRankOrderFilter(array, result, 2, 0.5);

        should(expected_result == result);
    };

    void test_rank_filter_6()
    {
        expected_result = reverse_array;
        expected_result[0] = expected_result[1];
        expected_result[expected_result.size()  - 1] = expected_result[expected_result.size() - 2];

//        expected_result[9] = 1; expected_result[8] = 1; expected_result[7] = 2; expected_result[6] = 3;
//        expected_result[5] = 4; expected_result[4] = 5; expected_result[3] = 6; expected_result[2] = 7;
//        expected_result[1] = 8; expected_result[0] = 8;

        result = 0;

        lineRankOrderFilter(reverse_array, result, 2, 0.5);

        should(expected_result == result);
    };

    void test_rank_filter_7()
    {
        expected_result = array;
        expected_result[0] = expected_result[1] = expected_result[2];
        expected_result[expected_result.size()  - 1] = expected_result[expected_result.size() - 2] = expected_result[expected_result.size() - 3];

//        expected_result[0] = 2; expected_result[1] = 2; expected_result[2] = 2; expected_result[3] = 3;
//        expected_result[4] = 4; expected_result[5] = 5; expected_result[6] = 6; expected_result[7] = 7;
//        expected_result[8] = 7; expected_result[9] = 7;

        result = 0;

        lineRankOrderFilter(array, result, 3, 0.5);

        should(expected_result == result);
    };

    void test_rank_filter_8()
    {
        expected_result = reverse_array;
        expected_result[0] = expected_result[1] = expected_result[2];
        expected_result[expected_result.size()  - 1] = expected_result[expected_result.size() - 2] = expected_result[expected_result.size() - 3];

//        expected_result[9] = 2; expected_result[8] = 2; expected_result[7] = 2; expected_result[6] = 3;
//        expected_result[5] = 4; expected_result[4] = 5; expected_result[3] = 6; expected_result[2] = 7;
//        expected_result[1] = 7; expected_result[0] = 7;

        result = 0;

        lineRankOrderFilter(reverse_array, result, 3, 0.5);

        should(expected_result == result);
    };

    void test_rank_filter_9()
    {
        expected_result = array;
        expected_result[0] = expected_result[1] = expected_result[2];
        expected_result[expected_result.size()  - 1] = expected_result[expected_result.size() - 2] = expected_result[expected_result.size() - 3];

//        expected_result[9] = 2; expected_result[8] = 2; expected_result[7] = 2; expected_result[6] = 3;
//        expected_result[5] = 4; expected_result[4] = 5; expected_result[3] = 6; expected_result[2] = 7;
//        expected_result[1] = 7; expected_result[0] = 7;

        result = 0;

        lineRankOrderFilter(array.insertSingletonDimension(0), result.insertSingletonDimension(0), 3, 0.5);

        should(expected_result == result);
    };

    void test_rank_filter_10()
    {
        expected_result = reverse_array;
        expected_result[0] = expected_result[1] = expected_result[2];
        expected_result[expected_result.size()  - 1] = expected_result[expected_result.size() - 2] = expected_result[expected_result.size() - 3];

//        expected_result[9] = 2; expected_result[8] = 2; expected_result[7] = 2; expected_result[6] = 3;
//        expected_result[5] = 4; expected_result[4] = 5; expected_result[3] = 6; expected_result[2] = 7;
//        expected_result[1] = 7; expected_result[0] = 7;

        result = 0;

        lineRankOrderFilter(reverse_array.insertSingletonDimension(0), result.insertSingletonDimension(0), 3, 0.5);

        should(expected_result == result);
    };
};

struct RankFilterTestSuite
        : public vigra::test_suite
{
    RankFilterTestSuite()
            : vigra::test_suite("RankFilterTestSuite")
    {
        add( testCase( &RankFilterTest::test_rank_filter_1 ) );
        add( testCase( &RankFilterTest::test_rank_filter_2 ) );
        add( testCase( &RankFilterTest::test_rank_filter_3 ) );
        add( testCase( &RankFilterTest::test_rank_filter_4 ) );
        add( testCase( &RankFilterTest::test_rank_filter_5 ) );
        add( testCase( &RankFilterTest::test_rank_filter_6 ) );
        add( testCase( &RankFilterTest::test_rank_filter_7 ) );
        add( testCase( &RankFilterTest::test_rank_filter_8 ) );
        add( testCase( &RankFilterTest::test_rank_filter_9 ) );
        add( testCase( &RankFilterTest::test_rank_filter_10 ) );
    }
}; // struct RankFilterTestSuite

int main(int argc, char ** argv)
{
    // run the multi-array testsuite
    RankFilterTestSuite test1;
    int failed = test1.run(vigra::testsToBeExecuted(argc, argv));
    std::cout << test1.report() << std::endl;

    return(failed != 0);
}