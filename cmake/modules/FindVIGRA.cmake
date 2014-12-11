# This module finds an installed Vigra package.
#
# It sets the following variables:
#  VIGRA_ROOT                      - The root path to find includes and libraries for VIGRA (not Python modules).
#  VIGRA_FOUND                     - Set to false, or undefined, if vigra isn't found.
#  VIGRA_INCLUDE_DIR               - Vigra include directory.
#  VIGRA_VIGRANUMPYCORE_LIBRARY    - Vigra's vigranumpycore library
#  VIGRANUMPY_SITEPACKAGE_DIR      - path to Vigra vigranumpycore library


# See if VIGRA_ROOT was set externally, if so use it.
if (("${VIGRA_ROOT}" STREQUAL "") OR ("${VIGRA_ROOT}" STREQUAL "VIGRA_ROOT-NOTFOUND"))
    if (NOT "$ENV{VIGRA_ROOT}" STREQUAL "")
        set(VIGRA_ROOT $ENV{VIGRA_ROOT})
    elseif (NOT "$ENV{VIGRAROOT}" STREQUAL "")
          set(VIGRA_ROOT $ENV{VIGRAROOT})
          set(ENV{VIGRA_ROOT} $ENV{VIGRA_ROOT})
    endif()
endif()

# configVersion.hxx only present, after build of Vigra
FIND_PATH(VIGRA_INCLUDE_DIR vigra/configVersion.hxx PATHS ${VIGRA_ROOT}/include ENV CPLUS_INCLUDE_PATH)

if (NOT "${VIGRA_ROOT}" STREQUAL "")
    set(VIGRA_LIBRARY_DIR ${VIGRA_ROOT}/lib)
endif()

EXECUTE_PROCESS(COMMAND ${PYTHON_EXECUTABLE} -c
                            "import vigra.vigranumpycore; print vigra.vigranumpycore.__file__"
                            RESULT_VARIABLE VIGRA_VIGRANUMPYCORE_LIBRARY_NOT_FOUND
                            OUTPUT_VARIABLE VIGRA_VIGRANUMPYCORE_LIBRARY
                            OUTPUT_STRIP_TRAILING_WHITESPACE)

IF(NOT VIGRA_VIGRANUMPYCORE_LIBRARY_NOT_FOUND)
    SET( VIGRANUMPY_SITEPACKAGE_DIR ${VIGRA_VIGRANUMPYCORE_LIBRARY} CACHE PATH "Path to Vigra's vigranumpycore library.")

    MESSAGE(STATUS "Found VIGRA")
    MESSAGE(STATUS "  > includes:                 ${VIGRA_INCLUDE_DIR}")
    MESSAGE(STATUS "  > libraries:                ${VIGRA_LIBRARY_DIR}")
    MESSAGE(STATUS "  > vigranumpy site-package:  ${VIGRANUMPY_SITEPACKAGE_DIR}")
    MESSAGE(STATUS "  > vigranumpycore library:   ${VIGRA_VIGRANUMPYCORE_LIBRARY}")
ENDIF()




# handle the QUIETLY and REQUIRED arguments and set VIGRA_FOUND to TRUE if
# all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(VIGRA DEFAULT_MSG VIGRA_ROOT VIGRA_INCLUDE_DIR VIGRA_LIBRARY_DIR VIGRANUMPY_SITEPACKAGE_DIR VIGRA_VIGRANUMPYCORE_LIBRARY )

MARK_AS_ADVANCED(VIGRA_ROOT VIGRA_INCLUDE_DIR VIGRA_LIBRARY_DIR VIGRANUMPY_SITEPACKAGE_DIR VIGRA_VIGRANUMPYCORE_LIBRARY)
