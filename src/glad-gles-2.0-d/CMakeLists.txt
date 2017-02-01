
include_directories(include)

set (sources src/glad.c)
set (target glad-gles-2.0-d)

add_library(${target} ${sources})
