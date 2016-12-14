
#include "MemoryStream.hpp"

#include <cassert>
#include <cstring>

namespace xe {
    MemoryStream::MemoryStream(const std::uint8_t *data, const std::size_t size)
        : m_data(data), m_size(size) {
        
        assert(m_data);
        assert(m_size);
    }

    MemoryStream::~MemoryStream() {}
    
    bool MemoryStream::isReadable() const { 
        return true; 
    }
    
    std::uint32_t MemoryStream::read(void *bufferOut, const std::uint32_t blockLength) {
        assert(m_data);
        assert(bufferOut);
        
        std::memcpy(bufferOut, &m_data[m_offset], blockLength);
        m_offset += blockLength;
    
        return blockLength;
    }
    
    bool MemoryStream::seek(const int offset, const StreamOffset position) {
        switch (position) {
        case StreamOffset::Current:
            m_offset += offset;
            break;
            
        case StreamOffset::Set:
            m_offset = offset;
            break;
            
        case StreamOffset::End:
            m_offset = offset - m_size;
            break;
            
        default:
            assert(false);
        }
        
        return true;
    }
    
    std::uint32_t MemoryStream::tell() const {
        return m_offset;
    }
}
