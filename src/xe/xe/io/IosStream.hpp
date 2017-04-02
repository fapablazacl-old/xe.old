
#pragma once 

#ifndef __xe_iosstream_hpp__
#define __xe_iosstream_hpp__

#include <string>
#include <istream>

#include "Stream.hpp"

namespace xe {
    /**
     * @brief Stream implementation using i/o C++ streams.
     * @note Buggy implementation. Fix pending.
     */
    class XE_API IosStream : public Stream {
    public:;
        explicit IosStream(std::istream *stdStream);
    
        virtual ~IosStream();
        
        virtual bool isReadable() const override;
        
        virtual int read(void *bufferOut, const int size, const int count) override;
        
        virtual bool seek(const int offset, const StreamOffset position) override;
        
        virtual int tell() const override;
        
    private:
        struct Private;
        Private *m_impl = nullptr;
    };
}

#endif 
