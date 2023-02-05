#!/bin/bash
rootdir=$(pwd)
if test -f glad/build/libglad.a && test -f build/lib/libglad.a; then
	mkdir -p build
	cd build
	cmake ..
	make
else
	cd glad
	mkdir -p build
	cd build 
	cmake ..
	make
	cd $rootdir
	mkdir -p build
	cd build
	cmake ..
	# ln -f  $rootdir/glad/build/libglad.a ./lib/libglad.a
	cp  $rootdir/glad/build/libglad.a $rootdir/build/lib/ 
	make
fi