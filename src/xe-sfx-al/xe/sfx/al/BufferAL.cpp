
#include "BufferAL.hpp"

namespace xe { namespace sfx { namespace al {
    BufferAL::BufferAL() {
        alGenBuffers(1, &m_id);
        
    }

    BufferAL::~BufferAL() {
        
    }

    std::size_t BufferAL::getSize() const {
        return 0;
    }

    void BufferAL::read(void* destination, const int size, const int offset, const int destination_offset) const {
        
    }

    void BufferAL::write(const void *source, const int size, const int offset, const int source_offset) {
        
    }
}}}
