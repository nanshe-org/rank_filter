#!/bin/bash -v

export VIRTUAL_ENV=$1
export PYTHON_EXECUTABLE=$2

cd /tmp
wget -O boost_1_56_0.tar.bz2 http://sourceforge.net/projects/boost/files/boost/1.56.0/boost_1_56_0.tar.bz2/download
tar -xjf boost_1_56_0.tar.bz2
cd boost_1_56_0 

./bootstrap.sh --with-libraries=container,python --with-python=$PYTHON_EXECUTABLE --prefix=$VIRTUAL_ENV
./b2
./b2 install
