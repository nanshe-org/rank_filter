if [[ `uname` == 'Darwin' ]]; then
    LIBRARY_SEARCH_VAR=DYLD_FALLBACK_LIBRARY_PATH
else
    LIBRARY_SEARCH_VAR=LD_LIBRARY_PATH
fi

if [ -z "${USE_CYTHON}" ] || [ "${USE_CYTHON}" == "<UNDEFINED>" ];
then
    unset USE_CYTHON
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
