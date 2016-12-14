
set (target xe)

set (sources 
    xe/Buffer.hpp 
    xe/Common.hpp 
    xe/DataFormat.hpp 
    xe/DataType.hpp 
    xe/Traits.hpp 
    xe/Array.hpp
    xe/Vector.hpp 
    xe/Matrix.hpp 
    xe/Quaternion.hpp 
    xe/Boundary.hpp
    xe/Forward.hpp
    xe/Rect.hpp
    xe/Box.hpp
    xe/FileLocator.hpp 
    xe/FileLocator.cpp
    xe/FileUtil.hpp 
    xe/FileUtil.cpp
    xe/Core.hpp 
    xe/Core.cpp
    xe/Stream.hpp 
    xe/Stream.cpp
    xe/FileStream.hpp 
    xe/FileStream.cpp
    xe/MemoryStream.hpp 
    xe/MemoryStream.cpp
    xe/Meta.hpp 
)

set (sources_input
    xe/input/EventImpl.hpp 
    xe/input/Event.hpp 
    xe/input/EventHandler.hpp 
    xe/input/InputDevice.hpp 
    xe/input/InputManager.hpp 
    xe/input/Keyboard.hpp 
    xe/input/Mouse.hpp 
    xe/input/InputManagerImpl.hpp  
    xe/input/InputManagerImpl.cpp 
    xe/input/KeyboardStatus.hpp    
    xe/input/KeyboardStatus.cpp 
    xe/input/KeyCode.hpp 
    xe/input/KeyStatus.hpp 
    xe/input/KeyStroke.hpp 
)

set (sources_gfx 
    xe/gfx/Device.hpp 
    xe/gfx/Device.cpp 
    xe/gfx/DeviceInfo.hpp
    xe/gfx/DeviceInfo.cpp
    xe/gfx/BufferType.hpp
    xe/gfx/Program.hpp 
    xe/gfx/Program.cpp
    xe/gfx/ShaderType.hpp
    xe/gfx/Subset.hpp 
    xe/gfx/Subset.cpp
    xe/gfx/SubsetFormat.hpp 
    xe/gfx/SubsetFormat.cpp
    xe/gfx/Texture.hpp 
    xe/gfx/Texture.cpp
    xe/gfx/Image.hpp
    xe/gfx/PixelFormat.hpp 
    xe/gfx/PixelFormat.cpp
    xe/gfx/UniformFormat.hpp
    xe/gfx/Material.hpp
    xe/gfx/Manager.hpp
    xe/gfx/Manager.cpp
    xe/gfx/Factory.hpp
    xe/gfx/Factory.cpp
    xe/gfx/FactoryImpl.hpp
    xe/gfx/FactoryImpl.cpp
    xe/gfx/ImageLoader.cpp
    xe/gfx/ImageLoader.hpp
)

set (sources_sfx
    xe/sfx/Source.hpp 
    xe/sfx/Source.cpp 
    xe/sfx/Device.hpp 
    xe/sfx/Device.cpp 
)

set (sources_sg    
    xe/sg/Renderable.cpp
    xe/sg/Pipeline.cpp
    xe/sg/SceneNode.cpp 
    xe/sg/Scene.cpp
    xe/sg/Camera.cpp 
    xe/sg/Light.cpp
    xe/sg/Geometry.cpp
    xe/sg/Generator.cpp
    
    xe/sg/Forward.hpp 
    xe/sg/Renderable.hpp
    xe/sg/Pipeline.hpp
    xe/sg/SceneNode.hpp      
    xe/sg/Scene.hpp          
    xe/sg/Camera.hpp         
    xe/sg/Light.hpp          
    xe/sg/Geometry.hpp       
    xe/sg/TSolidGeometry.hpp 
    xe/sg/Segment.hpp 
    xe/sg/Box.hpp            
    xe/sg/Ray.hpp            
    xe/sg/Plane.hpp          
    xe/sg/Intersect.hpp      
    xe/sg/IntersectInfo.hpp  
    xe/sg/Sphere.hpp
    xe/sg/Triangle.hpp
    xe/sg/Generator.hpp
    xe/sg/Generators.hpp
)

source_group(\\         FILES ${sources})
source_group(\\gfx      FILES ${sources_gfx})
source_group(\\sfx      FILES ${sources_sfx})
source_group(\\sg       FILES ${sources_sg})
source_group(\\input    FILES ${sources_input})

add_definitions(-DXE_BUILD -DXE_SHARED)

add_library(${target} SHARED
    ${sources} 
    ${sources_gfx} 
    ${sources_sfx} 
    ${sources_sg} 
    ${sources_input}
)

target_link_libraries(${target} ${Boost_LIBRARIES} ${XE_SYS_LIBRARY})
