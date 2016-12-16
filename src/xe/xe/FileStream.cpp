
#include "FileStream.hpp"

#include <cassert>
#include <fstream>

namespace xe {
    struct FileStream::Private {
        mutable std::istream *stdStream = nullptr;
    };

    FileStream::FileStream(std::istream *stdStream) : m_impl(new FileStream::Private())  {
        assert(m_impl);
        assert(stdStream);
        
        m_impl->stdStream = stdStream;
    }
    
    FileStream::~FileStream() {
        assert(m_impl);
        
        delete m_impl;
    }
    
    bool FileStream::isReadable() const { 
        assert(m_impl);
        
        return true; 
    }
    
    std::uint32_t FileStream::read(void *bufferOut, const std::uint32_t blockLength) {
        assert(m_impl);
        assert(bufferOut);
        
        auto pos = m_impl->stdStream->tellg();
                
        m_impl->stdStream->read((char*)bufferOut, blockLength);
        
        return m_impl->stdStream->tellg() - pos;
    }
    
    bool FileStream::seek(const int offset, const StreamOffset position) {
        assert(m_impl);
        
        switch (position) {
        case StreamOffset::Current:
            m_impl->stdStream->seekg(offset, std::ios_base::cur);
            break;
            
        case StreamOffset::Set:
            m_impl->stdStream->seekg(offset);
            break;
            
        case StreamOffset::End:
            m_impl->stdStream->seekg(offset, std::ios_base::end);
            
        default:
            assert(false);
        }
        
        return true;
    }
    
    std::uint32_t FileStream::tell() const {
        assert(m_impl);
        
        return m_impl->stdStream->tellg();
    }
}
