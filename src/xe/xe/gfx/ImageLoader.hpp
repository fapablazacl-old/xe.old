
#pragma once

#ifndef __xe_gfx_imageloader_hpp__
#define __xe_gfx_imageloader_hpp__

#include <xe/io/Stream.hpp>
#include <xe/gfx/Image.hpp>

namespace xe {

    /**
     * @brief Image Proxy Interface.
     */
    class XE_API ImageProxy {
    public:
        virtual ~ImageProxy() {}
        
        virtual bool isValid() const = 0;
        
        virtual std::string getErrorMessage() const = 0;
        
        virtual ImagePtr getImage() const = 0;
    };
    
    typedef std::unique_ptr<ImageProxy> ImageProxyPtr;
    
    /**
     * @brief Image Loader Interface. Creates image proxies from streams.
     */    
    class XE_API ImageLoader {
    public:
        virtual ~ImageLoader();
        
        virtual ImageProxyPtr createProxy(xe::Stream *stream) = 0;
    };
}

#endif
