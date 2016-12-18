
set (target xe.gfx.png)

set (sources 
    PluginPNG.cpp
    ImagePNG.cpp 
    ImagePNG.hpp
    ImageLoaderPNG.cpp 
    ImageLoaderPNG.hpp
)

find_package(PNG REQUIRED)

include_directories(${PNG_INCLUDE_DIRS})

add_definitions(-DXE_BUILD -DXE_SHARED)

add_library (${target} SHARED ${sources})

target_link_libraries(${target} xe ${PNG_LIBRARIES})
