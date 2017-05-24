
set (target xe-sfx-al)

set (sources
    xe/sfx/al/SourceAL.hpp 
    xe/sfx/al/SourceAL.cpp 
    xe/sfx/al/BufferAL.hpp 
    xe/sfx/al/BufferAL.cpp 
)

add_library(${target} ${sources})
