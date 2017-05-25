
# dependencies
if (UNIX)
    set (XE_DEP_LIBRARIES dl)
else ()
    set (XE_DEP_LIBRARIES )
endif()

if (XE_PLUGIN_DYNAMIC_LINKING)
	set (XE_PLUGINS )
endif ()

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
    xe/Meta.hpp 
	xe/PreDef.cpp 
	xe/PreDef.hpp
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

set (sources_io
	xe/io/Archive.hpp
	xe/io/Archive.cpp
    xe/io/Stream.hpp 
    xe/io/Stream.cpp
    xe/io/FileStream.hpp 
    xe/io/FileStream.cpp
    xe/io/IosStream.hpp 
    xe/io/IosStream.cpp
    xe/io/MemoryStream.hpp 
    xe/io/MemoryStream.cpp
	xe/io/FileUtil.cpp 
	xe/io/FileUtil.hpp 
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

	xe/math/Triangle.hpp
    xe/math/Generator.hpp
    xe/math/PlaneGenerator.hpp
    xe/math/SphereGenerator.hpp
    xe/math/Generators.hpp
    xe/math/Generator.cpp
    xe/math/PlaneGenerator.cpp
    xe/math/SphereGenerator.cpp
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
	xe/gfx/BufferType.cpp
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
	xe/gfx/Image.cpp
    xe/gfx/PixelFormat.hpp 
    xe/gfx/PixelFormat.cpp
    xe/gfx/UniformFormat.hpp
    xe/gfx/Material.hpp
    xe/gfx/ImageLoader.cpp
    xe/gfx/ImageLoader.hpp
	xe/gfx/Vertex.cpp
    xe/gfx/Vertex.hpp
	xe/gfx/Font.cpp
    xe/gfx/Font.hpp
	xe/gfx/FontRenderer.cpp
	xe/gfx/FontRenderer.hpp
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
	"xe/sg/Renderable.cpp" 
	"xe/sg/Renderable.hpp" 
	"xe/sg/Scene.cpp" 
	"xe/sg/Scene.hpp" 
	"xe/sg/SceneManager.cpp" 
	"xe/sg/SceneManager.hpp" 
	"xe/sg/SceneNode.cpp" 
	"xe/sg/SceneNode.hpp" 
	"xe/sg/GenericScene.cpp" 
	"xe/sg/GenericScene.hpp" 
	"xe/sg/GenericSceneNode.cpp" 
	"xe/sg/GenericSceneNode.hpp" 
	"xe/sg/GenericSceneManager.cpp" 
	"xe/sg/GenericSceneManager.hpp" 
)

set (sources_game
	"xe/game/Entity.cpp"
	"xe/game/Entity.hpp"
	"xe/game/Message.cpp"
	"xe/game/Message.hpp"
	"xe/game/MessageBus.cpp"
	"xe/game/MessageBus.hpp"
	"xe/game/MessageHandler.cpp"
	"xe/game/MessageHandler.hpp"
	"xe/game/System.cpp"
	"xe/game/System.hpp" 
)

source_group(\\         FILES ${sources})
source_group(\\gfx      FILES ${sources_gfx})
source_group(\\sfx      FILES ${sources_sfx})
source_group(\\sg       FILES ${sources_sg})
source_group(\\input    FILES ${sources_input})
source_group(\\math     FILES ${sources_math})
source_group(\\game		FILES ${sources_game})
source_group(\\io		FILES ${sources_io})

add_definitions(-DXE_BUILD -DXE_SHARED)

add_library(${target} SHARED
    ${sources} 
    ${sources_gfx} 
    ${sources_sfx} 
    ${sources_sg} 
    ${sources_input}
    ${sources_math}
	${sources_game}
	${sources_io}
)

target_link_libraries (
	${target} 
	${XE_DEP_LIBRARIES}
	${XE_PLUGINS}
)
