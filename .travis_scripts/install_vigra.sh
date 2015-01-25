#!/bin/bash -v

export VIRTUAL_ENV=$1
export PYTHON_SHARED_OBJECT=$2

git clone http://github.com/ukoethe/vigra /tmp/vigra 2> /dev/null
cd /tmp/vigra
git pull
mkdir -p /tmp/vigra/build
cd /tmp/vigra/build

cmake -DDEPENDENCY_SEARCH_PREFIX=$VIRTUAL_ENV -DCMAKE_INSTALL_PREFIX=$VIRTUAL_ENV -DCMAKE_PREFIX_PATH=$VIRTUAL_ENV -DVIGRANUMPY_LIBRARIES="${PYTHON_SHARED_OBJECT};${VIRTUAL_ENV}/lib/libboost_python.so" -DWITH_BOOST_GRAPH=0 ..
make install
