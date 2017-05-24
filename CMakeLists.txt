# 
# The XE C++ high performance engine
#

cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(xe)

# Use C++14 
set(CMAKE_CXX_STANDARD 14)

# options
option (XE_PLUGIN_DYNAMIC_LINKING "Enable plugin dynamic linking" ON)
option (XE_GFX_ENABLE_GL3		"Enable OpenGL 3.3 support"			ON)
option (XE_GFX_ENABLE_GLES2		"Enable OpenGL ES 2.0 support"		OFF)
option (XE_GFX_ENABLE_FREEIMAGE "Enable FreeImage loader support"	ON)
option (XE_GFX_ENABLE_PNG		"Enable PNG loader support"			OFF)
option (XE_SFX_ENABLE_AL	    "Enable OpenAL support"				OFF)
option (XE_ENABLE_TEST	        "Enable Unit Testings"				OFF)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# 
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# prepropressor definitions for supressing VC warnings
add_definitions (-D_CRT_SECURE_NO_WARNINGS)    
add_definitions (-D_SCL_SECURE_NO_WARNINGS)

# version Information
add_definitions(-DXE_VERSION_MAJOR=1)
add_definitions(-DXE_VERSION_MINOR=0)
add_definitions(-DXE_VERSION_REVISION=0)
add_definitions(-DXE_VERSION_BUILD=0)

# add definition for the plugin linking 
if (XE_PLUGIN_DYNAMIC_LINKING)
	add_definitions(-DXE_PLUGIN_DYNAMIC_LINKING)
endif ()

set (XE_PLUGINS )

# required include directories
include_directories(src/xe/)
include_directories(src/khronos)

# unit test target
if (XE_ENABLE_TEST)
	add_subdirectory(dep/unittest-cpp)
	include_directories(dep/unittest-cpp)
    add_subdirectory(src/xe-tdd)
endif()

# OpenAL plugin
if(XE_SFX_ENABLE_AL)
	add_definitions (-DXE_SFX_ENABLE_AL)

	add_subdirectory(src/xe-sfx-al)

	set (XE_PLUGINS ${XE_PLUGINS} xe-sfx-al)
endif()

# OpenGL 3 plugin
if(XE_GFX_ENABLE_GL3)
	add_definitions (-DXE_GFX_ENABLE_GL3)

	add_subdirectory(dep/glfw)
	
	include_directories(src/glad-gl33)
	add_subdirectory(src/glad-gl33)
	add_subdirectory(src/xe-gfx-gl33)

	set (XE_PLUGINS ${XE_PLUGINS} xe-gfx-gl33 glad-gl33 glfw)
endif()

# OpenGL ES 2 plugin
if(XE_GFX_ENABLE_GLES2)
	add_definitions (-DXE_GFX_ENABLE_GLES2)

	add_subdirectory(dep/glfw)
	
    include_directories(src/glad-es2)
	add_subdirectory(src/glad-es2)
	add_subdirectory(src/xe-gfx-es2)

	set (XE_PLUGINS ${XE_PLUGINS} xe-gfx-es2 glad-es2 glfw)
endif()

# FreeImage plugin
if(XE_GFX_ENABLE_FREEIMAGE)
	add_definitions (-DXE_GFX_ENABLE_FREEIMAGE)

	add_subdirectory(src/xe-gfx-fi)

	set (XE_PLUGINS ${XE_PLUGINS} xe-gfx-fi)
endif()

# PNG plugin
if(XE_GFX_ENABLE_PNG)
	add_definitions (-DXE_GFX_ENABLE_PNG)

	add_subdirectory(src/xe-gfx-png)

	set (XE_PLUGINS ${XE_PLUGINS} xe-gfx-png)
endif()

add_subdirectory(src/xe-demo)

# the multimedia engine core
add_subdirectory(src/xe)
