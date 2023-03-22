#!/bin/bash
rootdir=$(pwd)
if test -f 3rd-party/glad/build/libglad.a && test -f build/lib/libglad.a; then
	mkdir -p build
	cd build
	cmake ..
	make
else
	cd 3rd-party/glad
	mkdir -p build
	cd build 
	cmake ..
	make
	cd $rootdir
	mkdir -p build
	cd build
	cmake ..
	cp  $rootdir/3rd-party/glad/build/libglad.a $rootdir/build/lib/ 
	make
fi