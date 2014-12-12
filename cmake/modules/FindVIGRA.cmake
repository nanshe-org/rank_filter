# This module finds an installed Vigra package.
#
# It sets the following variables:
#  VIGRA_FOUND              - Set to false, or undefined, if vigra isn't found.
#  VIGRA_INCLUDE_DIR        - Vigra include directory.
#  VIGRA_VIGRANUMPYCORE_LIBRARY      - Vigra's impex library
#  VIGRA_VIGRANUMPYCORE_LIBRARY_DIR  - path to Vigra impex library


# configVersion.hxx only present, after build of Vigra
FIND_PATH(VIGRA_INCLUDE_DIR vigra/configVersion.hxx PATHS $ENV{VIGRA_ROOT}/include ENV CPLUS_INCLUDE_PATH)

EXECUTE_PROCESS(COMMAND ${PYTHON_EXECUTABLE} -c
                            "import vigra.vigranumpycore; print vigra.vigranumpycore.__file__"
                            RESULT_VARIABLE VIGRA_VIGRANUMPYCORE_LIBRARY_NOT_FOUND
                            OUTPUT_VARIABLE VIGRA_VIGRANUMPYCORE_LIBRARY
                            OUTPUT_STRIP_TRAILING_WHITESPACE)

IF(NOT VIGRA_VIGRANUMPYCORE_LIBRARY_NOT_FOUND)
    GET_FILENAME_COMPONENT(VIGRA_VIGRANUMPYCORE_LIBRARY_PATH ${VIGRA_VIGRANUMPYCORE_LIBRARY} PATH)
    SET( VIGRA_VIGRANUMPYCORE_LIBRARY_DIR ${VIGRA_VIGRANUMPYCORE_LIBRARY_PATH} CACHE PATH "Path to Vigra's vigranumpycore library.")

    MESSAGE(STATUS "Found VIGRA")
    MESSAGE(STATUS "  > vigranumpy: ${VIGRA_VIGRANUMPYCORE_LIBRARY}")
    MESSAGE(STATUS "  > includes:   ${VIGRA_INCLUDE_DIR}")
ENDIF()



EXECUTE_PROCESS ( COMMAND python -c "from distutils.sysconfig import get_python_lib; print get_python_lib()" OUTPUT_VARIABLE PYTHON_SITE_PACKAGES OUTPUT_STRIP_TRAILING_WHITESPACE)

# handle the QUIETLY and REQUIRED arguments and set VIGRA_FOUND to TRUE if
# all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(VIGRA DEFAULT_MSG VIGRA_VIGRANUMPYCORE_LIBRARY_PATH VIGRA_VIGRANUMPYCORE_LIBRARY VIGRA_INCLUDE_DIR )

MARK_AS_ADVANCED( VIGRA_INCLUDE_DIR VIGRA_VIGRANUMPYCORE_LIBRARY_PATH VIGRA_VIGRANUMPYCORE_LIBRARY VIGRA_VIGRANUMPYCORE_LIBRARY_DIR)
