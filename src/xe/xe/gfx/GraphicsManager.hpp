
#pragma once

#ifndef __xe_gfx_manager_hpp__
#define __xe_gfx_manager_hpp__

#include <string>
#include <vector>
#include <memory>
#include <xe/PreDef.hpp>

namespace xe {
    class XE_API Stream;

    struct GraphicsDeviceInfo;
    
    class XE_API GraphicsFactory;
    class XE_API GraphicsDevice;
    class XE_API ImageLoader;
    class XE_API Image;
    
    class XE_API GraphicsManager {
    public:
        GraphicsManager();
        ~GraphicsManager();

        std::vector<GraphicsDeviceInfo> enumerateDevices();

        std::unique_ptr<GraphicsDevice> createDevice();

        std::unique_ptr<GraphicsDevice> createDevice(const GraphicsDeviceInfo &info);

        void registerFactory(GraphicsFactory *factory);

        void unregisterFactory(GraphicsFactory *factory);
        
        void registerImageLoader(ImageLoader *loader);
        
        void unregisterImageLoader(ImageLoader *loader);
        
        std::unique_ptr<Image> createImage(Stream *stream);
        
    private:
        GraphicsManager(const GraphicsManager& other) = delete;
        void operator= (const GraphicsManager& other) = delete;

    private:
        struct Private;
        Private *m_impl = nullptr;
    };
}

#endif
