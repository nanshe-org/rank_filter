# Get commonly needed env vars
RANK_FILTER_CXX_FLAGS="${CXXFLAGS}"
RANK_FILTER_LDFLAGS="${CXX_LDFLAGS}"

if [[ `uname` == 'Darwin' ]]; then
    LIBRARY_SEARCH_VAR=DYLD_FALLBACK_LIBRARY_PATH
    CXXFLAGS="${CXXFLAGS} -stdlib=libc++"
    CXX_LDFLAGS="${LDFLAGS} -stdlib=libc++"
else
    LIBRARY_SEARCH_VAR=LD_LIBRARY_PATH
    CXXFLAGS="${CXXFLAGS}"
    CXX_LDFLAGS="${LDFLAGS}"
fi

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
        -DCMAKE_SHARED_LINKER_FLAGS="${RANK_FILTER_LDFLAGS}" \
\
        -DCMAKE_CXX_LINK_FLAGS="${RANK_FILTER_CXX_FLAGS}" \
        -DCMAKE_CXX_FLAGS="${RANK_FILTER_CXX_FLAGS}" \
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
