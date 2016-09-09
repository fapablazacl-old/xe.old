
#pragma once

#ifndef __gl3_buffer__
#define __gl3_buffer__

#include <memory>
#include <cassert>

#include "OpenGL.hpp"
#include "xe/Buffer.hpp"

namespace xe { namespace gfx { namespace gl3  {

    class BufferGL : public Buffer {
    public:
        BufferGL() {}

        BufferGL(GLenum target_, GLenum usage, std::size_t size_, const void *data=nullptr) {
            construct(target_, usage, size_, data);
        }

        ~BufferGL();

        virtual void write(const void *source, const int size = 0, const int offset = 0, const int source_offset = 0) override;

        virtual void read(void* destination, const int size = 0, const int offset = 0, const int destination_offset = 0) const override;

        virtual size_t getSize() const override {
            return m_size;
        }

        GLint getId() const {
            return m_id;
        }

        GLenum getTarget() const {
            return m_target;
        }

        operator bool() const {
            return m_id != 0;
        }

    protected:
        void construct(GLenum target_, GLenum usage, std::size_t size_, const void *data=nullptr);

    private:
        GLenum m_target;
        GLuint m_id = 0;
        std::size_t m_size = 0;
    };
    
    typedef std::unique_ptr<BufferGL> BufferGLPtr;
    typedef std::vector<BufferPtr> BufferGLVector;
}}}

#endif
