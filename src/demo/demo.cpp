
#include <xe/Core.hpp>
#include <xe/PluginManager.hpp>
#include <xe/gfx/Manager.hpp>
#include <xe/gfx/Device.hpp>

int main() {
    xe::Core core;

    core.getPluginManager()->load("xe.gfx.gl3");

    return 0;
}
