
set (target demo)
set (sources 
	Application.hpp 
	Application.cpp
	ResourceManager.hpp
	ResourceManager.cpp
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

add_executable(${target} ${sources} ${sources_render})

target_link_libraries(${target} xe)
