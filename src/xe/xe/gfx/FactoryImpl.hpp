
#pragma once

#ifndef __xe_gfx_factoryimpl_hpp__
#define __xe_gfx_factoryimpl_hpp__

#include <xe/gfx/Factory.hpp>
#include <xe/gfx/DeviceInfo.hpp>

namespace xe {
    template<typename DeviceImpl>
    class FactoryImpl : public Factory {
    public:
        explicit FactoryImpl(const GraphicsDeviceInfo &info) : m_info(info) {}

        virtual ~FactoryImpl() {}

        virtual GraphicsDeviceInfo getDeviceInfo() override {
            return m_info;
        }

        virtual std::unique_ptr<GraphicsDevice> createDevice() override {
            return std::make_unique<DeviceImpl>();
        }

    private:
        GraphicsDeviceInfo  m_info;
    };
}

#endif
