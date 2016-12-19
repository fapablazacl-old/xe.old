
#include "MeshGL.hpp"
#include "Util.hpp"

#include <map>
#include <vector>
#include <algorithm>
#include <numeric>

namespace xe { namespace gfx { namespace gl3  {
    
    MeshGL::~MeshGL() {
        if (m_id) {
            glDeleteVertexArrays(1, &m_id);
            m_id = 0;
        }

        XE_GL_CHECK_ERROR();
    }
    
    void MeshGL::construct(const SubsetFormat *format, std::vector<BufferPtr> buffers, BufferPtr indexBuffer) {
        XE_GL_CHECK_ERROR();

        m_format = format;

        // downcast the buffers to BufferGL
        for (BufferPtr &buffer : buffers) {
            assert(buffer.get());
            
            m_buffers.emplace_back(static_cast<BufferGL*>(buffer.release()));
        }
        
        // downcast the index buffers
        m_indexBuffer.reset(static_cast<BufferGL*>(indexBuffer.release()));
        
        auto bufferIndices = m_format->getBufferIndices();
        
        // create the vertex array object
        glGenVertexArrays(1, &m_id);
        glBindVertexArray(m_id);
        
        // bind vertex attribute buffers
        GLuint vertexAttrib = 0;
        
        for (const int bufferIndex : m_format->getBufferIndices()) {
            const BufferGL *buffer = m_buffers[bufferIndex].get();
            const auto &attribs = m_format->getAttribs(bufferIndex);
            
            assert(buffer);
            
            glBindBuffer(buffer->getTarget(), buffer->getId());
            
            std::uint8_t *offset = 0;
            
            // compute stride for current vertex buffer
            GLsizei stride = std::accumulate(std::begin(attribs), std::end(attribs), 0, [](const GLsizei &accum, const MeshAttrib &attrib) {
                return accum + static_cast<GLsizei>(attrib.getSize());
            });
            
            for (const MeshAttrib &attrib : attribs) {
                glEnableVertexAttribArray(vertexAttrib);
                
                auto dim = static_cast<GLint>(attrib.dim);
                auto type = convertDataType(attrib.type);
                
                glVertexAttribPointer(vertexAttrib, dim, type, GL_FALSE, stride, offset);
                
                offset += static_cast<int>(attrib.getSize());
                vertexAttrib ++;
            }
        }
        
        // bind index buffer 
        if (m_indexBuffer) {
            assert(m_indexBuffer->getTarget() == GL_ELEMENT_ARRAY_BUFFER);
            assert(m_indexBuffer->getId() != 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer->getId());
        } else {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }
        
        glBindVertexArray(0);

        XE_GL_CHECK_ERROR();
    }
}}}
