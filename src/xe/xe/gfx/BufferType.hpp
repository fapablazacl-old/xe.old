
#pragma once

#ifndef __xe_gfx_buffertype__
#define __xe_gfx_buffertype__

#include <iosfwd>

namespace xe {
    enum class BufferType {
        Unknown = -1,
        Vertex, 
        Index
    };
}

/*extern XE_API std::ostream& operator<< (std::ostream& os, const xe::BufferType bufferType);*/


#include <ostream>

/*XE_API*/ inline std::ostream& operator<< (std::ostream& os, const xe::BufferType bufferType) {
    switch (bufferType) {
    case xe::BufferType::Unknown:
        return os << "xe::BufferType::Unknown";

    case xe::BufferType::Vertex:
        return os << "xe::BufferType::Vertex";
        
    case xe::BufferType::Index:
        return os << "xe::BufferType::Index";
        
    default:
        return os;    
    }
}

#endif 
