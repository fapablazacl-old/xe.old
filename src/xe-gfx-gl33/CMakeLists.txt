
set (target xe-gfx-gl3)

set (sources
    xe/gfx/gl3/OpenGL.hpp 
    xe/gfx/gl3/BufferGL.hpp        
    xe/gfx/gl3/BufferGL.cpp
    xe/gfx/gl3/GraphicsDeviceGL.hpp        
    xe/gfx/gl3/GraphicsDeviceGL.cpp 
    xe/gfx/gl3/TextureGL.hpp       
    xe/gfx/gl3/TextureGL.cpp 
    xe/gfx/gl3/TextureBufferGL.hpp 
    xe/gfx/gl3/TextureBufferGL.cpp 
    xe/gfx/gl3/ProgramGL.hpp       
    xe/gfx/gl3/ProgramGL.cpp 
    xe/gfx/gl3/ShaderGL.hpp
    xe/gfx/gl3/ShaderGL.cpp 
    xe/gfx/gl3/SubsetGL.hpp
    xe/gfx/gl3/SubsetGL.cpp
    xe/gfx/gl3/InputManagerGLFW.hpp
    xe/gfx/gl3/InputManagerGLFW.cpp
    xe/gfx/gl3/PluginGL.hpp
    xe/gfx/gl3/PluginGL.cpp
    xe/gfx/gl3/Util.hpp
)

source_group (\\ FILES ${sources})

add_definitions(-DXE_BUILD -DXE_SHARED)

if (XE_PLUGIN_DYNAMIC_LINKING)
	add_library(${target} SHARED ${sources})
	target_link_libraries(${target} xe glfw glad-gl33)
else()
	add_library(${target} ${sources})
endif ()
