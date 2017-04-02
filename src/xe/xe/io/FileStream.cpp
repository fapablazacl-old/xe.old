
#include "FileStream.hpp"

#include <cassert>
#include <iostream>

namespace xe {
    FileStream::FileStream(const std::string &name) {
        m_file = std::fopen(name.c_str(), "rb");
        assert(m_file);
    }
    
    FileStream::~FileStream() {
        assert(m_file);
        std::fclose(m_file);
    }
    
    int FileStream::read(void *bufferOut, const int size, const int count) {
        assert(m_file);
        return (int)std::fread(bufferOut, size, count, m_file);
    }
    
    bool FileStream::seek(const int offset, const StreamOffset position) {
        assert(m_file);
        
        int whence;
        
        switch (position) {
        case StreamOffset::Current: whence = SEEK_CUR; break;
        case StreamOffset::Set: whence = SEEK_SET; break;
        case StreamOffset::End: whence = SEEK_END; break;
        default: assert(false); 
        }
        
        if (std::fseek(m_file, offset, whence)) {
            return false;
        } else {
            return true;
        }
    }
    
    int FileStream::tell() const {
        assert(m_file);

        return std::ftell(m_file);
    }
}
