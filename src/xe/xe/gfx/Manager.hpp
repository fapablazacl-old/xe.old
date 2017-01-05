
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
    
    class XE_API Factory;
    class XE_API GraphicsDevice;
    class XE_API ImageLoader;
    class XE_API Image;
    
    class XE_API Manager {
    public:
        Manager();
        ~Manager();

        std::vector<GraphicsDeviceInfo> enumerateDevices();

        std::unique_ptr<GraphicsDevice> createDevice();

        std::unique_ptr<GraphicsDevice> createDevice(const GraphicsDeviceInfo &info);

        void registerFactory(Factory *factory);

        void unregisterFactory(Factory *factory);
        
        void registerImageLoader(ImageLoader *loader);
        
        void unregisterImageLoader(ImageLoader *loader);
        
        std::unique_ptr<Image> createImage(Stream *stream);
        
    private:
        Manager(const Manager& other) = delete;
        void operator= (const Manager& other) = delete;

    private:
        struct Private;
        Private *m_impl = nullptr;
    };
}

#endif
