# Minimum version of CMake required
cmake_minimum_required(VERSION 3.0)

# Set project name and language
project(opengl_app LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive")

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmodules-ts")
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_BUILD_TYPE RelWithDebInfo)
# Set the output directory for executables
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

# Set the output directory for libraries
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib )

# Add the "include" directory to the include path
include_directories(${PROJECT_SOURCE_DIR}/include)

# Add the "glad" directory to the include path
include_directories(${PROJECT_SOURCE_DIR}/3rd-party)
include_directories(${PROJECT_SOURCE_DIR}/3rd-party/glad)

# Add the glad subdirectory as a library
add_subdirectory(3rd-party/glad)

# build glad as a C static library
# add_library(glad STATIC ${CMAKE_SOURCE_DIR}/glad/glad.c)


# Set the linker language for the glad library
# add_library(glad STATIC ${CMAKE_SOURCE_DIR}/glad/glad.c)
set_target_properties(glad PROPERTIES LINKER_LANGUAGE CXX)

set(glad libglad.a)


# Add an executable target for each subdirectory under src/
file(GLOB SUBDIRECTORIES "src/*")
foreach(SUBDIRECTORY ${SUBDIRECTORIES})
    get_filename_component(TARGET_NAME ${SUBDIRECTORY} NAME)

    # Add all C++ files in the subdirectory as sources for the executable target
    file(GLOB TARGET_SOURCES ${SUBDIRECTORY}/*.cpp)
    add_executable(${TARGET_NAME} ${TARGET_SOURCES})
	target_link_directories(${TARGET_NAME} PUBLIC ${CMAKE_BINARY_DIR}/lib) # libglad.a
	target_link_libraries(${TARGET_NAME} LINK_PUBLIC glad glfw glut GL GLEW GLU freetype)
    
endforeach()


    
    








