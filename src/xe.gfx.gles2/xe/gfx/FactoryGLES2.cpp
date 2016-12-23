
#include "FactoryGLES2.hpp"
#include "DeviceGLES2.hpp"

#include <xe/gfx/DeviceInfo.hpp>

namespace xe { namespace gfx {

    DeviceInfo FactoryGLES2::getDeviceInfo() {
        DeviceInfo info;

        info.name = "xe.gfx.gles2";
        info.desc = "OpenGL ES 2.0 Device Implementation";
        info.driver = Driver::GLES_2_0;
        info.lang = Language::GLSL;

        return info;
    }

    std::unique_ptr<Device> FactoryGLES2::createDevice() {
        return std::make_unique<DeviceGLES2>();
    }
}}
