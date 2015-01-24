#!/bin/bash -v

#This script originates from the ilastik project.

git clone http://github.com/ukoethe/vigra /tmp/vigra 2> /dev/null
cd /tmp/vigra
git pull
mkdir -p /tmp/vigra/build
cd /tmp/vigra/build

cmake -DDEPENDENCY_SEARCH_PREFIX=$VIRTUAL_ENV -DCMAKE_INSTALL_PREFIX=$VIRTUAL_ENV -DCMAKE_PREFIX_PATH=$VIRTUAL_ENV -DVIGRANUMPY_LIBRARIES="${VIRTUAL_ENV}/lib/libpython2.7.so;${VIRTUAL_ENV}/lib/libboost_python.so" ..
make install
