#!/bin/bash -v

#This script originates from the ilastik project.

wget -O boost_1_56_0.tar.bz2 http://sourceforge.net/projects/boost/files/boost/1.56.0/boost_1_56_0.tar.bz2/download

./bootstrap.sh --with-libraries=container,python 
./b2
./b2 install