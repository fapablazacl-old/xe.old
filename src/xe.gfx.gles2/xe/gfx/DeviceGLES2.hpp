
#include <GLES2/gl2.h>
#include <GLFW/glfw3.h>
#include <xe/gfx/Device.hpp>

namespace xe { namespace gfx {
    class DeviceGLES2 : public Device {
    public:
        DeviceGLES2();

        virtual ~DeviceGLES2();

        virtual xe::input::InputManager* getInputManager() override;

        virtual const xe::input::InputManager* getInputManager() const override;

        virtual SubsetPtr createSubset(const SubsetFormat *format, std::vector<BufferPtr> buffers, const DataType indexType, BufferPtr indexBuffer) override;
        
        virtual BufferPtr createBuffer(const BufferType type, const std::size_t size, const void *data=nullptr) override;

        virtual TexturePtr createTexture(const TextureDesc &desc, const PixelFormat sourceFormat, const DataType sourceType, const void* sourceData) override;

        virtual ProgramPtr createProgram(const std::list<ShaderSource> &sources) override;

        virtual void setProgram(Program *program) override;

        virtual Program* getProgram() override;
        
        virtual void setMaterial(Material *material) override;

        virtual void setMesh(Subset *mesh) override;

        virtual void draw(Primitive primitive, size_t start, size_t count) override;

        virtual void beginFrame(const ClearFlags flags=ClearFlags::All, const ClearParams &params=ClearParams()) override;

        virtual void endFrame() override;

        virtual void setUniformMatrix(int location, int total, bool transpose, float *values) override;

        virtual void setUniform(const UniformDescriptor &desc, const void* uniform) override;

    private:
        GLFWwindow *m_window = nullptr;
    };
}}
