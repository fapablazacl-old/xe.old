
cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(xe)

# 
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Prepropressor definitions for supressing VC warnings
add_definitions (-D_CRT_SECURE_NO_WARNINGS)    
add_definitions (-D_SCL_SECURE_NO_WARNINGS)

# XE.SYS
find_package(xe.sys REQUIRED)
include_directories(${XE_SYS_INCLUDE_DIR})

# Version Information
add_definitions(-DXE_VERSION_MAJOR=1)
add_definitions(-DXE_VERSION_MINOR=0)
add_definitions(-DXE_VERSION_REVISION=0)
add_definitions(-DXE_VERSION_BUILD=0)

set(CMAKE_CXX_STANDARD 14)

include_directories(src/xe)

add_subdirectory(src/xe)
add_subdirectory(src/xe.gfx.gl3)
add_subdirectory(src/xe.tests)
#add_subdirectory(src/xe.sfx.al)

add_subdirectory(src/demo)
