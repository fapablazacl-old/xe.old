
#pragma once

#ifndef __xe_gfx_factory_hpp__
#define __xe_gfx_factory_hpp__

#include <xe/PreDef.hpp>
#include <memory>

namespace xe {
    struct GraphicsDeviceInfo;
    class XE_API GraphicsDevice;
    class XE_API GraphicsFactory {
    public:
        virtual ~GraphicsFactory();
        virtual GraphicsDeviceInfo getDeviceInfo() = 0;
        virtual std::unique_ptr<GraphicsDevice> createDevice() = 0;
    };
}

#endif
