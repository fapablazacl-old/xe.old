
#include "FileStream.hpp"

#include <cassert>
#include <fstream>

namespace xe {
    
    struct FileStream::Private {
        mutable std::fstream fs;
    };

    FileStream::FileStream(const std::string &file) : m_impl(new FileStream::Private())  {
        assert(m_impl);
        
        m_impl->fs.open(file.c_str(), std::ios_base::binary | std::ios_base::in);
        
        assert(m_impl->fs.is_open());
    }
    
    FileStream::~FileStream() {
        assert(m_impl);
        
        delete m_impl;
    }
    
    bool FileStream::isReadable() const { 
        assert(m_impl);
        assert(m_impl->fs.is_open());
        
        return true; 
    }
    
    std::uint32_t FileStream::read(void *bufferOut, const std::uint32_t blockLength) {
        assert(m_impl);
        assert(m_impl->fs.is_open());
        assert(bufferOut);
        
        auto pos = m_impl->fs.tellg();
                
        m_impl->fs.read((char*)bufferOut, blockLength);
        
        return m_impl->fs.tellg() - pos;
    }
    
    bool FileStream::seek(const int offset, const StreamOffset position) {
        assert(m_impl);
        assert(m_impl->fs.is_open());
        
        switch (position) {
        case StreamOffset::Current:
            m_impl->fs.seekg(offset, std::ios_base::cur);
            break;
            
        case StreamOffset::Set:
            m_impl->fs.seekg(offset);
            break;
            
        case StreamOffset::End:
            m_impl->fs.seekg(offset, std::ios_base::end);
            
        default:
            assert(false);
        }
        
        return true;
    }
    
    std::uint32_t FileStream::tell() const {
        assert(m_impl);
        assert(m_impl->fs.is_open());
        
        return m_impl->fs.tellg();
    }
}
