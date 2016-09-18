
#include <iostream>
#include <xe/Core.hpp>
#include <xe/PluginManager.hpp>
#include <xe/gfx/Manager.hpp>
#include <xe/gfx/Device.hpp>
#include <xe/gfx/DeviceInfo.hpp>

int main() {
    xe::Core core;

    core.getPluginManager()->load("xe.gfx.gl3");

    /*
    auto deviceInfos = core.getGraphicsManager()->enumerateDevices();

    std::cout << "Available device infos:" << std::endl;

    for (const xe::gfx::DeviceInfo &deviceInfo : deviceInfos) {
        std::cout << deviceInfo << std::endl;
    }
    */

    auto device = core.getGraphicsManager()->createDevice();
    auto input = device->getInputManager();
    auto keyboardStatus = input->getKeyboard()->getStatus();

    while(true) {
        input->poll();

        if (keyboardStatus->getKeyStatus(xe::input::KeyCode::KeyEsc) == xe::input::KeyStatus::Press) {
            break;
        }

        device->beginFrame();

        device->endFrame();
    }

    return 0;
}
