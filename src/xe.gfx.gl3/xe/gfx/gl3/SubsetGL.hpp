
#pragma once

#ifndef __gl3_subset__
#define __gl3_subset__

#include <memory>
#include "xe/DataFormat.hpp"
#include "xe/gfx/Subset.hpp"
#include "BufferGL.hpp"

namespace xe { namespace gfx { namespace gl3  {

    class SubsetGL : public Subset {
    public:
        SubsetGL() = default;
        
        SubsetGL(const SubsetFormat *format, std::vector<BufferPtr> buffers, const DataType indexType, BufferPtr indexBuffer) {
            assert(format);
            this->construct(format, std::move(buffers), indexType, std::move(indexBuffer));
        }
        
        ~SubsetGL();

        GLuint getId() const {
            return m_id;
        }
        
        virtual std::size_t getBufferCount() const override {
            return m_buffers.size();
        }

        virtual BufferGL* getBuffer(const std::size_t index) override {
            assert(index >= 0);
            assert(index < m_buffers.size());
            
            return m_buffers[index].get();
        }

        virtual const BufferGL* getBuffer(const std::size_t index) const override {
            assert(index >= 0);
            assert(index < m_buffers.size());
            
            return m_buffers[index].get();
        }

        const SubsetFormat* getFormat() const override {
            assert(m_format);
            
            return m_format;
        }

        virtual Buffer* getIndexBuffer() override {
            //assert(m_indexBuffer->getTarget() == GL_ELEMENT_ARRAY_BUFFER);
            return m_indexBuffer.get();
        }
        
        virtual const Buffer* getIndexBuffer() const override {
            //assert(m_indexBuffer->getTarget() == GL_ELEMENT_ARRAY_BUFFER);
            return m_indexBuffer.get();
        }
        
        virtual DataType getIndexType() const override {
            return m_indexType;
        }

    protected:
        void construct(const SubsetFormat *format, std::vector<BufferPtr> buffers, const DataType indexType, BufferPtr indexBuffer);

    private:
        GLuint m_id = 0;
        std::vector<BufferGLPtr> m_buffers;
        BufferGLPtr m_indexBuffer;
        const SubsetFormat *m_format = nullptr;

        DataType m_indexType = DataType::Unknown;
    };

    typedef std::unique_ptr<SubsetGL> MeshGLPtr;
}}}

#endif
