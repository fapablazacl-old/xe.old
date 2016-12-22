
#include "FactoryD3D10.hpp"
#include "DeviceD3D10.hpp"

#include <xe/gfx/DeviceInfo.hpp>

namespace xe { namespace gfx {
    FactoryD3D10::FactoryD3D10(const std::string &class_) 
        : m_class(class_) {}

    FactoryD3D10::~FactoryD3D10() {}

    DeviceInfo FactoryD3D10::getDeviceInfo() {
        DeviceInfo info;

        info.name = "Direc3D 10 Device";
        info.desc = "";
        info.driver = Driver::D3D_10;
        info.lang = Language::HLSL;

        return info;
    }

    std::unique_ptr<Device> FactoryD3D10::createDevice() {
        return std::make_unique<DeviceD3D10>(m_class);
    }
}}
