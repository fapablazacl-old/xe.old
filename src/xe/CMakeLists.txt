
# dependencies
if (UNIX)
    set (XE_DEP_LIBRARIES dl)
else ()
    set (XE_DEP_LIBRARIES )
endif()

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
    xe/Core.hpp 
    xe/Core.cpp
    xe/Stream.hpp 
    xe/Stream.cpp
    xe/FileStream.hpp 
    xe/FileStream.cpp
    xe/IosStream.hpp 
    xe/IosStream.cpp
    xe/MemoryStream.hpp 
    xe/MemoryStream.cpp
    xe/Meta.hpp 
	xe/PreDef.cpp 
	xe/PreDef.hpp
	xe/FileUtil.cpp 
	xe/FileUtil.hpp 
	xe/Library.hpp
	xe/LibraryPosix.cpp  
	xe/LibraryWin.cpp 
	xe/Plugin.cpp 
	xe/Plugin.hpp 
	xe/PluginData.cpp
	xe/PluginData.hpp
	xe/PluginLibrary.cpp 
	xe/PluginLibrary.hpp 
	xe/PluginManager.cpp 
	xe/PluginManager.hpp 
	xe/PluginManagerImpl.cpp 
	xe/PluginManagerImpl.hpp 
	xe/Version.cpp 
	xe/Version.hpp
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
    xe/gfx/GraphicsDevice.hpp 
    xe/gfx/GraphicsDevice.cpp 
    xe/gfx/GraphicsDeviceInfo.hpp
    xe/gfx/GraphicsDeviceInfo.cpp
    xe/gfx/GraphicsManager.hpp
    xe/gfx/GraphicsManager.cpp
    xe/gfx/GraphicsFactory.hpp
    xe/gfx/GraphicsFactory.cpp
    xe/gfx/GraphicsFactoryImpl.hpp
    xe/gfx/GraphicsFactoryImpl.cpp
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
    xe/sg/PlaneGenerator.cpp
    xe/sg/SphereGenerator.cpp
    
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
    xe/sg/PlaneGenerator.hpp
    xe/sg/SphereGenerator.hpp
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

target_link_libraries(${target} ${XE_DEP_LIBRARIES})
