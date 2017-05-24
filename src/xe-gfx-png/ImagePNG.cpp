
#include "lodepng/lodepng.h"

#include "ImagePNG.hpp"

#include <xe/io/Stream.hpp>

#include <cstring>
#include <cassert>
#include <iostream>

namespace xe {
    ImagePNG::ImagePNG(std::vector<std::uint8_t> pixels, const unsigned width, const unsigned height) {
        m_pixels = std::move(pixels);
        m_desc.width = width;
        m_desc.height = height;
        m_desc.format = PixelFormat::RGBA_8;
    } 

    ImagePNG::~ImagePNG() {}
}
