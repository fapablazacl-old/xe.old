
#pragma once 

#ifndef __xe_factorygl_hpp__
#define __xe_factorygl_hpp__

#include <xe/gfx/Factory.hpp>

namespace xe { namespace gfx { namespace gl3  {
    class FactoryGL : public Factory {
    public:
        virtual ~FactoryGL();

        virtual DeviceInfo getDeviceInfo() override;
        virtual std::unique_ptr<Device> createDevice() override;
    };
}}}

#endif
