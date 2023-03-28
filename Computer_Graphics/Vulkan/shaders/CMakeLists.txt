cmake_minimum_required(VERSION 3.10)

project(MyVulkanProject)

find_package(Vulkan REQUIRED)

# Set the shader source and output directories
set(SHADER_SOURCE_DIR "${CMAKE_SOURCE_DIR}/shaders")
set(SHADER_OUTPUT_DIR "${CMAKE_BINARY_DIR}/shaders")

# Create the output directory
file(MAKE_DIRECTORY ${SHADER_OUTPUT_DIR})

# Find all shader files in the source directory
file(GLOB_RECURSE SHADER_SOURCE_FILES
    "${SHADER_SOURCE_DIR}/*.vert"
    "${SHADER_SOURCE_DIR}/*.frag"
)

# Compile each shader file to SPIR-V
foreach(SHADER_SOURCE_FILE ${SHADER_SOURCE_FILES})
    # Get the shader file's relative path from the source directory
    file(RELATIVE_PATH SHADER_RELATIVE_PATH ${SHADER_SOURCE_DIR} ${SHADER_SOURCE_FILE})

    # Get the shader file's name without extension
    get_filename_component(SHADER_BASENAME ${SHADER_SOURCE_FILE} NAME)

    # Set the shader output file
    set(SHADER_OUTPUT_FILE "${SHADER_OUTPUT_DIR}/${SHADER_RELATIVE_PATH}.spv")

    # Create the output subdirectory
    get_filename_component(SHADER_OUTPUT_SUBDIR ${SHADER_OUTPUT_FILE} DIRECTORY)
    file(MAKE_DIRECTORY ${SHADER_OUTPUT_SUBDIR})

    # Add a custom command to compile the shader to SPIR-V using glslc
    add_custom_command(
        OUTPUT ${SHADER_OUTPUT_FILE}
        COMMAND glslc "${SHADER_SOURCE_FILE}" -o "${SHADER_OUTPUT_FILE}"
        DEPENDS ${SHADER_SOURCE_FILE}
        COMMENT "Compiling ${SHADER_SOURCE_FILE} to ${SHADER_OUTPUT_FILE}"
    )

    # Add the shader output file to the list of compiled shaders
    list(APPEND COMPILED_SHADERS ${SHADER_OUTPUT_FILE})
endforeach()

# Create a custom target to build all shaders
add_custom_target(Shaders ALL DEPENDS ${COMPILED_SHADERS})
