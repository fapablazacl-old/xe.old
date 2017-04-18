
set (target xe.gfx.png)

set (sources 
    ImageLoaderPNG.cpp 
    ImageLoaderPNG.hpp 
    ImagePNG.cpp 
    ImagePNG.hpp

	PluginPNG.cpp
)

set (lodepng_sources
    lodepng/lodepng.cpp
    lodepng/lodepng.h
)

source_group(\\ FILES ${sources})
source_group(\\lodepng FILES ${lodepng_sources})

add_library(${target} SHARED ${sources} ${lodepng_sources})

target_link_libraries(${target} xe)
