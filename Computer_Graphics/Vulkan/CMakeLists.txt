# Minimum version of CMake required
cmake_minimum_required(VERSION 3.0)

# Set project name and language
project(VulkanAPP LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ")

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmodules-ts")
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_BUILD_TYPE RelWithDebInfo)
# Set the output directory for executables
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

# Set the output directory for libraries
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib )

# Add the "include" directory to the include path
include_directories(${PROJECT_SOURCE_DIR}/include)

find_package(Vulkan REQUIRED)
find_package(X11 REQUIRED)
find_package(glfw3 REQUIRED)


# Add an executable target for each subdirectory under src/
file(GLOB SUBDIRECTORIES "src/*")
foreach(SUBDIRECTORY ${SUBDIRECTORIES})
    get_filename_component(TARGET_NAME ${SUBDIRECTORY} NAME)

    # Add all C++ files in the subdirectory as sources for the executable target
    file(GLOB TARGET_SOURCES ${SUBDIRECTORY}/*.cpp)
    add_executable(${TARGET_NAME} ${TARGET_SOURCES})
    target_compile_definitions(${TARGET_NAME} PRIVATE VK_USE_PLATFORM_XLIB_KHR)
    target_include_directories(${TARGET_NAME} PRIVATE ${X11_INCLUDE_DIR})
	# target_link_directories(${TARGET_NAME} PUBLIC ${CMAKE_BINARY_DIR}/lib) # precompiled libs
	target_link_libraries(${TARGET_NAME} LINK_PUBLIC vulkan X11 m glfw)
    
endforeach()

add_subdirectory(shaders)







