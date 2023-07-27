cmake_minimum_required(VERSION 3.10)

project(ML)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add -shared to cflags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -shared")

# gdb debug on
set(CMAKE_BUILD_TYPE Debug)

# create a library folder "lib" in the build directory
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

# compile all *.cc files inside src/libdata into a shared library
file(GLOB LIBDATA_SOURCES "src/libdata/*.cc")
add_library(data SHARED ${LIBDATA_SOURCES})





include_directories(include)

file(GLOB SOURCES "src/*.cc")

# add_executable(ML ${SOURCES})