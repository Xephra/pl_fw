# CMake entry point
cmake_minimum_required (VERSION 2.6)
project (pl_fw)


OPTION(MAKE_DEMO "Make pl_fw demo application" ON)

# Compile external dependencies
find_package(OpenGL REQUIRED)

add_subdirectory (ext_libs)

include_directories(
	${CMAKE_SOURCE_DIR}/ext_libs/glfw-3.2.1/include/GLFW
	${CMAKE_SOURCE_DIR}/ext_libs/glew-2.1.0/include
	${CMAKE_SOURCE_DIR}/ext_libs/glm-0.9.8.4
	${CMAKE_SOURCE_DIR}/ext_libs/SOIL2/${HEADERS}
	${CMAKE_SOURCE_DIR}/ext_libs
	${CMAKE_SOURCE_DIR}/pl_fw
	${CMAKE_SOURCE_DIR}/.
)

link_directories(
	${CMAKE_SOURCE_DIR}/ext_libs/glfw-3.2.1/src
	${CMAKE_SOURCE_DIR}/ext_libs/glew-2.1.0/lib
	${CMAKE_SOURCE_DIR}/pl_fw
)

set(ALL_GRAPHICS_LIBS
	${OPENGL_LIBRARY}
	pl_fw
	glfw
	glew
)

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

####################################################################
# libpl_fw.a                                                        #
####################################################################
add_library(pl_fw
	pl_fw/graphics/window.cpp
	pl_fw/graphics/window.h
	pl_fw/input/input.cpp
	pl_fw/input/input.h
	pl_fw/maths/vec2.cpp
	pl_fw/maths/vec2.h
	
)
file(
	COPY ${CMAKE_SOURCE_DIR}/pl_fw/shaders
	DESTINATION ${CMAKE_BINARY_DIR}
)
file(
	COPY ${CMAKE_SOURCE_DIR}/pl_fw/fonts
	DESTINATION ${CMAKE_BINARY_DIR}
)

####################################################################
# demo               	                                          #
####################################################################
IF(MAKE_DEMO)
	add_executable(DEMO
		DEMO/main.cpp
	)
	target_link_libraries(DEMO
		${ALL_GRAPHICS_LIBS}
	)
	# Copy assets to the build directory
	file(
		COPY DEMO/assets
		DESTINATION ${CMAKE_BINARY_DIR}
	)
ENDIF()
