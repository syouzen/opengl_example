# CMake entry point
cmake_minimum_required (VERSION 3.0)
project (Tutorials)

find_package(OpenGL REQUIRED)


if( CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR )
    message( FATAL_ERROR "Please select another Build Directory ! (and give it a clever name, like bin_Visual2012_64bits/)" )
endif()
if( CMAKE_SOURCE_DIR MATCHES " " )
	message( "Your Source Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()
if( CMAKE_BINARY_DIR MATCHES " " )
	message( "Your Build Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()



# Compile external dependencies 
add_subdirectory (external)

# On Visual 2005 and above, this module can set the debug working directory
cmake_policy(SET CMP0026 OLD)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/external/rpavlik-cmake-modules-fe2273")
include(CreateLaunchers)
include(MSVCMultipleProcessCompile) # /MP

if(INCLUDE_DISTRIB)
	add_subdirectory(distrib)
endif(INCLUDE_DISTRIB)

include_directories(
	external/AntTweakBar-1.16/include/
	external/glfw-3.1.2/include/
	external/glm-0.9.7.1/
	external/glew-1.13.0/include/
	external/assimp-3.0.1270/include/
	external/bullet-2.81-rev2613/src/
	include/
)

set(ALL_LIBS
	${OPENGL_LIBRARY}
	glfw
	GLEW_1130
)

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

add_compile_options(-Wall -g)

# Example 1
add_executable(first_window 
src/first_window/first_window.cc
)

target_link_libraries(first_window
${ALL_LIBS}
)

set_target_properties(first_window
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/first_window"
)

# Example 2
add_executable(colorful_window
src/colorful_window/colorful_window.cc
)

target_link_libraries(colorful_window
${ALL_LIBS}
)

set_target_properties(colorful_window
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/colorful_window"
)

# Example 3
add_executable(triangle
src/triangle/triangle.cc

src/triangle/VertexShader.vertexshader
src/triangle/FragmentShader.fragmentshader
)

target_link_libraries(triangle
${ALL_LIBS}
)

set_target_properties(triangle
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/triangle"
)

# Example 4
add_executable(cube
src/cube/cube.cc

src/cube/VertexShader.vertexshader
src/cube/FragmentShader.fragmentshader
)

target_link_libraries(cube
${ALL_LIBS}
)

set_target_properties(cube
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/cube"
)

# Example 5
add_executable(rotating_cube
src/rotating_cube/rotating_cube.cc

src/rotating_cube/VertexShader.vertexshader
src/rotating_cube/FragmentShader.fragmentshader
)

target_link_libraries(rotating_cube
${ALL_LIBS}
)

set_target_properties(rotating_cube
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/rotating_cube"
)

# Example 6
add_executable(textured_cube
src/textured_cube/textured_cube.cc

src/textured_cube/VertexShader.vertexshader
src/textured_cube/FragmentShader.fragmentshader
)

target_link_libraries(textured_cube
${ALL_LIBS}
)

set_target_properties(textured_cube
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/textured_cube"
)

# Example 7
add_executable(model_loader
src/model_loader/model_loader.cc

src/model_loader/VertexShader.vertexshader
src/model_loader/FragmentShader.fragmentshader
)

target_link_libraries(model_loader
${ALL_LIBS}
)

set_target_properties(model_loader
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/model_loader"
)

# Example 8
add_executable(indexing_vbo
src/indexing_vbo/indexing_vbo.cc

src/indexing_vbo/VertexShader.vertexshader
src/indexing_vbo/FragmentShader.fragmentshader
)

target_link_libraries(indexing_vbo
${ALL_LIBS}
)

set_target_properties(indexing_vbo
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/indexing_vbo"
)

# Example 8
add_executable(instancing
src/instancing/instancing.cc

src/instancing/VertexShader.vertexshader
src/instancing/FragmentShader.fragmentshader
)

target_link_libraries(instancing
${ALL_LIBS}
)

set_target_properties(instancing
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/instancing"
)

# Example 9
add_executable(tess_mode
src/tess_mode/tess_mode.cc

src/tess_mode/VertexShader.vertexshader
src/tess_mode/TessControlShader.tesscontrolshader
src/tess_mode/TessEvaluationShader.tessevaluationshader
src/tess_mode/FragmentShader.fragmentshader
)

target_link_libraries(tess_mode
${ALL_LIBS}
)

set_target_properties(tess_mode
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/tess_mode"
)

