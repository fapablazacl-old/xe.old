
#include "GraphicsManager.hpp"

#include <map>
#include <set>
#include <iostream>
#include <cassert>
#include <xe/gfx/GraphicsDevice.hpp>
#include <xe/gfx/GraphicsDeviceInfo.hpp>
#include <xe/gfx/GraphicsFactory.hpp>
#include <xe/gfx/Image.hpp>
#include <xe/gfx/ImageLoader.hpp>

namespace xe {

    struct GraphicsManager::Private {
        std::map<GraphicsDeviceInfo, GraphicsFactory*> factories;
        
        std::set<ImageLoader*> imageLoaders;
    };

    GraphicsManager::GraphicsManager() 
        : m_impl(new GraphicsManager::Private()) {}

    GraphicsManager::~GraphicsManager() {
        delete m_impl;
    }

    std::vector<GraphicsDeviceInfo> GraphicsManager::enumerateDevices() {
        assert(m_impl);

        std::vector<GraphicsDeviceInfo> deviceInfos;

        for (const auto &pair : m_impl->factories) {
            deviceInfos.push_back(pair.first);
        }

        return deviceInfos;
    }

    std::unique_ptr<GraphicsDevice> GraphicsManager::createDevice() {
        assert(m_impl);

        if (m_impl->factories.size() == 0) {
            std::clog << "xe::GraphicsManager::createDevice: No registered device factories." << std::endl;
            return std::unique_ptr<GraphicsDevice>();
        }

        auto first = m_impl->factories.begin();

        return first->second->createDevice();
    }

    std::unique_ptr<GraphicsDevice> GraphicsManager::createDevice(const GraphicsDeviceInfo &info) {
        assert(m_impl);
        
        if (m_impl->factories.size() == 0) {
            std::clog << "xe::GraphicsManager::createDevice: No registered device factories." << std::endl;
            return std::unique_ptr<GraphicsDevice>();
        }

        auto pos = m_impl->factories.find(info);

        if (pos == m_impl->factories.end()) {
            std::clog << "xe::GraphicsManager::createDevice: The specified device key isn't registered." << std::endl;
        }

        return pos->second->createDevice();
    }

    void GraphicsManager::registerFactory(GraphicsFactory *factory) {
        assert(m_impl);
        assert(factory);

        GraphicsDeviceInfo info = factory->getDeviceInfo();

        auto pos = m_impl->factories.find(info);

        if (pos == m_impl->factories.end()) {
            m_impl->factories.insert({info, factory});
        } else {
            std::clog << "xe::GraphicsManager::registerFactory: Replacing previous factory." << std::endl;
        }
    }

    void GraphicsManager::unregisterFactory(GraphicsFactory *factory) {
        assert(m_impl);
        assert(factory);

        GraphicsDeviceInfo info = factory->getDeviceInfo();

        auto pos = m_impl->factories.find(info);

        if (pos != m_impl->factories.end()) {
            m_impl->factories.erase(pos);
        } else {
            std::clog << "xe::GraphicsManager::unregisterFactory: The specified factory isn't registered." << std::endl;
        }
    }
    
    void GraphicsManager::registerImageLoader(ImageLoader *loader) {
        assert(m_impl);
        assert(loader);
        
        m_impl->imageLoaders.insert(loader);
        
    }
    
    void GraphicsManager::unregisterImageLoader(ImageLoader *loader) {
        assert(m_impl);
        assert(loader);

        m_impl->imageLoaders.erase(loader);
    }
    
    std::unique_ptr<Image> GraphicsManager::createImage(Stream *stream) {
        assert(m_impl);
        assert(stream);
        
        std::clog 
                << "xe::GraphicsManager::createImage: Trying from the stream from " 
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
                std::clog << "xe::GraphicsManager::createImage: Error while the image loading: " << std::endl;
                std::clog << "    " << proxy->getErrorMessage() << std::endl;
            }
        }   
        
        return std::move(image);
    }
}
