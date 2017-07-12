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
                         COMMAND cmake -E remove ${CMAKE_CURRENT_BINARY_DIR}/CMakeCache.txt
                         COMMAND cmake -E remove_directory ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles
                         COMMAND cmake -E remove ${CMAKE_CURRENT_BINARY_DIR}/CTestTestfile.cmake
                         COMMAND cmake -E remove_directory ${CMAKE_CURRENT_BINARY_DIR}/Testing
                         COMMAND cmake -E remove ${CMAKE_CURRENT_BINARY_DIR}/cmake_install.cmake
                         COMMAND cmake -E remove ${CMAKE_CURRENT_BINARY_DIR}/Makefile
                         COMMAND cmake -E remove ${CMAKE_CURRENT_BINARY_DIR}/install_manifest.txt
                         COMMAND cmake -E remove_directory ${CMAKE_CURRENT_SOURCE_DIR}/build
                         COMMAND cmake -E remove_directory ${CMAKE_CURRENT_SOURCE_DIR}/dist
                         COMMAND cmake -E remove_directory ${CMAKE_CURRENT_SOURCE_DIR}/rank_filter.egg-info
                         COMMAND cmake -E remove ${CMAKE_CURRENT_SOURCE_DIR}/src/rank_filter.cpp
                         COMMAND cmake -E remove ${CMAKE_CURRENT_SOURCE_DIR}/rank_filter*.so)

# Add a target to wipe out all CMake files generated.
add_custom_target(distclean COMMAND cmake -E remove ${CMAKE_CURRENT_BINARY_DIR}/CMakeCache.txt
                            COMMAND cmake -E remove_directory ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles
                            COMMAND cmake -E remove ${CMAKE_CURRENT_BINARY_DIR}/CTestTestfile.cmake
                            COMMAND cmake -E remove_directory ${CMAKE_CURRENT_BINARY_DIR}/Testing
                            COMMAND cmake -E remove ${CMAKE_CURRENT_BINARY_DIR}/cmake_install.cmake
                            COMMAND cmake -E remove ${CMAKE_CURRENT_BINARY_DIR}/Makefile
                            COMMAND cmake -E remove ${CMAKE_CURRENT_BINARY_DIR}/install_manifest.txt
                            COMMAND cmake -E remove ${CMAKE_CURRENT_BINARY_DIR}/bin/cxxtest_base.out
                            COMMAND cmake -E remove ${CMAKE_CURRENT_BINARY_DIR}/bin/cxxtest_vigra.out
                            COMMAND cmake -E remove_directory ${CMAKE_CURRENT_SOURCE_DIR}/build
                            COMMAND cmake -E remove_directory ${CMAKE_CURRENT_SOURCE_DIR}/dist
                            COMMAND cmake -E remove_directory ${CMAKE_CURRENT_SOURCE_DIR}/rank_filter.egg-info
                            COMMAND cmake -E remove ${CMAKE_CURRENT_SOURCE_DIR}/src/rank_filter.cpp
                            COMMAND cmake -E remove ${CMAKE_CURRENT_SOURCE_DIR}/rank_filter*.so)

# Import needed CMakes for finding dependencies.
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/)

find_package(PYTHON REQUIRED)
find_package(Boost "1.56.0" REQUIRED COMPONENTS container)
find_package(CYTHON REQUIRED)
find_package(VIGRA)
find_package(NUMPY REQUIRED)

include(CheckCXXSourceCompiles)

# Set all directories to search for includes
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
    ${PYTHON_INCLUDE_DIR}
    ${Boost_INCLUDE_DIRS}
    ${PYTHON_NUMPY_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
)


# Set all directories to search for libraries
link_directories(${PYTHON_LIBRARY_DIR} ${Boost_LIBRARY_DIRS})

# Build binary for running base API C++ unitests
add_executable(cxxtest_base ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_rank_filter_base)
target_link_libraries(cxxtest_base ${Boost_CONTAINER_LIBRARY})
set_target_properties(cxxtest_base PROPERTIES SUFFIX ".out" PREFIX "")

# Build binary for running base API C++ unitests
if(${VIGRA_FOUND})
    add_executable(cxxtest_vigra ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_rank_filter_vigra)
    target_compile_options(cxxtest_vigra PUBLIC "-std=c++11")
    target_include_directories(cxxtest_vigra PUBLIC ${VIGRA_INCLUDE_DIR})
    target_link_libraries(cxxtest_vigra ${Boost_CONTAINER_LIBRARY})
    set_target_properties(cxxtest_vigra PROPERTIES SUFFIX ".out" PREFIX "")
endif()

# Run C++ unitests binary
if(${VIGRA_FOUND})
    add_custom_target(check COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/cxxtest_base.out COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/cxxtest_vigra.out DEPENDS cxxtest_base cxxtest_vigra)
else()
    add_custom_target(check COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/cxxtest_base.out DEPENDS cxxtest_base)
endif()

# Build Python module with Python bindings to the C++ library.
add_custom_target(
    rank_filter
    ALL
    COMMAND ${PYTHON_EXECUTABLE} setup.py test
    DEPENDS check
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

# Ensure the C++ unitests were run before building the Python module.
add_dependencies(rank_filter check)

# Run unittest on completion to ensure all works and is accurate.
add_test(NAME unittest COMMAND ${PYTHON_EXECUTABLE} -m unittest discover -s ${CMAKE_CURRENT_SOURCE_DIR} WORKING_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

# Install the module in the Python site-packages folder.
install(CODE "execute_process(COMMAND ${PYTHON_EXECUTABLE} setup.py install WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})")
#install(FILES include/rank_filter.hxx DESTINATION ${VIGRA_INCLUDE_DIR})
