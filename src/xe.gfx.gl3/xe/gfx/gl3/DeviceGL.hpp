
#pragma once

#ifndef __xe_gfx_gl3_device__
#define __xe_gfx_gl3_device__

#include <cassert>

#include <xe/gfx/Device.hpp>
#include <xe/gfx/UniformFormat.hpp>

#include "InputManagerGLFW.hpp"
#include "OpenGL.hpp"
#include "ProgramGL.hpp"
#include "SubsetGL.hpp"

namespace xe { namespace gfx { namespace gl3  {

    class DeviceGL : public Device {
    public:
        DeviceGL();

        virtual ~DeviceGL();

        virtual xe::input::InputManager* getInputManager() override {
            return &m_inputManager;
        }

        virtual const xe::input::InputManager* getInputManager() const override {
            return &m_inputManager;
        }

        virtual SubsetPtr createSubset(const SubsetFormat *format, std::vector<BufferPtr> buffers, const DataType indexType, BufferPtr indexBuffer)  override;

        virtual BufferPtr createBuffer(const BufferType type, const std::size_t getSize, const void *data)  override;

        virtual TexturePtr createTexture(const TextureDesc &desc, const PixelFormat sourceFormat, const DataType sourceType, const void* sourceData)  override;

        virtual ProgramPtr createProgram(const std::list<ShaderSource> &sources) override;

        virtual void setProgram(Program *program) override;

        virtual Program* getProgram() override {
            return m_program;
        }
        
        virtual void setMaterial(Material *material) override;

        virtual void setMesh(Subset *mesh) override;

        virtual void draw(Primitive primitive, size_t start, size_t count) override;

        virtual void beginFrame(const ClearFlags flags, const ClearParams &params)  override;

        virtual void endFrame()  override;

        virtual void setUniformMatrix(int location, int total, bool transpose, float *values) override;

        virtual void setUniform(const UniformDescriptor &desc, const void* uniform) override;

        virtual void setUniform(const UniformFormat* format, const void *uniforms) override;

    private:
        void renderMaterialStatus(const MaterialStatus *status);
        
        void postRenderMaterialLayers(const Material *material);

        void preRenderMaterialLayers(const Material *material);

    private:
        GLFWwindow *m_window = nullptr;

        Material *m_material = nullptr;
        SubsetGL *m_mesh = nullptr;
        ProgramGL *m_program = nullptr;

        InputManagerGLFW m_inputManager;
    };
}}}

#endif
