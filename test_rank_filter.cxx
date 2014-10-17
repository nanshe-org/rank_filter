#include "vigra/unittest.hxx"

#include "rank_filter.hxx"

class RankFilterTest
{
private:

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

    RankFilterTest() : size_1(size), array_1(size_1), reverse_array_1(size_1), expected_result_1(size_1), result_1(size_1),
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

    ~RankFilterTest()
    {
    };

    void test_rank_filter_1()
    {
        expected_result_1 = array_1;

        result_1 = 0;

        lineRankOrderFilter(array_1, result_1, 0, 0.5);

        should(expected_result_1 == result_1);
    };

    void test_rank_filter_2()
    {
        expected_result_1 = reverse_array_1;

        result_1 = 0;

        lineRankOrderFilter(reverse_array_1, result_1, 0, 0.5);

        should(expected_result_1 == result_1);
    };

    void test_rank_filter_3()
    {
        expected_result_1 = array_1;
        expected_result_1[0] = expected_result_1[1];
        expected_result_1[expected_result_1.size()  - 1] = expected_result_1[expected_result_1.size() - 2];

        result_1 = 0;

        lineRankOrderFilter(array_1, result_1, 1, 0.5);

        should(expected_result_1 == result_1);
    };

    void test_rank_filter_4()
    {
        expected_result_1 = reverse_array_1;
        expected_result_1[0] = expected_result_1[1];
        expected_result_1[expected_result_1.size()  - 1] = expected_result_1[expected_result_1.size() - 2];

        result_1 = 0;

        lineRankOrderFilter(reverse_array_1, result_1, 1, 0.5);

        should(expected_result_1 == result_1);
    };

    void test_rank_filter_5()
    {
        expected_result_1 = array_1;
        expected_result_1[0] = expected_result_1[1];
        expected_result_1[expected_result_1.size()  - 1] = expected_result_1[expected_result_1.size() - 2];

        result_1 = 0;

        lineRankOrderFilter(array_1, result_1, 2, 0.5);

        should(expected_result_1 == result_1);
    };

    void test_rank_filter_6()
    {
        expected_result_1 = reverse_array_1;
        expected_result_1[0] = expected_result_1[1];
        expected_result_1[expected_result_1.size()  - 1] = expected_result_1[expected_result_1.size() - 2];

        result_1 = 0;

        lineRankOrderFilter(reverse_array_1, result_1, 2, 0.5);

        should(expected_result_1 == result_1);
    };

    void test_rank_filter_7()
    {
        expected_result_1 = array_1;
        expected_result_1[0] = expected_result_1[1] = expected_result_1[2];
        expected_result_1[expected_result_1.size()  - 1] = expected_result_1[expected_result_1.size() - 2] = expected_result_1[expected_result_1.size() - 3];

        result_1 = 0;

        lineRankOrderFilter(array_1, result_1, 3, 0.5);

        should(expected_result_1 == result_1);
    };

    void test_rank_filter_8()
    {
        expected_result_1 = reverse_array_1;
        expected_result_1[0] = expected_result_1[1] = expected_result_1[2];
        expected_result_1[expected_result_1.size()  - 1] = expected_result_1[expected_result_1.size() - 2] = expected_result_1[expected_result_1.size() - 3];

        result_1 = 0;

        lineRankOrderFilter(reverse_array_1, result_1, 3, 0.5);

        should(expected_result_1 == result_1);
    };

    void test_rank_filter_9()
    {
        expected_result_1 = array_1;
        expected_result_1[0] = expected_result_1[1] = expected_result_1[2];
        expected_result_1[expected_result_1.size()  - 1] = expected_result_1[expected_result_1.size() - 2] = expected_result_1[expected_result_1.size() - 3];

        result_1 = 0;

        lineRankOrderFilter(array_1.insertSingletonDimension(0), result_1.insertSingletonDimension(0), 3, 0.5, 1);

        should(expected_result_1 == result_1);
    };

    void test_rank_filter_10()
    {
        expected_result_1 = reverse_array_1;
        expected_result_1[0] = expected_result_1[1] = expected_result_1[2];
        expected_result_1[expected_result_1.size()  - 1] = expected_result_1[expected_result_1.size() - 2] = expected_result_1[expected_result_1.size() - 3];

        result_1 = 0;

        lineRankOrderFilter(reverse_array_1.insertSingletonDimension(0), result_1.insertSingletonDimension(0), 3, 0.5, 1);

        should(expected_result_1 == result_1);
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

    void test_rank_filter_15()
    {
        expected_result_2 = array_2;
        expected_result_2.bindOuter(0) = expected_result_2.bindOuter(1);
        expected_result_2.bindOuter(expected_result_2.shape(0) - 1) = expected_result_2.bindOuter(expected_result_2.shape(0) - 2);

        result_2 = 0;

        lineRankOrderFilter(array_2, result_2, 1, 0.5, 1);

        should(expected_result_2 == result_2);
    };

    void test_rank_filter_16()
    {
        expected_result_2 = reverse_array_2;
        expected_result_2.bindOuter(0) = expected_result_2.bindOuter(1);
        expected_result_2.bindOuter(expected_result_2.shape(0) - 1) = expected_result_2.bindOuter(expected_result_2.shape(0) - 2);

        result_2 = 0;

        lineRankOrderFilter(reverse_array_2, result_2, 1, 0.5, 1);

        should(expected_result_2 == result_2);
    };

    void test_rank_filter_17()
    {
        expected_result_2 = reverse_array_2;
        expected_result_2.bindOuter(0) = expected_result_2.bindOuter(1);
        expected_result_2.bindOuter(expected_result_2.shape(0) - 1) = expected_result_2.bindOuter(expected_result_2.shape(0) - 2);

        result_2 = reverse_array_2;

        lineRankOrderFilter(result_2, result_2, 1, 0.5, 1);

        should(expected_result_2 == result_2);
    };

    void test_rank_filter_18()
    {
        for (size_t i = 0; i < array_1.size(); i++)
        {
            expected_result_1[i] = (i < 5) ? array_1[5] : array_1[4];
        }

        result_1 = 0;

        lineRankOrderFilter(array_1, result_1, size - 1, 0.5, 1);

        should(expected_result_1 == result_1);
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
        add( testCase( &RankFilterTest::test_rank_filter_15 ) );
        add( testCase( &RankFilterTest::test_rank_filter_16 ) );
        add( testCase( &RankFilterTest::test_rank_filter_17 ) );
        add( testCase( &RankFilterTest::test_rank_filter_18 ) );
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