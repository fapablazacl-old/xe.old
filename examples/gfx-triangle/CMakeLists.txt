
set (target gfx-triangle)
set (sources Triangle.cpp)

source_group(\\ FILES ${sources})

add_executable(${target} ${sources})

target_link_libraries(${target} xe)
