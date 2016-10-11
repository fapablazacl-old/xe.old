
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

    //void MeshGL::construct(const MeshFormat &format, std::vector<BufferPtr> buffers) {
    //    //!TODO: Implement proper construction with only one buffer for all attributes
    //    m_format = format;

    //    for (BufferPtr &buffer : buffers) {
    //        m_buffers.emplace_back(static_cast<BufferGL*>(buffer.release()));
    //    }

    //    glGenVertexArrays(1, &m_id);
    //    glBindVertexArray(m_id);
    //    XE_GL_CHECK_ERROR();

    //    GLuint vertexAttrib = 0;

    //    for (const MeshAttrib &attrib : format.attribs) {
    //        if (attrib.type == xe::DataType::Unknown) {
    //            break;
    //        }

    //        auto buffer = m_buffers[attrib.bufferIndex].get();

    //        glBindBuffer(buffer->getTarget(), buffer->getId());

    //        if (attrib.bufferType == BufferType::Vertex) {
    //            glEnableVertexAttribArray(vertexAttrib);
    //            glVertexAttribPointer(vertexAttrib, attrib.dim, convertDataType(attrib.type), GL_FALSE, 0, nullptr);
    //        }

    //        XE_GL_CHECK_ERROR();

    //        if (attrib.bufferType == BufferType::Index) {
    //            m_indexed = true;
    //        }

    //        ++vertexAttrib;
    //    }        
    //}

    void MeshGL::construct2(const MeshFormat &format, std::vector<BufferPtr> buffers) {
        XE_GL_CHECK_ERROR();

        m_format = format;

        // downcast the buffers to BufferGL
        for (BufferPtr &buffer : buffers) {
            m_buffers.emplace_back(static_cast<BufferGL*>(buffer.release()));
        }

        // sort attributes by buffer index
        std::vector<MeshAttrib> attribs = m_format.attribs;

        std::sort(attribs.begin(), attribs.end(), [] (const MeshAttrib &a1, const MeshAttrib &a2) {
            return a1.bufferIndex < a2.bufferIndex;
        });

        // create the vertex array object
        glGenVertexArrays(1, &m_id);
        glBindVertexArray(m_id);
        
        // bind vertex attribute buffers
        GLuint vertexAttrib = 0;
        int lastBufferIndex = attribs[0].bufferIndex;
        GLsizei stride = 0;

        for (const MeshAttrib &attrib : attribs) {
            assert(attrib.isValid());

            const BufferGL *buffer = m_buffers[attrib.bufferIndex].get();

            if (lastBufferIndex != attrib.bufferIndex) {
                glBindBuffer(buffer->getTarget(), buffer->getId());

                stride = 0;
            }

            glEnableVertexAttribArray(vertexAttrib);
            glVertexAttribPointer(vertexAttrib, static_cast<GLint>(attrib.dim), convertDataType(attrib.type), GL_FALSE, stride, nullptr);

            vertexAttrib ++;
            stride += static_cast<GLsizei>(attrib.getSize());
            lastBufferIndex = attrib.bufferIndex;
        }

        // bind index buffer
        if (m_format.indexAttrib.isValid()) {
            const BufferGL *buffer = m_buffers[m_format.indexAttrib.bufferIndex].get();
            glBindBuffer(buffer->getTarget(), buffer->getId());
        }

        glBindVertexArray(0);

        XE_GL_CHECK_ERROR();
    }
}}}
