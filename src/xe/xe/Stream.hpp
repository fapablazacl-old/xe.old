
#pragma once 

#ifndef __xe_stream_hpp__
#define __xe_stream_hpp__

#include <xe/PreDef.hpp>

namespace xe {

    enum class StreamOffset {
        Set,
        Current, 
        End
    };

    class XE_API Stream {
    public:
        virtual ~Stream();

        virtual bool isReadable() const { return false; }

        virtual int read(void *buffer, const int size, const int count) {return 0;}

        virtual bool isWrittable() const { return false; }

        virtual int write(const void *buffer, const int size) {return 0;}
        
        virtual bool seek(const int offset, const StreamOffset position) = 0;
        
        virtual int tell() const = 0;
    };
}

#endif 
