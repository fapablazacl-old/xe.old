
#pragma once

#ifndef __xe_gfx_device_hpp__
#define __xe_gfx_device_hpp__

#include <list>

#include <xe/Buffer.hpp>
#include <xe/Vector.hpp>
#include <xe/gfx/BufferType.hpp>
#include <xe/gfx/Subset.hpp>
#include <xe/gfx/ShaderType.hpp>
#include <xe/gfx/Program.hpp>
#include <xe/gfx/Texture.hpp>
#include <xe/gfx/UniformFormat.hpp>
#include <xe/gfx/Material.hpp>
#include <xe/gfx/Primitive.hpp>
#include <xe/input/InputManager.hpp>

namespace xe { namespace gfx {

    struct ClearParams {
        xe::Vector4f color;
        double depth;
        int stencil;

        ClearParams(xe::Vector4f color_ = {0.0f, 0.0f, 0.0f, 1.0f}, double depth_ = 1.0f, int stencil_ = 0) 
            : color(color_), depth(depth_), stencil(stencil_){}
    };

    enum class ClearFlags {
        Color = 0x01,
        Depth = 0x02,
        Stencil = 0x04,
        ColorDepth = Color | Depth,
        All = Color | Depth | Stencil
    };

    inline bool operator&(const ClearFlags flags, const ClearFlags value) {
        int nflags = static_cast<int>(flags);
        int nvalue = static_cast<int>(value);

        if (nflags & nvalue) {
            return true;
        } else {
            return false;
        }
    }

    struct BufferCreateParams {
        BufferType type = BufferType::Unknown;
        std::size_t size = 0;
        const void *data = nullptr;

        BufferCreateParams() = default;

        BufferCreateParams(const BufferType type_, const std::size_t size_, const void *data_ = nullptr) 
            : type(type_), size(size_), data(data_) {}
            
        template<typename Container>
        BufferCreateParams(const BufferType type_, const Container& values) 
            : type(type_), size(sizeof(typename Container::value_type) * values.size()), data(values.data()) {}
    };

    class XE_API Device {
    public:
        virtual ~Device() {}

        virtual xe::input::InputManager* getInputManager() = 0;

        virtual const xe::input::InputManager* getInputManager() const = 0;

        virtual SubsetPtr createSubset(const SubsetFormat *format, BufferPtr buffer);
        
        virtual SubsetPtr createSubset(const SubsetFormat *format, std::vector<BufferPtr> buffers) = 0;
        
        virtual SubsetPtr createSubset(const SubsetFormat *format, std::vector<BufferCreateParams> createParams);
        
        virtual BufferPtr createBuffer(const BufferType type, const std::size_t getSize, const void *data=nullptr) = 0;

        template<typename Container>
        BufferPtr  createBuffer(const BufferType type, const Container& values) {
            typedef typename Container::value_type Type;

            return this->createBuffer(type, sizeof(Type) * values.size(), values.data());
        }

        virtual TexturePtr createTexture(const TextureDesc &desc, const PixelFormat sourceFormat, const DataType sourceType, const void* sourceData) = 0;

        virtual ProgramPtr createProgram(const std::list<ShaderSource> &sources) = 0;

        virtual void setProgram(Program *program) = 0;

        virtual Program* getProgram() = 0;
        
        virtual void setMaterial(Material *material) = 0;

        virtual void setMesh(Subset *mesh) = 0;

        virtual void draw(Primitive primitive, size_t start, size_t count) = 0;

        virtual void beginFrame(const ClearFlags flags=ClearFlags::All, const ClearParams &params=ClearParams()) = 0;

        virtual void endFrame() = 0;

        virtual void setUniformMatrix(int location, int total, bool transpose, float *values) = 0;

        virtual void setUniform(const UniformDescriptor &desc, const void* uniform) = 0;

        virtual void setUniform(const UniformFormat* format, const void *uniforms);
    };

    typedef std::unique_ptr<Device> DevicePtr;
}}

#endif
