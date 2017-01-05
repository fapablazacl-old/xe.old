
#include "Manager.hpp"

#include <map>
#include <set>
#include <iostream>
#include <cassert>
#include <xe/gfx/Device.hpp>
#include <xe/gfx/DeviceInfo.hpp>
#include <xe/gfx/Factory.hpp>
#include <xe/gfx/Image.hpp>
#include <xe/gfx/ImageLoader.hpp>

namespace xe {

    struct Manager::Private {
        std::map<GraphicsDeviceInfo, Factory*> factories;
        
        std::set<ImageLoader*> imageLoaders;
    };

    Manager::Manager() 
        : m_impl(new Manager::Private()) {}

    Manager::~Manager() {
        delete m_impl;
    }

    std::vector<GraphicsDeviceInfo> Manager::enumerateDevices() {
        assert(m_impl);

        std::vector<GraphicsDeviceInfo> deviceInfos;

        for (const auto &pair : m_impl->factories) {
            deviceInfos.push_back(pair.first);
        }

        return deviceInfos;
    }

    std::unique_ptr<GraphicsDevice> Manager::createDevice() {
        assert(m_impl);

        if (m_impl->factories.size() == 0) {
            std::clog << "xe::Manager::createDevice: No registered device factories." << std::endl;
            return std::unique_ptr<GraphicsDevice>();
        }

        auto first = m_impl->factories.begin();

        return first->second->createDevice();
    }

    std::unique_ptr<GraphicsDevice> Manager::createDevice(const GraphicsDeviceInfo &info) {
        assert(m_impl);
        
        if (m_impl->factories.size() == 0) {
            std::clog << "xe::Manager::createDevice: No registered device factories." << std::endl;
            return std::unique_ptr<GraphicsDevice>();
        }

        auto pos = m_impl->factories.find(info);

        if (pos == m_impl->factories.end()) {
            std::clog << "xe::Manager::createDevice: The specified device key isn't registered." << std::endl;
        }

        return pos->second->createDevice();
    }

    void Manager::registerFactory(Factory *factory) {
        assert(m_impl);
        assert(factory);

        GraphicsDeviceInfo info = factory->getDeviceInfo();

        auto pos = m_impl->factories.find(info);

        if (pos == m_impl->factories.end()) {
            m_impl->factories.insert({info, factory});
        } else {
            std::clog << "xe::Manager::registerFactory: Replacing previous factory." << std::endl;
        }
    }

    void Manager::unregisterFactory(Factory *factory) {
        assert(m_impl);
        assert(factory);

        GraphicsDeviceInfo info = factory->getDeviceInfo();

        auto pos = m_impl->factories.find(info);

        if (pos != m_impl->factories.end()) {
            m_impl->factories.erase(pos);
        } else {
            std::clog << "xe::Manager::unregisterFactory: The specified factory isn't registered." << std::endl;
        }
    }
    
    void Manager::registerImageLoader(ImageLoader *loader) {
        assert(m_impl);
        assert(loader);
        
        m_impl->imageLoaders.insert(loader);
        
    }
    
    void Manager::unregisterImageLoader(ImageLoader *loader) {
        assert(m_impl);
        assert(loader);

        m_impl->imageLoaders.erase(loader);
    }
    
    std::unique_ptr<Image> Manager::createImage(Stream *stream) {
        assert(m_impl);
        assert(stream);
        
        std::clog 
                << "xe::Manager::createImage: Trying from the stream from " 
                << m_impl->imageLoaders.size() 
                << " ImageLoader implementation(s)" 
                << std::endl;
        
        std::unique_ptr<Image> image;
        
        for (ImageLoader *loader : m_impl->imageLoaders) {
            assert(loader);
            
            ImageProxyPtr proxy = loader->createProxy(stream);
            
            assert(proxy);
            
            if (proxy->isValid()) {
                image = proxy->getImage();
                break;
            } else {
                std::clog << "xe::Manager::createImage: Error while the image loading: " << std::endl;
                std::clog << "    " << proxy->getErrorMessage() << std::endl;
            }
        }   
        
        return std::move(image);
    }
}
