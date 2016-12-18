
#pragma once

#ifndef __xe_gfx_manager_hpp__
#define __xe_gfx_manager_hpp__

#include <string>
#include <vector>
#include <memory>
#include <xe/PreDef.hpp>

namespace xe {
    class XE_API Stream;
}

namespace xe { namespace gfx {
    
    struct DeviceInfo;
    
    class XE_API Factory;
    class XE_API Device;
    class XE_API ImageLoader;
    class XE_API Image;
    
    class XE_API Manager {
    public:
        Manager();
        ~Manager();

        std::vector<DeviceInfo> enumerateDevices();

        std::unique_ptr<Device> createDevice();

        std::unique_ptr<Device> createDevice(const DeviceInfo &info);

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
}}

#endif
