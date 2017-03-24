
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
    xe/Forward.hpp
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

set (sources_math 
    xe/math/Box.hpp            
    xe/math/Ray.hpp            
    xe/math/Plane.hpp          
    xe/math/Intersect.hpp      
    xe/math/IntersectInfo.hpp  
    xe/math/Sphere.hpp
    xe/math/Array.hpp
    xe/math/Vector.hpp 
    xe/math/Matrix.hpp 
    xe/math/Quaternion.hpp 
    xe/math/Boundary.hpp
    xe/math/Rect.hpp
    xe/math/Box.hpp
)

set (sources_input
	xe/input/InputManager.cpp 
	xe/input/InputManager.hpp 
	xe/input/InputCode.cpp 
	xe/input/InputCode.hpp 
	xe/input/InputStatus.cpp 
	xe/input/InputStatus.hpp 
	xe/input/InputState.cpp 
	xe/input/InputState.hpp 
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
	xe/gfx/Vertex.cpp
    xe/gfx/Vertex.hpp
)

set (sources_sfx
    xe/sfx/Source.hpp 
    xe/sfx/Source.cpp 
	xe/sfx/SourceDesc.hpp 
    xe/sfx/SourceDesc.cpp 
	xe/sfx/BufferDesc.hpp 
    xe/sfx/BufferDesc.cpp 
    xe/sfx/SoundDevice.hpp 
    xe/sfx/SoundDevice.cpp 
	xe/sfx/SoundContext.hpp
    xe/sfx/SoundContext.cpp
	xe/sfx/SoundManager.hpp
    xe/sfx/SoundManager.cpp
	xe/sfx/Listener.hpp 
    xe/sfx/Listener.cpp 
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
    xe/sg/Triangle.hpp
    xe/sg/Generator.hpp
    xe/sg/PlaneGenerator.hpp
    xe/sg/SphereGenerator.hpp
    xe/sg/Generators.hpp
)

set (sources_ext
	"xe/ext/Renderable.cpp" 
	"xe/ext/Renderable.hpp" 
	"xe/ext/Scene.cpp" 
	"xe/ext/Scene.hpp" 
	"xe/ext/SceneImpl.cpp" 
	"xe/ext/SceneImpl.hpp" 
	"xe/ext/SceneManager.cpp" 
	"xe/ext/SceneManager.hpp" 
	"xe/ext/SceneNode.cpp" 
	"xe/ext/SceneNode.hpp" 
	"xe/ext/SceneNodeImpl.cpp" 
	"xe/ext/SceneNodeImpl.hpp" 
	"xe/ext/SceneManagerImpl.cpp" 
	"xe/ext/SceneManagerImpl.hpp" 
)

source_group(\\         FILES ${sources})
source_group(\\gfx      FILES ${sources_gfx})
source_group(\\sfx      FILES ${sources_sfx})
source_group(\\sg       FILES ${sources_sg})
source_group(\\input    FILES ${sources_input})
source_group(\\math     FILES ${sources_math})
source_group(\\ext		FILES ${sources_ext})

add_definitions(-DXE_BUILD -DXE_SHARED)

add_library(${target} SHARED
    ${sources} 
    ${sources_gfx} 
    ${sources_sfx} 
    ${sources_sg} 
    ${sources_input}
    ${sources_math}
	${sources_toolkit}
)

target_link_libraries(${target} ${XE_DEP_LIBRARIES})
