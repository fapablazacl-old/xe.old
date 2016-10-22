
#include "MeshGL.hpp"
#include "Util.hpp"

#include <map>
#include <vector>
#include <algorithm>

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
            
            glBindBuffer(buffer->getTarget(), buffer->getId());
            
            GLsizei stride = 0;
            for (const MeshAttrib &attrib : m_format->getAttribs(bufferIndex)) {
                if (attrib.bufferType != BufferType::Vertex) {
                    continue;
                }
                
                glEnableVertexAttribArray(vertexAttrib);
                
                auto dim = static_cast<GLint>(attrib.dim);
                auto type = convertDataType(attrib.type);
                
                glVertexAttribPointer(vertexAttrib, dim, type, GL_FALSE, stride, nullptr);
                
                stride += static_cast<GLsizei>(attrib.getSize());
                vertexAttrib ++;
            }
        }
        
        glBindVertexArray(0);

        XE_GL_CHECK_ERROR();
    }
}}}
