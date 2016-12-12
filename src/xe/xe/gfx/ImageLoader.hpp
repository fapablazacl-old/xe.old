
#pragma once

#ifndef __xe_gfx_imageloader_hpp__
#define __xe_gfx_imageloader_hpp__

#include <xe/Stream.hpp>
#include <xe/gfx/Image.hpp>

namespace xe { namespace gfx {
    class XE_API ImageLoader {
    public:
        virtual ~ImageLoader() {}

        virtual std::unique_ptr<xe::gfx::Image> load(xe::Stream *stream) = 0;
    };
}}

#endif
