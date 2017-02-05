
set (target xe.gfx.vk)
set (sources PluginVK.hpp PluginVK.cpp)

add_library(${target} SHARED ${sources})
