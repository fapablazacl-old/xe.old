
#include "TextureGL.hpp"
#include "TextureBufferGL.hpp"

namespace xe {

    std::size_t TextureBufferGL::getSize() const {
        xe::TextureDesc desc = m_texture->getDesc();

        std::size_t size = desc.width;

        if (desc.height != 0) {
            size *= desc.height;
        }

        if (desc.depth != 0) {
            size *= desc.depth;
        }

        switch (desc.format) {
        case xe::PixelFormat::R5G5B5A1:
        case xe::PixelFormat::R5G5B5X1:
        case xe::PixelFormat::R5G6B5:
            size *= 2;

        case xe::PixelFormat::RGB_8:
            size *= 3;

        case xe::PixelFormat::RGBA_8:
            size *= 4;
            
        default: assert(false);
        }

        return size;
    }

    void TextureBufferGL::read(void* destination, const int size, const int offset, const int destination_offset) const {
        assert(size == 0);
        assert(offset == 0);

        assert(false);
    }

    void TextureBufferGL::write(const void *source, const int size, const int offset, const int source_offset) {
        assert(source);
        assert(size == 0);
        assert(offset == 0);
        assert(false);

        xe::TextureDesc desc = m_texture->getDesc();

        switch (desc.type) {
        case xe::TextureType::Tex1D:
            glTexSubImage1D(GL_TEXTURE_1D, 0, 0, (GLsizei)desc.width, GL_RG, GL_UNSIGNED_BYTE, (const char*)source + source_offset);
            
        default: assert(false);
        }
    }
}
