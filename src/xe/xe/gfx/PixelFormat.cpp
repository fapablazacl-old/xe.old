
#include "PixelFormat.hpp"

#include <cassert>
#include <ostream>

namespace xe { namespace gfx {
    std::size_t getSize(PixelFormat format) {
        switch (format) {
        case PixelFormat::R5G5B5X1:
        case PixelFormat::R5G5B5A1:
        case PixelFormat::R5G6B5:
        case PixelFormat::R_16:
            return 16;

        case PixelFormat::BGR_8:
        case PixelFormat::RGB_8:
            return 24;

        case PixelFormat::RGBA_8:
        case PixelFormat::BGRA_8:
            return 32;

        case PixelFormat::RGB_16:
            return 48;
            
        case PixelFormat::RGBA_16:
            return 64;
            
        default:
            assert(false);
            return 0;
        }
    }
    
    xe::DataType getDataType(const xe::gfx::PixelFormat format) {
        switch (format) {
        case PixelFormat::BGR_8:
        case PixelFormat::BGRA_8:
        case PixelFormat::RGB_8:
        case PixelFormat::RGBA_8:
            return xe::DataType::UInt8;
            
        case PixelFormat::RGB_16:
        case PixelFormat::RGBA_16:
        case PixelFormat::R_16:
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
    case xe::gfx::PixelFormat::RGB_8: os << "PixelFormat::R8G8B8"; break;
    case xe::gfx::PixelFormat::RGBA_8: os << "PixelFormat::R8G8B8A8"; break;
    case xe::gfx::PixelFormat::BGR_8: os << "PixelFormat::B8G8R8"; break;
    case xe::gfx::PixelFormat::BGRA_8: os << "PixelFormat::B8G8R8A8"; break;
    case xe::gfx::PixelFormat::RGB_16: os << "PixelFormat::R16G16B16"; break;
    case xe::gfx::PixelFormat::RGBA_16: os << "PixelFormat::R16G16B16A16"; break;
    case xe::gfx::PixelFormat::R_16: os << "PixelFormat::R16"; break;
    default: assert(false);
    }
    
    return os;
}
