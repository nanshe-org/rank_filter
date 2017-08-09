:: Configure, build, and install
mkdir build && cd build
if errorlevel 1 exit 1

cmake -G "NMake Makefiles"                         ^
      -DCMAKE_BUILD_TYPE:STRING="Release"          ^
      -DCMAKE_PREFIX_PATH:PATH="%LIBRARY_PREFIX%"  ^
      -DBOOST_ROOT:PATH="%LIBRARY_PREFIX%"         ^
      -DVIGRA_ROOT:PATH="%LIBRARY_PREFIX%"         ^
      -DPYTHON_EXECUTABLE:PATH="%PYTHON%"          ^
      "%SRC_DIR%"
if errorlevel 1 exit 1

nmake
if errorlevel 1 exit 1

nmake install
if errorlevel 1 exit 1
