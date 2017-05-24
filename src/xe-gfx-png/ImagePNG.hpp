
#pragma once 

#ifndef __engine_imagelpng_hpp__
#define __engine_imagelpng_hpp__

#include <cassert>
#include <vector>

#include <xe/gfx/Image.hpp>

namespace xe {
    class Stream;

    class ImagePNG : public Image {
    public:
        ImagePNG(std::vector<std::uint8_t> pixels, const unsigned width, const unsigned height);

        virtual ~ImagePNG();

        virtual ImageDesc getDesc() const override {
            return m_desc;
        }

        virtual void* getPointer() override {
            return m_pixels.data();
        }

        virtual const void* getPointer() const override {
            return m_pixels.data();
        }

    private:
        std::vector<std::uint8_t> m_pixels;
        ImageDesc m_desc;
    };
}

#endif
