
#pragma once

#ifndef __EXENG_GRAPHICS_PIXELFORMAT_HPP__
#define __EXENG_GRAPHICS_PIXELFORMAT_HPP__

#include <cstddef>
#include <cstdint>

#include <xe/PreDef.hpp>
#include <xe/DataType.hpp>
#include <ostream>

namespace xe { namespace gfx {
    
    /** 
     * @brief Pixel Format for textures and images
     */
    enum class PixelFormat {
        Unknown,
        R5G5B5X1,
        R5G5B5A1,
        R5G6B5,
        R8G8B8,
        R8G8B8A8,
        B8G8R8,
        B8G8R8A8,
        R16G16B16, 
        R16G16B16A16,
        R16
    };

    std::size_t getSize(PixelFormat format);
    
    xe::DataType getDataType(const PixelFormat format);
}}

extern std::ostream& XE_API operator<< (std::ostream &os, const xe::gfx::PixelFormat format);

#endif
