
#pragma once

#ifndef __xe_gfx_buffertype__
#define __xe_gfx_buffertype__

#include <iosfwd>

namespace xe { namespace gfx {
    enum class BufferType {
        Unknown = -1,
        Vertex, 
        Index
    };
}}

/*extern XE_API std::ostream& operator<< (std::ostream& os, const xe::gfx::BufferType bufferType);*/


#include <ostream>

/*XE_API*/ inline std::ostream& operator<< (std::ostream& os, const xe::gfx::BufferType bufferType) {
    switch (bufferType) {
    case xe::gfx::BufferType::Unknown:
        return os << "xe::gfx::BufferType::Unknown";

    case xe::gfx::BufferType::Vertex:
        return os << "xe::gfx::BufferType::Vertex";
        
    case xe::gfx::BufferType::Index:
        return os << "xe::gfx::BufferType::Index";
        
    default:
        return os;    
    }
}

#endif 
