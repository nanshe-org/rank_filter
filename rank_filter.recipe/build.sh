#
# We OVERRIDE conda's default value for MACOSX_DEPLOYMENT_TARGET,
#  because we want to link against libc++ (not stdlibc++) for C++ libraries (like vigra)
#

if [[ `uname` == 'Darwin' ]]; then
    export MACOSX_DEPLOYMENT_TARGET=10.7
    LIBRARY_SEARCH_VAR=DYLD_FALLBACK_LIBRARY_PATH
    DEFAULT_CC="clang"
    DEFAULT_CXX="clang++"
    DEFAULT_CXX_FLAGS="-stdlib=libc++"
    DEFAULT_CXX_LDFLAGS="-stdlib=libc++"
else
    LIBRARY_SEARCH_VAR=LD_LIBRARY_PATH
    DEFAULT_CC="gcc"
    DEFAULT_CXX="g++"
    DEFAULT_CXX_FLAGS=""
    DEFAULT_CXX_LDFLAGS=""
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

CXX_FLAGS="${CXXFLAGS} ${CXX_FLAGS} -std=c++11"
CXX_LDFLAGS="${LDFLAGS} ${CXX_LDFLAGS} -std=c++11"

# Build and install
eval ${LIBRARY_SEARCH_VAR}=$PREFIX/lib ${PYTHON} setup.py build
eval ${LIBRARY_SEARCH_VAR}=$PREFIX/lib ${PYTHON} setup.py test
eval ${LIBRARY_SEARCH_VAR}=$PREFIX/lib ${PYTHON} setup.py install

git clean -fdx
