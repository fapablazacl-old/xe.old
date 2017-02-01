
include_directories(include)

set (sources src/glad.c)
set (target glad-gles-2.0)

add_library(${target} ${sources})
