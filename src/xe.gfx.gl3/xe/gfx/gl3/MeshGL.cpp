
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
    
    void MeshGL::construct(const MeshFormat *format, std::vector<BufferPtr> buffers) {
        XE_GL_CHECK_ERROR();

        m_format = format;

        // downcast the buffers to BufferGL
        for (BufferPtr &buffer : buffers) {
            m_buffers.emplace_back(static_cast<BufferGL*>(buffer.release()));
        }
        
        auto bufferIndices = m_format->getBufferIndices();
        
        // create the vertex array object
        glGenVertexArrays(1, &m_id);
        glBindVertexArray(m_id);
        
        // bind vertex attribute buffers
        GLuint vertexAttrib = 0;
        
        for (const int bufferIndex : m_format->getBufferIndices()) {
            const BufferGL *buffer = m_buffers[bufferIndex].get();
            const auto &attribs = m_format->getAttribs(bufferIndex);
            
            glBindBuffer(buffer->getTarget(), buffer->getId());
            
            if (buffer->getTarget() != GL_ARRAY_BUFFER) {
                continue;
            }
            
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
        
        glBindVertexArray(0);

        XE_GL_CHECK_ERROR();
    }
}}}
