#!/bin/bash

# Override the compiler
if [ ! -z "${EXT_CC}" ];
then
    CC="${EXT_CC}"
fi

if [ ! -z "${EXT_CXX}" ];
then
    CXX="${EXT_CXX}"
fi

# Configure, build, and install
mkdir build && cd build
cmake "${SRC_DIR}" \
        -DCMAKE_MACOSX_RPATH=false \
\
        -DCMAKE_PREFIX_PATH="${PREFIX}" \
\
        -DCMAKE_SHARED_LINKER_FLAGS="${LDFLAGS} -Wl,-rpath,${PREFIX}/lib -L${PREFIX}/lib" \
\
        -DCMAKE_CXX_LINK_FLAGS="${CXXFLAGS} -Wl,-rpath,${PREFIX}/lib -L${PREFIX}/lib" \
        -DCMAKE_CXX_FLAGS="${CXXFLAGS} -Wl,-rpath,${PREFIX}/lib -L${PREFIX}/lib" \
\
        -DBOOST_ROOT="${PREFIX}" \
\
        -DPYTHON_EXECUTABLE="${PYTHON}" \

make -j${CPU_COUNT}

make install
