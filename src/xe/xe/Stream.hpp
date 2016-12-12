
#pragma once 

#ifndef __xe_stream_hpp__
#define __xe_stream_hpp__

#include <cstdint>
#include <xe/PreDef.hpp>

namespace xe {
    class XE_API Stream {
    public:
        virtual ~Stream();

        virtual bool isReadable() const { return false; }

        virtual std::uint32_t read(void *buffer, const std::uint32_t size) {return 0;}

        virtual bool isWrittable() const { return false; }

        virtual std::uint32_t write(const void *buffer, const std::uint32_t size) {return 0;}
    };
}

#endif 
