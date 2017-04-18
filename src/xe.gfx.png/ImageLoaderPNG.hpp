
#pragma once 

#ifndef __xe_gfx_png_imageloaderpng_hpp__
#define __xe_gfx_png_imageloaderpng_hpp__

#include <memory>
#include <string>

#include <xe/gfx/ImageLoader.hpp>

namespace xe {
    class ImageLoaderPNG : public ImageLoader {
    public:
        ImageLoaderPNG();

        virtual ~ImageLoaderPNG();

        virtual ImageProxyPtr createProxy(xe::Stream *stream) override;
    };
}

#endif 
