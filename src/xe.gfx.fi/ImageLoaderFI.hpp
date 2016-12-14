
#pragma once 

#ifndef __xe_gfx_imageloaderfi_hpp__
#define __xe_gfx_imageloaderfi_hpp__

#include <xe/gfx/ImageLoader.hpp>

namespace xe { namespace gfx { 
    class ImageLoaderFI : public ImageLoader {
    public:
        ImageLoaderFI();
        
        ~ImageLoaderFI();
        
        virtual bool tryLoad(xe::Stream *stream) override;
        
        virtual ImagePtr load(xe::Stream *stream) override;
    };
}}

#endif
