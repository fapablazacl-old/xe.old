
#pragma once

#ifndef __xe_gfx_factory_hpp__
#define __xe_gfx_factory_hpp__

#include <xe/PreDef.hpp>
#include <memory>

namespace xe { namespace gfx {
    struct DeviceInfo;
    class XE_API Device;
    class XE_API Factory {
    public:
        virtual ~Factory();
        virtual DeviceInfo getDeviceInfo() = 0;
        virtual std::unique_ptr<Device> createDevice() = 0;
    };
}}

#endif
