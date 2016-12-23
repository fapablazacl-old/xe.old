
#include "DeviceGLES2.hpp"

namespace xe { namespace gfx {
    DeviceGLES2::DeviceGLES2() 
    {
        ::glfwInit();

        int hints[][2] = {
            // version
            {GLFW_CLIENT_API, GLFW_OPENGL_ES_API},
            
            // framebuffer
            {GLFW_RED_BITS, 8},
            {GLFW_GREEN_BITS, 8},
            {GLFW_BLUE_BITS, 8},
            {GLFW_ALPHA_BITS, 8} ,
            {GLFW_DEPTH_BITS,  24},
            {GLFW_STENCIL_BITS, 8}
        };

        for (auto hintPair : hints) {
            ::glfwWindowHint(hintPair[0], hintPair[1]);
        }

        m_window = ::glfwCreateWindow(640, 480, "test", nullptr, nullptr);

        ::glfwMakeContextCurrent(m_window);
    }

    DeviceGLES2::~DeviceGLES2()
    {
        ::glfwDestroyWindow(m_window);
        ::glfwTerminate();
    }

    xe::input::InputManager* DeviceGLES2::getInputManager() 
    {
        return nullptr;
    }

    const xe::input::InputManager* DeviceGLES2::getInputManager() const 
    {
        return nullptr;
    }

    SubsetPtr DeviceGLES2::createSubset(const SubsetFormat *format, std::vector<BufferPtr> buffers, const DataType indexType, BufferPtr indexBuffer) 
    {
        return SubsetPtr();
    }
        
    BufferPtr DeviceGLES2::createBuffer(const BufferType type, const std::size_t size, const void *data) 
    {
        return BufferPtr();
    }

    TexturePtr DeviceGLES2::createTexture(const TextureDesc &desc, const PixelFormat sourceFormat, const DataType sourceType, const void* sourceData) 
    {
        return TexturePtr();
    }

    ProgramPtr DeviceGLES2::createProgram(const std::list<ShaderSource> &sources) 
    {
        assert(sources.size() > 0);
        
        return ProgramPtr();
    }

    void DeviceGLES2::setProgram(Program *program) 
    {
        assert(program);
    }

    Program* DeviceGLES2::getProgram() 
    {
        return nullptr;
    }
        
    void DeviceGLES2::setMaterial(Material *material) 
    {
        assert(material);
    }

    void DeviceGLES2::setMesh(Subset *mesh) 
    {
        assert(mesh);
    }

    void DeviceGLES2::draw(Primitive primitive, size_t start, size_t count) 
    {
        assert(start >= 0);
        assert(count > 0);
    }

    void DeviceGLES2::beginFrame(const ClearFlags flags, const ClearParams &params) 
    {
        ::glClearColor(params.color.x, params.color.y, params.color.z, params.color.w);
        ::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void DeviceGLES2::endFrame() 
    {
        ::glFlush();
        ::glfwSwapBuffers(m_window);
    }

    void DeviceGLES2::setUniformMatrix(int location, int total, bool transpose, float *values) 
    {
        assert(values);

    }

    void DeviceGLES2::setUniform(const UniformDescriptor &desc, const void* uniform) 
    {
        assert(uniform);

    }
}}
