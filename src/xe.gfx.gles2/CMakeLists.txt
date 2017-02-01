
# GLFW3
# for some reason, glfw's cmake on Windows doesn't work, so we hack the paths...
find_package(glfw3 3.2 REQUIRED)
include_directories(${glfw3_DIR}/../../../include)
link_directories(${glfw3_DIR}/../..)

set (target xe.gfx.gles2)
set (sources 
	xe/gfx/DeviceGLES2.hpp 
	xe/gfx/DeviceGLES2.cpp
	xe/gfx/PluginGLES2.hpp 
	xe/gfx/PluginGLES2.cpp
	xe/gfx/FactoryGLES2.hpp
	xe/gfx/FactoryGLES2.cpp
)

source_group(\\ FILES ${sources})

add_library(${target} SHARED ${sources})

target_link_libraries(${target} xe glfw ${GLAD_LIBRARY})
