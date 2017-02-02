
cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(xe)

# options
option (XE_GFX_ENABLE_GL3 "Enable OpenGL 3.3 Core support" ON)
option (XE_GFX_ENABLE_GLES2 "Enable OpenGL ES 2.0 support" OFF)
option (XE_GFX_ENABLE_D3D10 "Enable Direct3D 10 support" OFF)

option (XE_GFX_ENABLE_FREEIMAGE "Enable FreeImage loader support" ON)
option (XE_GFX_ENABLE_PNG "Enable PNG loader support" OFF)

option (XE_SFX_ENABLE_AL "Enable OpenAL Core support" OFF)

# setup dependency targets
if (XE_GFX_ENABLE_GL3 OR XE_GFX_ENABLE_GLES2)
	set (XE_GFX_ENABLE_GL_DEPENDENCIES ON)
else()
	set (XE_GFX_ENABLE_GL_DEPENDENCIES OFF)
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# 
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Prepropressor definitions for supressing VC warnings
add_definitions (-D_CRT_SECURE_NO_WARNINGS)    
add_definitions (-D_SCL_SECURE_NO_WARNINGS)

# Version Information
add_definitions(-DXE_VERSION_MAJOR=1)
add_definitions(-DXE_VERSION_MINOR=0)
add_definitions(-DXE_VERSION_REVISION=0)
add_definitions(-DXE_VERSION_BUILD=0)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)
include_directories(src/xe)

# mandatory target
add_subdirectory(src/xe)
add_subdirectory(src/demo)
add_subdirectory(src/xe.tests)

# optional targets
if(XE_GFX_ENABLE_GL_DEPENDENCIES)
    #find_package(glbinding REQUIRED)
	#include_directories(${glbinding_DIR}/include)
	#link_directories(${glbinding_DIR}/lib)
	#add_definitions(-DGL_BINDING)

	add_subdirectory(src/glad)
endif()

if(XE_GFX_ENABLE_GL3)
	add_subdirectory(src/xe.gfx.gl3)
endif()

if(XE_GFX_ENABLE_GLES2)
	add_subdirectory(src/xe.gfx.gles2)
endif()

if(XE_GFX_ENABLE_D3D10)
	add_subdirectory(src/xe.gfx.d3d10)
endif()

if(XE_GFX_ENABLE_FREEIMAGE)
	add_subdirectory(src/xe.gfx.fi)
endif()

if(XE_GFX_ENABLE_PNG)
	add_subdirectory(src/xe.gfx.png)
endif()

if(XE_SFX_ENABLE_AL)
	add_subdirectory(src/xe.sfx.al)
endif()
