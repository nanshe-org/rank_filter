#adapted from vigra source code

FIND_PACKAGE(PythonInterp)
IF(PYTHONINTERP_FOUND)
    IF(NOT PYTHON_ROOT)
        execute_process ( COMMAND ${PYTHON_EXECUTABLE} -c
                            "import sys; print sys.prefix"
                            RESULT_VARIABLE PYTHON_ROOT_NOT_FOUND
                            OUTPUT_VARIABLE PYTHON_ROOT
                            OUTPUT_STRIP_TRAILING_WHITESPACE)
        IF(NOT PYTHON_ROOT_NOT_FOUND)
            FILE(TO_CMAKE_PATH ${PYTHON_ROOT} PYTHON_ROOT)
        ELSE()
            SET(PYTHON_ROOT "PYTHON_ROOT-NOTFOUND")
        ENDIF()
    ENDIF()
    IF(NOT PYTHON_INCLUDE_DIR)
        execute_process ( COMMAND ${PYTHON_EXECUTABLE} -c
                            "import distutils; import distutils.sysconfig; print distutils.sysconfig.get_python_inc()"
                            RESULT_VARIABLE PYTHON_INCLUDE_DIR_NOT_FOUND
                            OUTPUT_VARIABLE PYTHON_INCLUDE_DIR
                            OUTPUT_STRIP_TRAILING_WHITESPACE)
        IF(NOT PYTHON_INCLUDE_DIR_NOT_FOUND)
            FILE(TO_CMAKE_PATH ${PYTHON_INCLUDE_DIR} PYTHON_INCLUDE_DIR)
        ELSE()
            SET(PYTHON_INCLUDE_DIR "PYTHON_INCLUDE_DIR-NOTFOUND")
        ENDIF()
    ENDIF()
    IF(NOT PYTHON_LIBRARY_DIR)
        execute_process ( COMMAND ${PYTHON_EXECUTABLE} -c
                            "import distutils; import distutils.sysconfig; print distutils.sysconfig.get_config_var(\"LIBDIR\")"
                            RESULT_VARIABLE PYTHON_LIBRARY_DIR_NOT_FOUND
                            OUTPUT_VARIABLE PYTHON_LIBRARY_DIR
                            OUTPUT_STRIP_TRAILING_WHITESPACE)
        IF(NOT PYTHON_LIBRARY_DIR_NOT_FOUND)
            FILE(TO_CMAKE_PATH ${PYTHON_LIBRARY_DIR} PYTHON_LIBRARY_DIR)
        ELSE()
            SET(PYTHON_LIBRARY_DIR "PYTHON_LIBRARY_DIR-NOTFOUND")
        ENDIF()
    ENDIF()
    IF(NOT PYTHON_SITE_PACKAGES)
        execute_process ( COMMAND ${PYTHON_EXECUTABLE} -c
                            "from distutils.sysconfig import get_python_lib; print get_python_lib()"
                            RESULT_VARIABLE PYTHON_SITE_PACKAGES_NOT_FOUND
                            OUTPUT_VARIABLE PYTHON_SITE_PACKAGES
                            OUTPUT_STRIP_TRAILING_WHITESPACE)
        IF(NOT PYTHON_SITE_PACKAGES_NOT_FOUND)
            FILE(TO_CMAKE_PATH ${PYTHON_SITE_PACKAGES} PYTHON_SITE_PACKAGES)
        ELSE()
            SET(PYTHON_SITE_PACKAGES "PYTHON_SITE_PACKAGES-NOTFOUND")
        ENDIF()
    ENDIF()
ELSE()
    SET(PYTHON_ROOT "PYTHON_ROOT-NOTFOUND")
    SET(PYTHON_INCLUDE_DIR "PYTHON_INCLUDE_DIR-NOTFOUND")
    SET(PYTHON_LIBRARY_DIR "PYTHON_LIBRARY_DIR-NOTFOUND")
    SET(PYTHON_SITE_PACKAGES "PYTHON_SITE_PACKAGES-NOTFOUND")
ENDIF()


IF(PYTHON_ROOT)
    SET(PYTHON_FOUND TRUE)

    IF (NOT Python_FIND_QUIETLY)
      MESSAGE(STATUS "Found Python")
      MESSAGE(STATUS "  > includes:          ${PYTHON_INCLUDE_DIR}")
      MESSAGE(STATUS "  > library path:      ${PYTHON_LIBRARY_DIR}")
    ENDIF()
ELSE()
    IF(Python_FIND_REQUIRED)
      MESSAGE(FATAL_ERROR "Could not find Numpy")
    ENDIF()
ENDIF()
