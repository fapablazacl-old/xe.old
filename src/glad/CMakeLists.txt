
set (target glad)
set (sources glad.h glad.c)

include_directories(.)

source_group(\\ FILES ${sources})

add_library(${target} ${sources})
