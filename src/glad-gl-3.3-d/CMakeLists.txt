
include_directories(include)

set (sources src/glad.c)
set (target glad-gl-3.3-d)

add_library(${target} ${sources})
