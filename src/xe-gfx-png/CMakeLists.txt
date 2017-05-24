
set (target xe-gfx-png)

set (sources 
    xe/gfx/png/ImageLoaderPNG.cpp 
    xe/gfx/png/ImageLoaderPNG.hpp 
    xe/gfx/png/ImagePNG.cpp 
    xe/gfx/png/ImagePNG.hpp
	xe/gfx/png/PluginPNG.cpp
	xe/gfx/png/PluginPNG.hpp
)

set (lodepng_sources
    lodepng/lodepng.cpp
    lodepng/lodepng.h
)

include_directories(.)

source_group(\\xe\\gfx\\png FILES ${sources})
source_group(\\lodepng FILES ${lodepng_sources})

if (XE_PLUGIN_DYNAMIC_LINKING)
	add_library(${target} SHARED ${sources} ${lodepng_sources})
	target_link_libraries(${target} xe)
else()
	add_library(${target} ${sources} ${lodepng_sources})
endif()
