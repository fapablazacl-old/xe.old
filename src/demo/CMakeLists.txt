
set (target demo)
set (sources 
	Application.hpp 
	Application.cpp

	PhongMaterial.hpp
	PhongMaterial.cpp
	PhongLight.hpp
	PhongLight.cpp
	PhongLightRenderer.hpp
	PhongLightRenderer.cpp
	PhongPipeline.hpp
	PhongPipeline.cpp
	Mesh.hpp
	Mesh.cpp
	MeshRenderer.hpp
	MeshRenderer.cpp
	Renderer.hpp
	Renderer.cpp
	Pipeline.hpp
	Pipeline.cpp
	SceneRenderer.hpp
	SceneRenderer.cpp
	Camera.hpp
	Camera.cpp
	CameraRenderer.hpp
	CameraRenderer.cpp

	Renderable.cpp
	Renderable.hpp
)

source_group(\\ FILES ${sources})

add_executable(${target} ${sources})

target_link_libraries(${target} xe ${XE_SYS_LIBRARY})
