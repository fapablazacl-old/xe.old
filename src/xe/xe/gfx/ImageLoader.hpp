
#pragma once

#ifndef __xe_gfx_imageloader_hpp__
#define __xe_gfx_imageloader_hpp__

#include <xe/Stream.hpp>
#include <xe/gfx/Image.hpp>

namespace xe { namespace gfx {

    class XE_API ImageLoader {
    public:
        virtual ~ImageLoader();

        virtual bool tryLoad(xe::Stream *stream) = 0;
        
        virtual ImagePtr load(xe::Stream *stream) = 0;
    };
}}

#endif
