if [ ! -z "${EXT_CC}" ] && [ "${EXT_CC}" != "<UNDEFINED>" ];
then
    CC="${EXT_CC}"
fi

if [ ! -z "${EXT_CXX}" ] && [ "${EXT_CXX}" != "<UNDEFINED>" ];
then
    CXX="${EXT_CXX}"
fi

# CONFIGURE
mkdir build
cd build

cmake "${SRC_DIR}"\
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
        -DVIGRA_ROOT="${PREFIX}" \
\
        -DPYTHON_EXECUTABLE="${PYTHON}" \
\

# BUILD (in parallel)
make -j${CPU_COUNT}

# "install" to the build prefix (conda will relocate these files afterwards)
make install
