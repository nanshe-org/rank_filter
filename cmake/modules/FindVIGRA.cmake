# This module finds an installed Vigra package.
#
# It sets the following variables:
#  VIGRA_ROOT                      - The root path to find includes and libraries for VIGRA (not Python modules).
#  VIGRA_FOUND                     - Set to false, or undefined, if vigra isn't found.
#  VIGRA_INCLUDE_DIR               - Vigra include directory.
#  VIGRA_VIGRANUMPYCORE_LIBRARY    - Vigra's vigranumpycore library
#  VIGRANUMPY_SITEPACKAGE_DIR      - path to Vigra vigranumpycore library


# See if VIGRA_ROOT was set externally, if so use it.
if (NOT "$ENV{VIGRA_ROOT}" STREQUAL "")
    set(VIGRA_ROOT $ENV{VIGRA_ROOT})
elseif (NOT "$ENV{VIGRAROOT}" STREQUAL "")
      set(VIGRA_ROOT $ENV{VIGRAROOT})
      set(ENV{VIGRA_ROOT} $ENV{VIGRA_ROOT})
endif()

# configVersion.hxx only present, after build of Vigra
FIND_PATH(VIGRA_INCLUDE_DIR vigra/configVersion.hxx ${VIGRA_ROOT}/include PATHS ENV CPLUS_INCLUDE_PATH)

EXECUTE_PROCESS(COMMAND ${PYTHON_EXECUTABLE} -c
                            "import vigra.vigranumpycore; print vigra.vigranumpycore.__file__"
                            RESULT_VARIABLE VIGRA_VIGRANUMPYCORE_LIBRARY_NOT_FOUND
                            OUTPUT_VARIABLE VIGRA_VIGRANUMPYCORE_LIBRARY
                            OUTPUT_STRIP_TRAILING_WHITESPACE)

IF(NOT VIGRA_VIGRANUMPYCORE_LIBRARY_NOT_FOUND)
    GET_FILENAME_COMPONENT(VIGRA_VIGRANUMPYCORE_LIBRARY_PATH ${VIGRA_VIGRANUMPYCORE_LIBRARY} PATH)
    SET( VIGRANUMPY_SITEPACKAGE_DIR ${VIGRA_VIGRANUMPYCORE_LIBRARY_PATH} CACHE PATH "Path to Vigra's vigranumpycore library.")

    MESSAGE(STATUS "Found VIGRA")
    MESSAGE(STATUS "  > vigranumpy: ${VIGRA_VIGRANUMPYCORE_LIBRARY}")
    MESSAGE(STATUS "  > includes:   ${VIGRA_INCLUDE_DIR}")
ENDIF()




# handle the QUIETLY and REQUIRED arguments and set VIGRA_FOUND to TRUE if
# all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(VIGRA DEFAULT_MSG VIGRA_ROOT VIGRA_VIGRANUMPYCORE_LIBRARY_PATH VIGRA_VIGRANUMPYCORE_LIBRARY VIGRA_INCLUDE_DIR )

MARK_AS_ADVANCED(VIGRA_ROOT VIGRA_INCLUDE_DIR VIGRA_VIGRANUMPYCORE_LIBRARY_PATH VIGRA_VIGRANUMPYCORE_LIBRARY VIGRANUMPY_SITEPACKAGE_DIR)

