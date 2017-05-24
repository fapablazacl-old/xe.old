
#include "FactoryGLES2.hpp"
#include "DeviceGLES2.hpp"

#include <xe/gfx/GraphicsDeviceInfo.hpp>

namespace xe { namespace gfx {

    GraphicsDeviceInfo FactoryGLES2::getDeviceInfo() {
        GraphicsDeviceInfo info;

        info.name = "xe.gfx.gles2";
        info.desc = "OpenGL ES 2.0 Device Implementation";
        info.driver = Driver::GLES_2_0;
        info.lang = Language::GLSL;

        return info;
    }

    std::unique_ptr<GraphicsDevice> FactoryGLES2::createDevice() {
        return std::make_unique<DeviceGLES2>();
    }
}}
