
#include "GraphicsDeviceGL.hpp"
#include "TextureGL.hpp"
#include "Util.hpp"

#include <cassert>
#include <algorithm>

namespace xe {
    void window_size_callback(GLFWwindow* m_window, int width, int height) {
        glViewport(0, 0, width, height);
    }

    GraphicsDeviceGL::GraphicsDeviceGL() {
        ::glfwInit();
    
        int hints[][2] = {
            // version
            {GLFW_CONTEXT_VERSION_MAJOR, 3},
            {GLFW_CONTEXT_VERSION_MINOR, 3},
            {GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE},

#if defined(_DEBUG)
            {GLFW_OPENGL_DEBUG_CONTEXT, 1},      
#endif

            // framebuffer
            {GLFW_RED_BITS, 8},
            {GLFW_GREEN_BITS, 8},
            {GLFW_BLUE_BITS, 8},
            {GLFW_ALPHA_BITS, 8} ,
            {GLFW_DEPTH_BITS,  24},
            {GLFW_STENCIL_BITS, 8}
        };
    
        for (auto hint : hints) {
            ::glfwWindowHint(hint[0], hint[1]);
        }
        
        m_window = ::glfwCreateWindow(1360, 900, "test", nullptr, nullptr);
    
        glfwMakeContextCurrent(m_window);
        
#if defined(GL_BINDING)
        glbinding::Binding::useCurrentContext();
        glbinding::Binding::initialize(true);
        
#else 
        ::gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
#endif
        
        XE_GL_CHECK_ERROR();

        glfwSetWindowUserPointer(m_window, this);
        glfwSetWindowSizeCallback(m_window, window_size_callback);

        m_inputManager.setWindow(m_window);
    }

    GraphicsDeviceGL::~GraphicsDeviceGL() {
        ::glfwDestroyWindow(m_window);
        ::glfwTerminate();
    }
    
    static GLenum targets[] = {
        GL_ARRAY_BUFFER, 
        GL_ELEMENT_ARRAY_BUFFER
    };
    
    BufferPtr GraphicsDeviceGL::createBuffer(const BufferType type, const std::size_t size, const void *data) { 
        GLenum target = targets[static_cast<int>(type)];
        GLenum usage = GL_DYNAMIC_DRAW;
        
        return std::make_unique<BufferGL>(target, usage, size, data);
    }

    TexturePtr GraphicsDeviceGL::createTexture(const TextureDesc &desc, const PixelFormat sourceFormat, const DataType sourceType, const void* sourceData)   { 
        return std::make_unique<TextureGL>(desc, sourceFormat, sourceType, sourceData);
    }
    
    SubsetPtr GraphicsDeviceGL::createSubset(const SubsetFormat *format, std::vector<BufferPtr> buffers, const DataType indexType, BufferPtr indexBuffer) { 
        return std::make_unique<SubsetGL>(format, std::move(buffers), indexType, std::move(indexBuffer));
    }

    ProgramPtr GraphicsDeviceGL::createProgram(const std::list<ShaderSource> &sources)  { 
        ShaderGLVector shaders;
        for (const ShaderSource source : sources) {
            shaders.emplace_back(new ShaderGL(converShaderType(source.type), source.source));
        }

        return std::make_unique<ProgramGL>(std::move(shaders));
    }

    void GraphicsDeviceGL::beginFrame(const ClearFlags flags, const ClearParams &params) {
        GLenum clearFlags = 0L;

        if (flags&ClearFlags::Color) {
            clearFlags |= GL_COLOR_BUFFER_BIT;
        }

        if (flags&ClearFlags::Depth) {
            clearFlags |= GL_DEPTH_BUFFER_BIT;
        }

        if (flags&ClearFlags::Stencil) {
            clearFlags |= GL_STENCIL_BUFFER_BIT;
        }

        glClearColor(params.color.x, params.color.y, params.color.z, params.color.w);
        glClearDepth(params.depth);
        glClearStencil(params.stencil);
        glClear(clearFlags);

        XE_GL_CHECK_ERROR();
    }

    void GraphicsDeviceGL::endFrame() {
        glFlush();
        glfwSwapBuffers(m_window);

        XE_GL_CHECK_ERROR();
    }

    void GraphicsDeviceGL::setProgram(Program *program) {
        m_program = static_cast<ProgramGL*>(program);

        glUseProgram(m_program->getId());

        XE_GL_CHECK_ERROR();
    }

    void GraphicsDeviceGL::renderMaterialStatus(const MaterialStatus *status) {
        assert(status);

        if (status->depthTest) {
            glEnable(GL_DEPTH_TEST);
        } else {
            glDisable(GL_DEPTH_TEST);
        }

        if (status->cullFace) {
            glEnable(GL_CULL_FACE);
        } else {
            glDisable(GL_CULL_FACE);
        }

        if (status->blending) {
            glEnable(GL_BLEND);
        } else {
            glDisable(GL_BLEND);
        }

        XE_GL_CHECK_ERROR();
    }

    void GraphicsDeviceGL::preRenderMaterialLayers(const Material *material) {
        assert(material);

        // apply texturing
        for (std::size_t i=0; i<material->getLayerCount(); i++) {
            glActiveTexture(static_cast<GLenum>(GL_TEXTURE0 + i));

            const MaterialLayer *layer = material->getLayer(i);

            if (layer->texture) {
                auto textureGL = static_cast<TextureGL*>(layer->texture);
                glBindTexture(textureGL->getTarget(), textureGL->getId());
            }
        }

        glActiveTexture(GL_TEXTURE0);

        XE_GL_CHECK_ERROR();
    }

