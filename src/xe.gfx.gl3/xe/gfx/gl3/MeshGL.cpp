
#include "MeshGL.hpp"
#include "Util.hpp"

#include <map>
#include <vector>

namespace xe { namespace gfx { namespace gl3  {
    
    /**
     * @brief Utility structure for buffer classification.
     */
    struct BufferClassifier {
        BufferType bufferType;
        int bufferIndex;

        BufferClassifier() {}

        BufferClassifier(BufferType bufferType_, int bufferIndex_) 
            : bufferType(bufferType_), bufferIndex(bufferIndex_) {}
    };

    inline bool operator== (const BufferClassifier &class1, const BufferClassifier &class2) {
        if (class1.bufferType != class2.bufferType) {
            return false;
        }

        if (class1.bufferIndex != class2.bufferIndex) {
            return false;
        }

        return true;
    }

    inline bool operator< (const BufferClassifier &class1, const BufferClassifier &class2) {
        if (class1.bufferType >= class2.bufferType) {
            return false;
        }

        if (class1.bufferIndex >= class2.bufferIndex) {
            return false;
        }

        return true;
    }

    MeshGL::~MeshGL() {
        if (m_id) {
            glDeleteVertexArrays(1, &m_id);
            m_id = 0;
        }

        XE_GL_CHECK_ERROR();
    }

    void MeshGL::construct(const MeshFormat &format, std::vector<BufferPtr> buffers) {
        //!TODO: Implement proper construction with only one buffer for all attributes
        m_format = format;

        for (BufferPtr &buffer : buffers) {
            m_buffers.emplace_back(static_cast<BufferGL*>(buffer.release()));
        }

        glGenVertexArrays(1, &m_id);
        glBindVertexArray(m_id);
        XE_GL_CHECK_ERROR();

        GLuint vertexAttrib = 0;

        for (const MeshAttrib &attrib : format.attribs) {
            if (attrib.type == xe::DataType::Unknown) {
                break;
            }

            auto buffer = m_buffers[attrib.bufferIndex].get();

            glBindBuffer(buffer->getTarget(), buffer->getId());

            if (attrib.bufferType == BufferType::Vertex) {
                glEnableVertexAttribArray(vertexAttrib);
                glVertexAttribPointer(vertexAttrib, attrib.dim, convertDataType(attrib.type), GL_FALSE, 0, nullptr);
            }

            XE_GL_CHECK_ERROR();

            if (attrib.bufferType == BufferType::Index) {
                m_indexed = true;
            }

            ++vertexAttrib;
        }        
    }

    void MeshGL::construct2(const MeshFormat &format, std::vector<BufferPtr> buffers) {
        XE_GL_CHECK_ERROR();

        m_format = format;

        // downcast the buffers to BufferGL
        for (BufferPtr &buffer : buffers) {
            m_buffers.emplace_back(static_cast<BufferGL*>(buffer.release()));
        }

        // classify the buffers by type and index
        std::map<BufferClassifier, std::vector<BufferGL*>> classifiedBuffers;

        for (const MeshAttrib &attrib : format.attribs) {
            auto key = BufferClassifier(attrib.bufferType, attrib.bufferIndex);
            auto value = m_buffers[attrib.bufferIndex].get();

            classifiedBuffers[key].push_back(value);
        }   

        // create the vertex array object
        glGenVertexArrays(1, &m_id);
        glBindVertexArray(m_id);
        
        for (const auto &pair : classifiedBuffers) {
            auto classifier = pair.first;

            for (auto buffer : pair.second) {
                //::glBindBuffer()
            }

            //::glBindBuffer()
        }

        glBindVertexArray(0);

        XE_GL_CHECK_ERROR();
    }
}}}
