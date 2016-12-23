
#pragma once

#ifndef __xe_gfx_factorygles2_hpp__
#define __xe_gfx_factorygles2_hpp__

#include <xe/gfx/Factory.hpp>

namespace xe { namespace gfx {
    class FactoryGLES2 : public Factory {
    public:
        virtual DeviceInfo getDeviceInfo() override;

        virtual std::unique_ptr<Device> createDevice() override;
    };
}}

#endif
