
#pragma once

#ifndef __xe_gfx_buffertype__
#define __xe_gfx_buffertype__

#include <string>
#include <xe/PreDef.hpp>

namespace xe {
    enum class BufferType {
        Unknown = -1,
        Vertex, 
        Index
    };

    extern XE_API std::string to_string(const BufferType type);
}

#endif 
