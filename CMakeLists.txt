project(rank_filter)

cmake_minimum_required(VERSION 2.8)

enable_testing()

set(CMAKE_MODULE_PATH cmake/modules/)

set(BOOST_ROOT /xopt_ilastik/local/)
set(VIGRA_INCLUDE_DIR /xopt_ilastik/local/include/vigra/)
set(VIGRA_IMPEX_LIBRARY /xopt_ilastik/local/lib/libvigraimpex.dylib)
set(PYTHON_EXECUTABLE /xopt_ilastik/local/Frameworks/Python.framework/Versions/2.7/bin/python2.7)

find_package(Boost "1.56.0" REQUIRED COMPONENTS container python)
find_package(VIGRA REQUIRED)

find_package(PYTHON REQUIRED)
find_package(NUMPY REQUIRED)

include(CheckCXXSourceCompiles)

include_directories(
    ${PYTHON_INCLUDE_DIR}
    ${VIGRA_INCLUDE_DIR}
    ${Boost_INCLUDE_DIRS}
    ${PYTHON_NUMPY_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

link_directories(${PYTHON_LIBRARY_DIR} ${Boost_LIBRARY_DIRS})

add_library(python_rank_filter SHARED python_rank_filter.cxx)
target_link_libraries(python_rank_filter "python2.7" ${Boost_LIBRARIES} )
