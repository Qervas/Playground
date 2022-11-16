cmake_minimum_required(VERSION 3.0)
project(opengl_app)

add_subdirectory(${CMAKE_SOURCE_DIR}/glad)

add_executable(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/src/main.cpp)
target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/glad)
target_link_libraries(${PROJECT_NAME} glad glfw)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/glad)

