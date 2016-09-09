
set (target xe.gfx.gl3)

set (sources
    xe/gfx/gl3/OpenGL.hpp 
    xe/gfx/gl3/BufferGL.hpp        
    xe/gfx/gl3/BufferGL.cpp
    xe/gfx/gl3/DeviceGL.hpp        
    xe/gfx/gl3/DeviceGL.cpp 
    xe/gfx/gl3/TextureGL.hpp       
    xe/gfx/gl3/TextureGL.cpp 
    xe/gfx/gl3/TextureBufferGL.hpp 
    xe/gfx/gl3/TextureBufferGL.cpp 
    xe/gfx/gl3/MaterialGL.hpp 
    xe/gfx/gl3/ProgramGL.hpp       
    xe/gfx/gl3/ProgramGL.cpp 
    xe/gfx/gl3/ShaderGL.hpp        
    xe/gfx/gl3/ShaderGL.cpp 
    xe/gfx/gl3/MeshGL.hpp          
    xe/gfx/gl3/MeshGL.cpp
    xe/gfx/gl3/InputManagerGLFW.hpp    
    xe/gfx/gl3/InputManagerGLFW.cpp
)

add_library(${target} ${sources})
