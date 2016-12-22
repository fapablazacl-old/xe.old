
#pragma once 

#ifndef __xe_gfx_factoryd3d10_hpp__
#define __xe_gfx_factoryd3d10_hpp__

#include <string>
#include <xe/gfx/Factory.hpp>

namespace xe { namespace gfx {

    class FactoryD3D10 : public Factory {
    public:
        FactoryD3D10 (const std::string &class_);
        virtual ~FactoryD3D10 ();

        virtual DeviceInfo getDeviceInfo() override;
        virtual std::unique_ptr<Device> createDevice() override;

    private:
        std::string m_class;
    };
}}

#endif
