
#include "IosStream.hpp"

#include <cassert>
#include <fstream>
#include <iostream>

namespace xe {
    struct IosStream::Private {
        mutable std::istream *stdStream = nullptr;
    };

    IosStream::IosStream(std::istream *stdStream) : m_impl(new IosStream::Private())  {
        assert(m_impl);
        assert(stdStream);
        
        m_impl->stdStream = stdStream;
    }
    
    IosStream::~IosStream() {
        assert(m_impl);
        
        delete m_impl;
    }
    
    bool IosStream::isReadable() const { 
        assert(m_impl);
        assert(m_impl->stdStream);
        
        return true; 
    }
    
    int IosStream::read(void *bufferOut, const int size, const int count) {
        std::cout << "xe::IosStream::read: size=" << size << ", count=" << count << std::endl;
        
        assert(m_impl);
        assert(m_impl->stdStream);
        assert(bufferOut);
        assert(size >= 0);
        assert(count >= 0);
        
        auto ios = m_impl->stdStream;
        
        if (size == 1) {
            ios->read((char*) bufferOut, size * count);
            
            return (int)ios->gcount();
            
        } else {
            // emulate C's fread.
            for (int i=0; i<count; i++) {
                ios->read((char*)bufferOut, size);
                
                const auto readed = ios->gcount();
                
                if (readed < size) {
                    std::cout << "xe::IosStream::read: Unsuccessful read: readed=" << readed << std::endl;
                    //ios->seekg(-readed, std::ios_base::cur);
                    
                    return i;
                }
            }
            
            return count;
        }
    }
    
    bool IosStream::seek(const int offset, const StreamOffset position) {
        std::cout << "xe::IosStream::seek: offset=" << offset << ", count=" << (int)position << std::endl;
        
        assert(m_impl);
        assert(m_impl->stdStream);
        
        switch (position) {
        case StreamOffset::Current:
            m_impl->stdStream->seekg(offset, std::ios_base::cur);
            break;
            
        case StreamOffset::Set:
            assert(offset >= 0);
            m_impl->stdStream->seekg(offset, std::ios_base::beg);
            break;
            
        case StreamOffset::End:
            assert(offset == 0);
            m_impl->stdStream->seekg(offset, std::ios_base::end);
            break;
            
        default:
            assert(false);
        }
        
        return true;
    }
    
    int IosStream::tell() const {
        std::cout << "xe::IosStream::tell: " << m_impl->stdStream->tellg() << std::endl;
        
        assert(m_impl);
        assert(m_impl->stdStream);
        
        assert(m_impl->stdStream->tellg() >= 0);
        
        return static_cast<int>(m_impl->stdStream->tellg());
    }
}
