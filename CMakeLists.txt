
cmake_minimum_required(VERSION 3.0)

project(xe)

# 
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Prepropressor for Visual C++
add_definitions (-D_CRT_SECURE_NO_WARNINGS)    
add_definitions (-D_SCL_SECURE_NO_WARNINGS)

# XE.SYS
find_package(xe.sys REQUIRED)
include_directories(${XE_SYS_INCLUDE_DIR})

# Boost
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

add_definitions (-DBOOST_ALL_DYN_LINK)
add_definitions (-DBOOST_ALL_NO_LIB)
add_definitions (-DBOOST_TEST_DYN_LINK)

find_package (Boost 
    COMPONENTS
        filesystem
        system
    REQUIRED
)

include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

# Version Information
add_definitions(-DXE_VERSION_MAJOR=1)
add_definitions(-DXE_VERSION_MINOR=0)
add_definitions(-DXE_VERSION_REVISION=0)
add_definitions(-DXE_VERSION_BUILD=0)

set(CMAKE_CXX_STANDARD 14)

include_directories(src/xe)

add_subdirectory(src/xe)
add_subdirectory(src/xe.gfx.gl3)
#add_subdirectory(src/xe.sfx.al)

add_subdirectory(src/demo)
