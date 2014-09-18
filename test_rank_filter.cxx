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

    vigra::MultiArray< 2, double > array_2;
    vigra::MultiArray< 2, double > reverse_array_2;

    vigra::MultiArray< 2, double > expected_result_2;
    vigra::MultiArray< 2, double > result_2;

public:

    RankFilterTest() : array(size), reverse_array(size), expected_result(size), result(size),
                       array_2(size, size), reverse_array_2(size, size), expected_result_2(size, size), result_2(size, size)
    {
        for (int i = 0; i < array.size(); i++)
        {
            array[i] = i;
        }

        for (int i = 0; i < reverse_array.size() ; i++)
        {
            reverse_array[i] = reverse_array.size() - i - 1;
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

        result = 0;

        lineRankOrderFilter(array, result, 1, 0.5);

        should(expected_result == result);
    };

    void test_rank_filter_4()
    {
        expected_result = reverse_array;
        expected_result[0] = expected_result[1];
        expected_result[expected_result.size()  - 1] = expected_result[expected_result.size() - 2];

        result = 0;

        lineRankOrderFilter(reverse_array, result, 1, 0.5);

        should(expected_result == result);
    };

    void test_rank_filter_5()
    {
        expected_result = array;
        expected_result[0] = expected_result[1];
        expected_result[expected_result.size()  - 1] = expected_result[expected_result.size() - 2];

        result = 0;

        lineRankOrderFilter(array, result, 2, 0.5);

        should(expected_result == result);
    };

    void test_rank_filter_6()
    {
        expected_result = reverse_array;
        expected_result[0] = expected_result[1];
        expected_result[expected_result.size()  - 1] = expected_result[expected_result.size() - 2];

        result = 0;

        lineRankOrderFilter(reverse_array, result, 2, 0.5);

        should(expected_result == result);
    };

    void test_rank_filter_7()
    {
        expected_result = array;
        expected_result[0] = expected_result[1] = expected_result[2];
        expected_result[expected_result.size()  - 1] = expected_result[expected_result.size() - 2] = expected_result[expected_result.size() - 3];

        result = 0;

        lineRankOrderFilter(array, result, 3, 0.5);

        should(expected_result == result);
    };

    void test_rank_filter_8()
    {
        expected_result = reverse_array;
        expected_result[0] = expected_result[1] = expected_result[2];
        expected_result[expected_result.size()  - 1] = expected_result[expected_result.size() - 2] = expected_result[expected_result.size() - 3];

        result = 0;

        lineRankOrderFilter(reverse_array, result, 3, 0.5);

        should(expected_result == result);
    };

    void test_rank_filter_9()
    {
        expected_result = array;
        expected_result[0] = expected_result[1] = expected_result[2];
        expected_result[expected_result.size()  - 1] = expected_result[expected_result.size() - 2] = expected_result[expected_result.size() - 3];

        result = 0;

        lineRankOrderFilter(array.insertSingletonDimension(0), result.insertSingletonDimension(0), 3, 0.5, 1);

        should(expected_result == result);
    };

    void test_rank_filter_10()
    {
        expected_result = reverse_array;
        expected_result[0] = expected_result[1] = expected_result[2];
        expected_result[expected_result.size()  - 1] = expected_result[expected_result.size() - 2] = expected_result[expected_result.size() - 3];

        result = 0;

        lineRankOrderFilter(reverse_array.insertSingletonDimension(0), result.insertSingletonDimension(0), 3, 0.5, 1);

        should(expected_result == result);
    };

    void test_rank_filter_11()
    {
        expected_result_2 = array_2;

        result_2 = 0;

        lineRankOrderFilter(array_2, result_2, 0, 0.5);

        should(expected_result_2 == result_2);
    };

    void test_rank_filter_12()
    {
        expected_result_2 = reverse_array_2;

        result_2 = 0;

        lineRankOrderFilter(reverse_array_2, result_2, 0, 0.5);

        should(expected_result_2 == result_2);
    };

    void test_rank_filter_13()
    {
        expected_result_2 = array_2;
        expected_result_2.bindInner(0) = expected_result_2.bindInner(1);
        expected_result_2.bindInner(expected_result_2.shape(0) - 1) = expected_result_2.bindInner(expected_result_2.shape(0) - 2);

        result_2 = 0;

        lineRankOrderFilter(array_2, result_2, 1, 0.5);

        should(expected_result_2 == result_2);
    };

    void test_rank_filter_14()
    {
        expected_result_2 = reverse_array_2;
        expected_result_2.bindInner(0) = expected_result_2.bindInner(1);
        expected_result_2.bindInner(expected_result_2.shape(0) - 1) = expected_result_2.bindInner(expected_result_2.shape(0) - 2);

        result_2 = 0;

        lineRankOrderFilter(reverse_array_2, result_2, 1, 0.5);

        should(expected_result_2 == result_2);
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
        add( testCase( &RankFilterTest::test_rank_filter_11 ) );
        add( testCase( &RankFilterTest::test_rank_filter_12 ) );
        add( testCase( &RankFilterTest::test_rank_filter_13 ) );
        add( testCase( &RankFilterTest::test_rank_filter_14 ) );
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