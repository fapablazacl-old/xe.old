
set (target demo)
set (sources 
	Application.hpp 
	Application.cpp

	PhongMaterial.hpp
	PhongMaterial.cpp
	PhongLight.hpp
	PhongLight.cpp
	PhongPipeline.hpp
	PhongPipeline.cpp
	Mesh.hpp
	Mesh.cpp

	#ModelPart.hpp
	#ModelPart.cpp
	#Model.hpp
	#Model.cpp
	#ModelRenderable.hpp
	#ModelRenderable.cpp
)

source_group(\\ FILES ${sources})

add_executable(${target} ${sources})

target_link_libraries(${target} xe ${XE_SYS_LIBRARY})
