
set (target xe-gfx-fi)

set (sources 
    PluginFI.cpp
    ImageFI.cpp 
    ImageFI.hpp
    ImageLoaderFI.cpp 
    ImageLoaderFI.hpp
)

find_package(FreeImage REQUIRED)

include_directories(${FREEIMAGE_INCLUDE_DIRS})

add_definitions(-DXE_BUILD -DXE_SHARED)

add_library (${target} SHARED ${sources})

source_group(\\ FILES ${sources})

target_link_libraries(${target} xe ${FREEIMAGE_LIBRARIES})
