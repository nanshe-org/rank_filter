###
#
#   Build and install rank_filter module in Python.
#
#
### Requires the following variables or grabs them from the environment:
#
#  VIGRA_ROOT                      - The root path to find includes and libraries for VIGRA (not Python modules).
#  BOOST_ROOT                      - The root path to find includes and libraries for Boost.
#  PYTHON_EXECUTABLE               - The Python interpreter to use (fetches all other relevant variables through it).
#
###
### Allows the following additional targets
#
#  rank_filter                      - Module to be built for Python and installed in site-packages.
#  distclean                        - Removes all CMake files (does not remove final output).
#  reset                            - Same as distclean, but also deletes the bin, slib, and lib directories.
#
###


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
                         COMMAND cmake -E remove_directory ${CMAKE_CURRENT_SOURCE_DIR}/Testing
                         COMMAND cmake -E remove ${CMAKE_CURRENT_SOURCE_DIR}/cmake_install.cmake
                         COMMAND cmake -E remove ${CMAKE_CURRENT_SOURCE_DIR}/Makefile
                         COMMAND cmake -E remove ${CMAKE_CURRENT_SOURCE_DIR}/install_manifest.txt)

# Add a target to wipe out all CMake files generated.
add_custom_target(distclean COMMAND cmake -E remove ${CMAKE_CURRENT_SOURCE_DIR}/CMakeCache.txt
                            COMMAND cmake -E remove_directory ${CMAKE_CURRENT_SOURCE_DIR}/CMakeFiles
                            COMMAND cmake -E remove ${CMAKE_CURRENT_SOURCE_DIR}/CTestTestfile.cmake
                            COMMAND cmake -E remove_directory ${CMAKE_CURRENT_SOURCE_DIR}/Testing
                            COMMAND cmake -E remove ${CMAKE_CURRENT_SOURCE_DIR}/cmake_install.cmake
                            COMMAND cmake -E remove ${CMAKE_CURRENT_SOURCE_DIR}/Makefile
                            COMMAND cmake -E remove ${CMAKE_CURRENT_SOURCE_DIR}/install_manifest.txt
                            COMMAND cmake -E remove ${CMAKE_CURRENT_SOURCE_DIR}/bin/cxxtest.out)

# Import needed CMakes for finding dependencies.
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules/)

find_package(PYTHON REQUIRED)
find_package(Boost "1.56.0" REQUIRED COMPONENTS container python)
find_package(VIGRA REQUIRED)
find_package(NUMPY REQUIRED)
find_package(NOSE)

include(CheckCXXSourceCompiles)

# Set all directories to search for includes
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
    ${PYTHON_INCLUDE_DIR}
    ${VIGRA_INCLUDE_DIR}
    ${Boost_INCLUDE_DIRS}
    ${PYTHON_NUMPY_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${VIGRA_VIGRANUMPYCORE_LIBRARY_PATH}
)

# Set all directories to search for libraries
link_directories(${PYTHON_LIBRARY_DIR} ${Boost_LIBRARY_DIRS})

# Use C++11
set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

# Build binary for running C++ unitests
add_executable(cxxtest ${CMAKE_CURRENT_SOURCE_DIR}/test/test_rank_filter)
target_link_libraries(cxxtest ${Boost_LIBRARIES})
set_target_properties(cxxtest PROPERTIES SUFFIX ".out" PREFIX "")

# Run C++ unitests binary
add_custom_target(check COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/bin/cxxtest.out DEPENDS cxxtest)

# Build Python module with Python bindings to the C++ library.
add_library(rank_filter SHARED ${CMAKE_CURRENT_SOURCE_DIR}/src/rank_filter_py.cxx)
target_link_libraries(rank_filter ${PYTHON_LIBRARY} ${Boost_LIBRARIES} ${VIGRA_VIGRANUMPYCORE_LIBRARY})
set_target_properties(rank_filter PROPERTIES SUFFIX ".so" PREFIX "")

# Ensure the C++ unitests were run before building the Python module.
add_dependencies(rank_filter check)

# Run nosetest on completion to ensure all works and is accurate
add_test(NAME nosetest COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test/run_nosetest.py)

# Install the module in the Python site-packages folder.
install(TARGETS rank_filter DESTINATION ${PYTHON_SITE_PACKAGES})
#install(FILES include/rank_filter.hxx DESTINATION ${VIGRA_INCLUDE_DIR})
