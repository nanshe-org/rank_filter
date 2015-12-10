#define PY_ARRAY_UNIQUE_SYMBOL rank_filter_PyArray_API
//#define NO_IMPORT_ARRAY


#include <iostream>
#include <string>
#include <utility>

#include "rank_filter.hxx"

#include <Python.h>
#include <boost/python.hpp>
#include <vigra/numpy_array.hxx>
#include <vigra/numpy_array_converters.hxx>


namespace rank_filter
{

    template < unsigned int N, class SrcPixelType >
    vigra::NumpyAnyArray pythonLineRankOrderFilter(const vigra::NumpyArray< N, vigra::Singleband<SrcPixelType> > & image,
            unsigned long half_length, double rank, int axis = N - 1,
            vigra::NumpyArray< N, vigra::Singleband<SrcPixelType> > res = boost::python::object())
    {
        std::string description("rank order filter over 1-Dimension, axis=");
        description += vigra::asString(axis);

        vigra_precondition((-static_cast<int>(N) <= axis) && (axis < static_cast<int>(N)),
                "lineRankOrderFilter(): Axis out of range.");

        if (axis < 0)
        {
            axis += N;
        }

        vigra_precondition(0 <= half_length,
                "lineRankOrderFilter(): Window must be non-negative.");

        vigra_precondition((half_length + 1) <= image.shape(axis),
                "lineRankOrderFilter(): Window must be no bigger than the image.");

        res.reshapeIfEmpty(image.taggedShape().setChannelDescription(description),
                "lineRankOrderFilter(): Output array has wrong shape.");

        {
            vigra::PyAllowThreads _pythread;

            rank_filter::lineRankOrderFilter(image, res, half_length, rank, static_cast<unsigned int>(axis));
        }
        return(res);
    }


    void defineRankFilter()
    {
        using namespace boost::python;

        docstring_options doc_options(true, true, false);

        def("lineRankOrderFilter",
                vigra::registerConverters(&pythonLineRankOrderFilter<1, float>),
                (arg("image"), arg("half_length"), arg("rank"), arg("axis")=(1-1), arg("out")=object()),
                "Convolution along a single dimension of a 1D scalar or multiband image. "
                        "'kernel' must be an instance of Kernel1D.\n"
                        "\n"
                        "For details see convolveMultiArrayOneDimension_ in the vigra C++ documentation.\n");

        def("lineRankOrderFilter",
                vigra::registerConverters(&pythonLineRankOrderFilter<2, float>),
                (arg("image"), arg("half_length"), arg("rank"), arg("axis")=(2-1), arg("out")=object()),
                "Convolution along a single dimension of a 2D scalar or multiband image. "
                        "'kernel' must be an instance of Kernel1D.\n"
                        "\n"
                        "For details see convolveMultiArrayOneDimension_ in the vigra C++ documentation.\n");

        def("lineRankOrderFilter",
                vigra::registerConverters(&pythonLineRankOrderFilter<3, float>),
                (arg("image"), arg("half_length"), arg("rank"), arg("axis")=(3-1), arg("out")=object()),
                "Convolution along a single dimension of a 3D scalar or multiband image. "
                        "'kernel' must be an instance of Kernel1D.\n"
                        "\n"
                        "For details see convolveMultiArrayOneDimension_ in the vigra C++ documentation.\n");

        def("lineRankOrderFilter",
                vigra::registerConverters(&pythonLineRankOrderFilter<4, float>),
                (arg("image"), arg("half_length"), arg("rank"), arg("axis")=(4-1), arg("out")=object()),
                "Convolution along a single dimension of a 4D scalar or multiband image. "
                        "'kernel' must be an instance of Kernel1D.\n"
                        "\n"
                        "For details see convolveMultiArrayOneDimension_ in the vigra C++ documentation.\n");

        def("lineRankOrderFilter",
                vigra::registerConverters(&pythonLineRankOrderFilter<5, float>),
                (arg("image"), arg("half_length"), arg("rank"), arg("axis")=(5-1), arg("out")=object()),
                "Convolution along a single dimension of a 5D scalar or multiband image. "
                        "'kernel' must be an instance of Kernel1D.\n"
                        "\n"
                        "For details see convolveMultiArrayOneDimension_ in the vigra C++ documentation.\n");

        def("lineRankOrderFilter",
                vigra::registerConverters(&pythonLineRankOrderFilter<1, double>),
                (arg("image"), arg("half_length"), arg("rank"), arg("axis")=(1-1), arg("out")=object()),
                "Convolution along a single dimension of a 1D scalar or multiband image. "
                        "'kernel' must be an instance of Kernel1D.\n"
                        "\n"
                        "For details see convolveMultiArrayOneDimension_ in the vigra C++ documentation.\n");

        def("lineRankOrderFilter",
                vigra::registerConverters(&pythonLineRankOrderFilter<2, double>),
                (arg("image"), arg("half_length"), arg("rank"), arg("axis")=(2-1), arg("out")=object()),
                "Convolution along a single dimension of a 2D scalar or multiband image. "
                        "'kernel' must be an instance of Kernel1D.\n"
                        "\n"
                        "For details see convolveMultiArrayOneDimension_ in the vigra C++ documentation.\n");

        def("lineRankOrderFilter",
                vigra::registerConverters(&pythonLineRankOrderFilter<3, double>),
                (arg("image"), arg("half_length"), arg("rank"), arg("axis")=(3-1), arg("out")=object()),
                "Convolution along a single dimension of a 3D scalar or multiband image. "
                        "'kernel' must be an instance of Kernel1D.\n"
                        "\n"
                        "For details see convolveMultiArrayOneDimension_ in the vigra C++ documentation.\n");

        def("lineRankOrderFilter",
                vigra::registerConverters(&pythonLineRankOrderFilter<4, double>),
                (arg("image"), arg("half_length"), arg("rank"), arg("axis")=(4-1), arg("out")=object()),
                "Convolution along a single dimension of a 4D scalar or multiband image. "
                        "'kernel' must be an instance of Kernel1D.\n"
                        "\n"
                        "For details see convolveMultiArrayOneDimension_ in the vigra C++ documentation.\n");

        def("lineRankOrderFilter",
                vigra::registerConverters(&pythonLineRankOrderFilter<5, double>),
                (arg("image"), arg("half_length"), arg("rank"), arg("axis")=(5-1), arg("out")=object()),
                "Convolution along a single dimension of a 5D scalar or multiband image. "
                        "'kernel' must be an instance of Kernel1D.\n"
                        "\n"
                        "For details see convolveMultiArrayOneDimension_ in the vigra C++ documentation.\n");
    }

}


BOOST_PYTHON_MODULE_INIT(rank_filter)
{
    vigra::import_vigranumpy();
    rank_filter::defineRankFilter();
}
