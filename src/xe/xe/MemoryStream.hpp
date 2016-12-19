
#pragma once 

#ifndef __xe_filestream_hpp__
#define __xe_filestream_hpp__

#include <cstdint>
#include <cstddef>
#include <xe/Stream.hpp>

namespace xe {
    class XE_API MemoryStream : public Stream {
    public:
        MemoryStream(const std::uint8_t *data, const std::size_t size);
        
        virtual ~MemoryStream();
        
        virtual bool isReadable() const override;
        
        virtual int read(void *bufferOut, const int size, const int count) override;
        
        virtual bool seek(const int offset, const StreamOffset position) override;
        
        virtual int tell() const override;
        
    private:
        const std::uint8_t *m_data;
        const std::size_t m_size;
        
        int m_offset = 0;
    };
}

#endif
