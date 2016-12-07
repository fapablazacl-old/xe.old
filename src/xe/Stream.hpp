
#pragma once 

#ifndef __xe_stream_hpp__
#define __xe_stream_hpp__

#include <cstdint>

namespace xe {
    class Stream {
    public:
        virtual ~Stream();

        virtual std::uint32_t read(void *buffer, const std::uint32_t size) = 0;

        virtual std::uint32_t write(const void *buffer, const std::uint32_t size) = 0;
    };
}

#endif 
