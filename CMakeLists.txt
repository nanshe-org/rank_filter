project(rank_filter)

cmake_minimum_required(VERSION 2.8)

enable_testing()

# Name all subdirectories relative to the build directory
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/slib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)

# Create subdirectories for all outputs in the build directory
file(MAKE_DIRECTORY ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
file(MAKE_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

# Returns the repo to the original state (i.e no CMake files, no output).
add_custom_target(reset  COMMAND cmake -E remove_directory ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}
                         COMMAND cmake -E remove_directory ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
                         COMMAND cmake -E remove_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
                         COMMAND cmake -E remove ${CMAKE_CURRENT_SOURCE_DIR}/CMakeCache.txt
                         COMMAND cmake -E remove_directory ${CMAKE_CURRENT_SOURCE_DIR}/CMakeFiles
                         COMMAND cmake -E remove ${CMAKE_CURRENT_SOURCE_DIR}/CTestTestfile.cmake
                         COMMAND cmake -E remove ${CMAKE_CURRENT_SOURCE_DIR}/cmake_install.cmake
                         COMMAND cmake -E remove ${CMAKE_CURRENT_SOURCE_DIR}/Makefile)

# Add a target to wipe out all CMake files generated.
add_custom_target(distclean COMMAND cmake -E remove ${CMAKE_CURRENT_SOURCE_DIR}/CMakeCache.txt
                            COMMAND cmake -E remove_directory ${CMAKE_CURRENT_SOURCE_DIR}/CMakeFiles
                            COMMAND cmake -E remove ${CMAKE_CURRENT_SOURCE_DIR}/CTestTestfile.cmake
                            COMMAND cmake -E remove ${CMAKE_CURRENT_SOURCE_DIR}/cmake_install.cmake
                            COMMAND cmake -E remove ${CMAKE_CURRENT_SOURCE_DIR}/Makefile)


set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules/)

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
    ${VIGRA_VIGRANUMPYCORE_LIBRARY_PATH}
)

link_directories(${PYTHON_LIBRARY_DIR} ${Boost_LIBRARY_DIRS})

add_library(python_rank_filter SHARED python_rank_filter.cxx)

target_link_libraries(python_rank_filter ${PYTHON_LIBRARY} ${Boost_LIBRARIES} ${VIGRA_VIGRANUMPYCORE_LIBRARY})

# Use C++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
