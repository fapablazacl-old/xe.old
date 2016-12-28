
include_directories(./)

set (target xe.gfx.d3d10)
set (sources 
	xe/gfx/DeviceD3D10.hpp 
	xe/gfx/DeviceD3D10.cpp
	xe/gfx/PluginD3D10.hpp 
	xe/gfx/PluginD3D10.cpp
	xe/gfx/FactoryD3D10.hpp 
	xe/gfx/FactoryD3D10.cpp
	xe/gfx/BufferD3D10.hpp 
	xe/gfx/BufferD3D10.cpp
	xe/gfx/TextureD3D10.hpp 
	xe/gfx/TextureD3D10.cpp
	xe/gfx/ProgramD3D10.hpp 
	xe/gfx/ProgramD3D10.cpp
)

source_group(\\ FILES ${sources})

add_library(${target} SHARED ${sources})

target_link_libraries(${target} xe d3d10)
