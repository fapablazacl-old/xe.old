
#pragma once 

#ifndef __xe_filestream_hpp__
#define __xe_filestream_hpp__

#include <string>
#include <cstdio>

#include "Stream.hpp"

namespace xe {

    /**
     * @brief Stream implementation using C file streams.
     */
    class XE_API FileStream : public Stream {
    public:;
        explicit FileStream(const std::string &file);
    
        virtual ~FileStream();
        
        virtual bool isReadable() const override {
            return true;
        }
        
        virtual int read(void *bufferOut, const int size, const int count) override;
        
        virtual bool seek(const int offset, const StreamOffset position) override;
        
        virtual int tell() const override;
        
    private:
        FILE *m_file;
    };
}

#endif 
