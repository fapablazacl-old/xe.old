
#include "PixelFormat.hpp"

#include <cassert>
#include <ostream>

namespace xe { namespace gfx {
    std::size_t getSize(PixelFormat format) {
        switch (format) {
        case PixelFormat::R5G5B5X1:
        case PixelFormat::R5G5B5A1:
        case PixelFormat::R5G6B5:
        case PixelFormat::R16:
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
    
    xe::DataType getDataType(const xe::gfx::PixelFormat format) {
        switch (format) {
        case PixelFormat::B8G8R8:
        case PixelFormat::B8G8R8A8:
        case PixelFormat::R8G8B8:
        case PixelFormat::R8G8B8A8:
            return xe::DataType::UInt8;
            
        case PixelFormat::R16G16B16:
        case PixelFormat::R16G16B16A16:
        case PixelFormat::R16:
            return xe::DataType::UInt16;
        
        default: 
            return xe::DataType::Unknown;
        }
    }
}}

std::ostream& XE_API operator<< (std::ostream &os, const xe::gfx::PixelFormat format) {
    
    switch (format) {
    case xe::gfx::PixelFormat::Unknown: os << "PixelFormat::Unknown"; break;
    case xe::gfx::PixelFormat::R5G5B5X1: os << "PixelFormat::R5G5B5X1"; break;
    case xe::gfx::PixelFormat::R5G5B5A1: os << "PixelFormat::R5G5B5A1"; break;
    case xe::gfx::PixelFormat::R5G6B5: os << "PixelFormat::R5G6B5"; break;
    case xe::gfx::PixelFormat::R8G8B8: os << "PixelFormat::R8G8B8"; break;
    case xe::gfx::PixelFormat::R8G8B8A8: os << "PixelFormat::R8G8B8A8"; break;
    case xe::gfx::PixelFormat::B8G8R8: os << "PixelFormat::B8G8R8"; break;
    case xe::gfx::PixelFormat::B8G8R8A8: os << "PixelFormat::B8G8R8A8"; break;
    case xe::gfx::PixelFormat::R16G16B16: os << "PixelFormat::R16G16B16"; break;
    case xe::gfx::PixelFormat::R16G16B16A16: os << "PixelFormat::R16G16B16A16"; break;
    case xe::gfx::PixelFormat::R16: os << "PixelFormat::R16"; break;
    default: assert(false);
    }
    
    return os;
}
