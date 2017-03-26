
include_directories(".")

set (target demo)

set (sources 
	DemoApp.hpp 
	DemoApp.cpp
	Resources.hpp
	Resources.cpp
)

set (sources_util 
	util/Archive.hpp
	util/Archive.cpp
	util/FrameTimer.hpp
	util/FrameTimer.cpp
)

set (sources_system
	system/Entity.hpp
	system/Entity.cpp
	system/CameraEntity.hpp
	system/CameraEntity.cpp
	system/Message.hpp
	system/Message.cpp
	system/MessageBus.hpp
	system/MessageBus.cpp
	system/MessageHandler.hpp
	system/MessageHandler.cpp
	system/System.hpp
	system/System.cpp
	system/InputSystem.hpp
	system/InputSystem.cpp
	system/GameSystem.hpp
	system/GameSystem.cpp
	system/RenderSystem.hpp
	system/RenderSystem.cpp
	system/ResourceManager.hpp
	system/ResourceManager.cpp
)

set (sources_render
	render/PhongMaterial.hpp
	render/PhongMaterial.cpp
	render/PhongLight.hpp
	render/PhongLight.cpp
	render/PhongLightRenderer.hpp
	render/PhongLightRenderer.cpp
	render/PhongPipeline.hpp
	render/PhongPipeline.cpp
	render/Mesh.hpp
	render/Mesh.cpp
	render/MeshRenderer.hpp
	render/MeshRenderer.cpp
	render/Renderer.hpp
	render/Renderer.cpp
	render/Pipeline.hpp
	render/Pipeline.cpp
	render/SceneRenderer.hpp
	render/SceneRenderer.cpp
	render/Camera.hpp
	render/Camera.cpp
	render/CameraRenderer.hpp
	render/CameraRenderer.cpp
	render/Renderable.cpp
	render/Renderable.hpp
)

source_group(\\ FILES ${sources})
source_group(\\render FILES ${sources_render})
source_group(\\util FILES ${sources_util})
source_group(\\system FILES ${sources_system})

add_executable(${target} ${sources} ${sources_render} ${sources_util} ${sources_system})

target_link_libraries(${target} xe)
