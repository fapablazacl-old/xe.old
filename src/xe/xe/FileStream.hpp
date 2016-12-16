
#pragma once 

#ifndef __xe_filestream_hpp__
#define __xe_filestream_hpp__

#include <string>
#include <xe/Stream.hpp>
#include <istream>

namespace xe {
    class XE_API FileStream : public Stream {
    public:;
        explicit FileStream(std::istream *stdStream);
    
        virtual ~FileStream();
        
        virtual bool isReadable() const override;
        
        virtual std::uint32_t read(void *bufferOut, const std::uint32_t blockLength) override;
        
        virtual bool seek(const int offset, const StreamOffset position) override;
        
        virtual std::uint32_t tell() const override;
        
    private:
        struct Private;
        Private *m_impl = nullptr;
    };
}

#endif 
