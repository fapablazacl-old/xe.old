
#pragma once

#ifndef __xe_gfx_factoryimpl_hpp__
#define __xe_gfx_factoryimpl_hpp__

#include <xe/gfx/Factory.hpp>
#include <xe/gfx/DeviceInfo.hpp>

namespace xe { namespace gfx {
    template<typename DeviceImpl>
    class FactoryImpl : public Factory {
    public:
        explicit FactoryImpl(const DeviceInfo &info) : m_info(info) {}

        virtual ~FactoryImpl() {}

        virtual DeviceInfo getDeviceInfo() override {
            return m_info;
        }

        virtual std::unique_ptr<Device> createDevice() override {
            return std::make_unique<DeviceImpl>();
        }

    private:
        DeviceInfo  m_info;
    };
}}

#endif
