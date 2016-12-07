
#pragma once

#ifndef __gl3_subset__
#define __gl3_subset__

#include <memory>
#include "xe/DataFormat.hpp"
#include "xe/gfx/Subset.hpp"
#include "BufferGL.hpp"

namespace xe { namespace gfx { namespace gl3  {

    class MeshGL : public Subset {
    public:
        MeshGL() = default;
        
        MeshGL(const SubsetFormat *format, std::vector<BufferPtr> buffers) {
            this->construct(format, std::move(buffers));
        }
        
        ~MeshGL();

        GLuint getId() const {
            return m_id;
        }
        
        virtual std::size_t getBufferCount() const override {
            return m_buffers.size();
        }

        virtual BufferGL* getBuffer(const std::size_t index) override {
            return m_buffers[index].get();
        }

        virtual const BufferGL* getBuffer(const std::size_t index) const override {
            return m_buffers[index].get();
        }

        const SubsetFormat* getFormat() const override {
            return m_format;
        }

    protected:
        //void construct(const SubsetFormat &format, std::vector<BufferPtr> buffers);

        void construct(const SubsetFormat *format, std::vector<BufferPtr> buffers);

    private:
        GLuint m_id = 0;
        std::vector<BufferGLPtr> m_buffers;
        const SubsetFormat *m_format = nullptr;
    };

    typedef std::unique_ptr<MeshGL> MeshGLPtr;
}}}

#endif
