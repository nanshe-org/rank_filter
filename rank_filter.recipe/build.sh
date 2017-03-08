#
# We OVERRIDE conda's default value for MACOSX_DEPLOYMENT_TARGET,
#  because we want to link against libc++ (not stdlibc++) for C++ libraries (like vigra)
#

if [[ `uname` == 'Darwin' ]]; then
    LIBRARY_SEARCH_VAR=DYLD_FALLBACK_LIBRARY_PATH
else
    LIBRARY_SEARCH_VAR=LD_LIBRARY_PATH
fi

if [ -z "${USE_CYTHON}" ] || [ "${USE_CYTHON}" == "<UNDEFINED>" ];
then
    unset USE_CYTHON
fi
if [ -z "${CC}" ] || [ "${CC}" == "<UNDEFINED>" ];
then
    CC=$DEFAULT_CC
fi
if [ -z "${CXX}" ] || [ "${CXX}" == "<UNDEFINED>" ];
then
    CXX=$DEFAULT_CXX
fi
if [ -z "${CXX_FLAGS}" ] || [ "${CXX_FLAGS}" == "<UNDEFINED>" ];
then
    CXX_FLAGS=$DEFAULT_CXX_FLAGS
fi
if [ -z "${CXX_LDFLAGS}" ] || [ "${CXX_LDFLAGS}" == "<UNDEFINED>" ];
then
    CXX_LDFLAGS=$DEFAULT_CXX_LDFLAGS
fi

CXX_FLAGS="${CXXFLAGS} ${CXX_FLAGS}"
CXX_LDFLAGS="${LDFLAGS} ${CXX_LDFLAGS}"

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
