
include_directories(.)

set (sources 
	glad/glad.c
	glad/glad_debug.c.in
	glad/glad_release.c.in
	glad/glad.h
	glad/glad_debug.h
	glad/glad_release.h
)

set (target glad-gl21)

source_group(\\ FILES ${sources})

add_library(${target} ${sources})
