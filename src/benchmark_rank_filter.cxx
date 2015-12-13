#include <random>

#include "rank_filter.hxx"




int main(int argc, char** argv)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::normal_distribution<float> dist;

    vigra::MultiArray<3, float>::difference_type shape(100, 101, 102);
    vigra::MultiArray<3, float> input(shape);
    vigra::MultiArray<3, float> output(shape);

    for (unsigned long i_0 = 0; i_0 < shape[0]; i_0++)
    {
        for (unsigned long i_1 = 0; i_1 < shape[1]; i_1++)
        {
            for (unsigned long i_2 = 0; i_2 < shape[2]; i_2++)
            {
                input(i_0, i_1, i_2) = dist(gen);
            }
        }
    }

    lineRankOrderFilter(input, output, 25L, 0.5, 0);

    return(0);
}
