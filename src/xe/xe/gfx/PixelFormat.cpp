
#include "PixelFormat.hpp"

#include <cassert>

namespace xe { namespace gfx {
    std::size_t size(PixelFormat format) {
        switch (format) {
        case PixelFormat::R5G5B5X1:
        case PixelFormat::R5G5B5A1:
        case PixelFormat::R5G6B5:
            return 16;

        case PixelFormat::B8G8R8:
        case PixelFormat::R8G8B8:
            return 24;

        case PixelFormat::R8G8B8A8:
        case PixelFormat::B8G8R8A8:
            return 32;

        case PixelFormat::R16G16B16:
            return 48;
            
        case PixelFormat::R16G16B16A16:
            return 64;
            
        default:
            assert(false);
            return 0;
        }
    }
    
    xe::DataType getType(const xe::gfx::PixelFormat format) {
        switch (format) {
        case PixelFormat::B8G8R8:
        case PixelFormat::B8G8R8A8:
        case PixelFormat::R8G8B8:
        case PixelFormat::R8G8B8A8:
            return xe::DataType::UInt8;
            
        case PixelFormat::R16G16B16:
        case PixelFormat::R16G16B16A16:
            return xe::DataType::UInt16;
        
        default: 
            return xe::DataType::Unknown;
        }
    }
}}
