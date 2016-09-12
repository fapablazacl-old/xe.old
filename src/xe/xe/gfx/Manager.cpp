
#include "Manager.hpp"

#include <map>
#include <iostream>
#include <cassert>
#include <xe/gfx/Device.hpp>
#include <xe/gfx/DeviceInfo.hpp>
#include <xe/gfx/Factory.hpp>

namespace xe { namespace gfx {

    struct Manager::Private {
        std::map<DeviceInfo, Factory*> factories;
    };

    Manager::Manager() : m_impl(new Manager::Private()) {}

    Manager::~Manager() {
        delete m_impl;
    }

    std::vector<DeviceInfo> Manager::enumerateDevices() {
        assert(m_impl);

        std::vector<DeviceInfo> deviceInfos;

        for (const auto &pair : m_impl->factories) {
            deviceInfos.push_back(pair.first);
        }

        return deviceInfos;
    }

    std::unique_ptr<Device> Manager::createDevice() {
        assert(m_impl);

        if (m_impl->factories.size() == 0) {
            std::clog << "xe::gfx::Manager::createDevice: No registered device factories." << std::endl;
            return std::unique_ptr<Device>();
        }

        auto first = m_impl->factories.begin();

        return first->second->createDevice();
    }

    std::unique_ptr<Device> Manager::createDevice(const DeviceInfo &info) {
        assert(m_impl);
        
        if (m_impl->factories.size() == 0) {
            std::clog << "xe::gfx::Manager::createDevice: No registered device factories." << std::endl;
            return std::unique_ptr<Device>();
        }

        auto pos = m_impl->factories.find(info);

        if (pos == m_impl->factories.end()) {
            std::clog << "xe::gfx::Manager::createDevice: The specified device key is not registered." << std::endl;
        }

        return pos->second->createDevice();
    }

    void Manager::registerFactory(Factory *factory) {
        assert(m_impl);
        assert(factory);

        DeviceInfo info = factory->getDeviceInfo();

        auto pos = m_impl->factories.find(info);

        if (pos == m_impl->factories.end()) {
            m_impl->factories.insert({info, factory});
        } else {
            std::clog << "xe::gfx::Manager::registerFactory: Replacing previous factory." << std::endl;
        }
    }

    void Manager::unregisterFactory(Factory *factory) {
        assert(m_impl);
        assert(factory);

        DeviceInfo info = factory->getDeviceInfo();

        auto pos = m_impl->factories.find(info);

        if (pos != m_impl->factories.end()) {
            m_impl->factories.erase(pos);
        } else {
            std::clog << "xe::gfx::Manager::unregisterFactory: The specified factory isn't registered." << std::endl;
        }
    }
}}
