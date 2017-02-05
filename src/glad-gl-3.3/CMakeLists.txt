
include_directories(include)

set (target glad-gl-3.3)
set (sources 
	include/glad/glad.h 
	include/glad/glad_debug.h 
	include/glad/glad_release.h 
	src/glad.c
)

add_library(${target} ${sources})