    void GraphicsDeviceGL::postRenderMaterialLayers(const Material *material) {
        assert(material);

        // apply texturing
        for (std::size_t i=0; i<material->getLayerCount(); i++) {
            glActiveTexture(static_cast<GLenum>(GL_TEXTURE0 + i));

            const MaterialLayer *layer = material->getLayer(i);

            if (layer->texture) {
                auto textureGL = static_cast<TextureGL*>(layer->texture);
                glBindTexture(textureGL->getTarget(), 0);
            }
        }

        XE_GL_CHECK_ERROR();
    }

    void GraphicsDeviceGL::setMaterial(Material *material) {
        assert(material);
        
        if (m_material == material) {
            return;
        } else if (m_material != nullptr) {
            this->postRenderMaterialLayers(m_material);
        }

        this->renderMaterialStatus(material->getStatus());
        this->preRenderMaterialLayers(material);

        // render user defined material attributes
        material->render(this);

        m_material = material;
    }

    void GraphicsDeviceGL::setMesh(Subset *mesh) {
        m_mesh = static_cast<SubsetGL*>(mesh);

        if (m_mesh) {
            glBindVertexArray(m_mesh->getId());
        } else {
            glBindVertexArray(0);
        }

        XE_GL_CHECK_ERROR();
    }

    static GLenum primitives[] = {
        GL_POINTS,
        GL_LINES,
        GL_LINE_STRIP,
        GL_LINE_LOOP,
        GL_TRIANGLES,
        GL_TRIANGLE_STRIP,
        GL_TRIANGLE_FAN
    };
    
    void GraphicsDeviceGL::draw(Primitive primitive, size_t start, size_t count) {
        assert(m_mesh);
        assert(start >= 0);
        assert(count > 0);

        const GLenum mode = primitives[static_cast<int>(primitive)];
        
        const auto elementCount = static_cast<GLsizei>(count);
        const auto elementStart = static_cast<GLint>(start);
        
        // check if the geometry is indexed
        DataType indexType = DataType::Unknown;

        if (m_mesh->getIndexBuffer()) {
            indexType = m_mesh->getIndexType();
        }

        /*
        for (int i=0; i<m_mesh->getFormat()->getAttribCount(); i++) {
            auto attrib = m_mesh->getFormat()->getAttrib(i);
            auto buffer = m_mesh->getBuffer(attrib->bufferIndex);
            
            if (buffer->getTarget() == GL_ELEMENT_ARRAY_BUFFER) {
                indexType = attrib->type;
            }
        }
        */
        
        const bool isIndexed = indexType != DataType::Unknown;
        
        // draw the geometry, whenever is indexed or not
        if (isIndexed) {
            GLenum type = convertDataType(indexType);
            
            if (elementStart == 0) {
                glDrawElements(mode, elementCount, type, nullptr);    
            } else {
                glDrawElementsBaseVertex(mode, elementCount, type, nullptr, elementStart);
            }
        } else {
            glDrawArrays(mode, elementStart, elementCount);
        }

        XE_GL_CHECK_ERROR();
    }

    void GraphicsDeviceGL::setUniformMatrix(int location, int total, bool transpose, float *values) {
        glUniformMatrix4fv(location, total, transpose?GL_TRUE:GL_FALSE, values);
        
        XE_GL_CHECK_ERROR();
    }

    void GraphicsDeviceGL::setUniform(const UniformDescriptor &desc, const void* uniform) {
        assert(desc.dim >= 1);
        assert(desc.dim <= 4);
        assert(desc.count > 0);
        assert(uniform);
        assert(m_program);

        const auto count = static_cast<GLsizei>(desc.count);

        const GLint location = m_program->getUniform(desc.name);

#if defined(_DEBUG)
        if (location > -1) {
            std::clog << "GraphicsDeviceGL::setUniform: The uniform '" + desc.name + "' hasn't been used in the shader, or isn't defined. Ignoring uniform." << std::endl;
        }
#endif

        switch (desc.type) {
        case xe::DataType::Int32:
            switch (desc.dim) {
                case 1: glUniform1iv(location, count, (const GLint*)uniform); break;
                case 2: glUniform2iv(location, count, (const GLint*)uniform); break;
                case 3: glUniform3iv(location, count, (const GLint*)uniform); break;
                case 4: glUniform4iv(location, count, (const GLint*)uniform); break;
            }
            break;
            
        case xe::DataType::Float32:
            switch (desc.dim) {
                case 1: glUniform1fv(location, count, (const GLfloat*)uniform); break;
                case 2: glUniform2fv(location, count, (const GLfloat*)uniform); break;
                case 3: glUniform3fv(location, count, (const GLfloat*)uniform); break;
                case 4: glUniform4fv(location, count, (const GLfloat*)uniform); break;
            }
            break;

        case xe::DataType::UInt32:
            switch (desc.dim) {
                case 1: glUniform1uiv(location, count, (const GLuint*)uniform); break;
                case 2: glUniform2uiv(location, count, (const GLuint*)uniform); break;
                case 3: glUniform3uiv(location, count, (const GLuint*)uniform); break;
                case 4: glUniform4uiv(location, count, (const GLuint*)uniform); break;
            }
            break;

        default:
            assert(false);
        }

        XE_GL_CHECK_ERROR();  
    }

    void GraphicsDeviceGL::setUniform(const UniformFormat *format, const void *uniforms) {
        assert(format && format->attribs.size() > 0);
        assert(uniforms);

        auto uniform = static_cast<const std::uint8_t*>(uniforms);

        for (const UniformDescriptor &desc : format->attribs) {
            this->setUniform(desc, uniform);

            const size_t size = desc.getSize();

            uniform += size;
        }
    }
}
