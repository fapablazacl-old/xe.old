
include_directories(include)

set (sources 
	src/glad.c
	src/glad_debug.c.in
	src/glad_release.c.in
	include/glad/glad.h
	include/glad/glad_debug.h
	include/glad/glad_release.h
)

set (target glad-gles-2.0)

add_library(${target} ${sources})
