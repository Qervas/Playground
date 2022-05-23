cmake_minimum_required(VERSION 3.22)
project(POSIX_Multithreading)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS} -g -Werror -Wextra" )
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")
add_executable(POSIX_Multithreading main.cpp ContentSearch_POSIX.cpp ContentSearch_POSIX.h)
