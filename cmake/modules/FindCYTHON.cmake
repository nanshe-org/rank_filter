#adapted from vigra source code


IF(PYTHONINTERP_FOUND)
    IF(NOT PYTHON_CYTHON)
        execute_process ( COMMAND ${PYTHON_EXECUTABLE} -c
                            "import cython; print(cython.__file__)"
                            RESULT_VARIABLE PYTHON_CYTHON_NOT_FOUND
                            OUTPUT_VARIABLE PYTHON_CYTHON
                            OUTPUT_STRIP_TRAILING_WHITESPACE)
        IF(NOT PYTHON_CYTHON_NOT_FOUND)
            FILE(TO_CMAKE_PATH ${PYTHON_CYTHON} PYTHON_CYTHON)
        ELSE()
            SET(PYTHON_CYTHON "PYTHON_CYTHON-NOTFOUND")
        ENDIF()
    ENDIF()
ELSE()
    SET(PYTHON_CYTHON "PYTHON_CYTHON-NOTFOUND")
ENDIF()

SET(PYTHON_CYTHON ${PYTHON_CYTHON}
    CACHE PATH "Path to cython" FORCE)

IF(PYTHON_CYTHON)
    SET(CYTHON_FOUND TRUE)

    IF (NOT CYTHON_FIND_QUIETLY)
        MESSAGE(STATUS "Found Cython")
        MESSAGE(STATUS "  > cython:      ${PYTHON_CYTHON}")
    ENDIF()
ELSE()
    IF(CYTHON_FIND_REQUIRED)
        MESSAGE(FATAL_ERROR "Could not find Cython")
    ELSEIF(NOT CYTHON_FIND_QUIETLY)
        MESSAGE(STATUS "Unable to fine Cython")
    ENDIF()
ENDIF()
