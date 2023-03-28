#!/bin/bash
rootdir=$(pwd)
mkdir -p $rootdir/build
cd $rootdir/build
cmake ..
make
cd $rootdir/build/shaders
make

