#
# We OVERRIDE conda's default value for MACOSX_DEPLOYMENT_TARGET,
#  because we want to link against libc++ (not stdlibc++) for C++ libraries (like vigra)
#

if [[ `uname` == 'Darwin' ]]; then
    export MACOSX_DEPLOYMENT_TARGET=10.7
    LIBRARY_SEARCH_VAR=DYLD_FALLBACK_LIBRARY_PATH
else
    LIBRARY_SEARCH_VAR=LD_LIBRARY_PATH
fi

CXX_FLAGS="${CXXFLAGS} ${CXX_FLAGS} -std=c++11"
CXX_LDFLAGS="${LDFLAGS} ${CXX_LDFLAGS} -std=c++11"

# CONFIGURE
SRC=$(pwd)
mkdir -pv build
cd build
BLD=$(pwd)

cmake ${SRC}\
        -DCMAKE_MACOSX_RPATH=false \
\
        -DCMAKE_PREFIX_PATH="${PREFIX}" \
\
        -DCMAKE_SHARED_LINKER_FLAGS="${CXX_LDFLAGS}" \
\
        -DCMAKE_CXX_LINK_FLAGS="${CXX_FLAGS}" \
        -DCMAKE_CXX_FLAGS="${CXX_FLAGS}" \
\
        -DBOOST_ROOT="${PREFIX}" \
        -DVIGRA_ROOT="${PREFIX}" \
\
        -DPYTHON_EXECUTABLE="${PYTHON}" \
\

# BUILD (in parallel)
eval ${LIBRARY_SEARCH_VAR}=$PREFIX/lib make -j${CPU_COUNT}

# "install" to the build prefix (conda will relocate these files afterwards)
eval ${LIBRARY_SEARCH_VAR}=$PREFIX/lib make install
