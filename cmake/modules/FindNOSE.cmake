#adapted from vigra source code


IF(PYTHONINTERP_FOUND)
    IF(NOT PYTHON_NOSE_CORE)
        execute_process ( COMMAND ${PYTHON_EXECUTABLE} -c
                            "import nose.core; print(nose.core.__file__)"
                            RESULT_VARIABLE PYTHON_NOSE_NOT_FOUND
                            OUTPUT_VARIABLE PYTHON_NOSE_CORE
                            OUTPUT_STRIP_TRAILING_WHITESPACE)
        IF(NOT PYTHON_NOSE_NOT_FOUND)
            FILE(TO_CMAKE_PATH ${PYTHON_NOSE_CORE} PYTHON_NOSE_CORE)
        ELSE()
            SET(PYTHON_NOSE_CORE "PYTHON_NOSE_CORE-NOTFOUND")
        ENDIF()
    ENDIF()
ELSE()
    SET(PYTHON_NOSE_CORE "PYTHON_NOSE_CORE-NOTFOUND")
ENDIF()

SET(PYTHON_NOSE_CORE ${PYTHON_NOSE_CORE}
    CACHE PATH "Path to nose.core" FORCE)

IF(PYTHON_NOSE_CORE)
    SET(NOSE_FOUND TRUE)

    IF (NOT NOSE_FIND_QUIETLY)
        MESSAGE(STATUS "Found Nose")
        MESSAGE(STATUS "  > nose.core:      ${PYTHON_NOSE_CORE}")
    ENDIF()
ELSE()
    IF(NOSE_FIND_REQUIRED)
        MESSAGE(FATAL_ERROR "Could not find Nose")
    ELSEIF(NOT NOSE_FIND_QUIETLY)
        MESSAGE(STATUS "Unable to fine Nose")
    ENDIF()
ENDIF()
