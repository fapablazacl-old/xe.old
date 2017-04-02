
#pragma once

#ifndef __xe_gfx_device_hpp__
#define __xe_gfx_device_hpp__

#include <list>

#include <xe/Buffer.hpp>
#include <xe/math/Vector.hpp>
#include <xe/gfx/BufferType.hpp>
#include <xe/gfx/Subset.hpp>
#include <xe/gfx/ShaderType.hpp>
#include <xe/gfx/Program.hpp>
#include <xe/gfx/Texture.hpp>
#include <xe/gfx/UniformFormat.hpp>
#include <xe/gfx/Material.hpp>
#include <xe/gfx/Primitive.hpp>
#include <xe/input/InputManager.hpp>

namespace xe {

    /**
     * @brief The clear information used in each call to GraphicsDevice::beginFrame
     */
    struct ClearParams {
        //! Color used to clear the Color Buffer
        Vector4f color = {0.0f, 0.0f, 1.0f, 1.0f};

        //! Depth used to clear the Depth Buffer
        double depth = 1.0f;

        //! Value to clear the Stencil Buffer
        int stencil = 0;

        ClearParams() {}

        ClearParams(const Vector4f &color) 
            : color(color) {}

        ClearParams(const Vector4f &color, const double depth) 
            : color(color), depth(depth) {}

        ClearParams(const Vector4f &color, const double depth, const int stencil) 
            : color(color), depth(depth), stencil(stencil) {}
    };

    /**
     * @brief Specify wich buffer will be used to clear
     */
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

    struct BufferDesc {
        std::size_t size = 0;
        const void *data = nullptr;

        BufferDesc() = default;

        BufferDesc(const std::size_t size_, const void *data_ = nullptr) 
            : size(size_), data(data_) {}
            
        template<typename Container>
        BufferDesc(const Container& values) 
            : size(sizeof(typename Container::value_type) * values.size()), data(values.data()) {}
        
        operator bool() const {
            return size > 0;
        }
    };

    struct SubsetDesc {
        const SubsetFormat *format;
        std::vector<BufferDesc> buffersDescs;

        DataType indexType;
        BufferDesc indexBufferDesc;

        SubsetDesc(const SubsetFormat *format_, const BufferDesc &bufferDesc_, const DataType indexType_=DataType::Unknown, const BufferDesc indexBufferDesc_=BufferDesc())
            : format(format_), indexType(indexType_), indexBufferDesc(indexBufferDesc_) {
            buffersDescs.push_back(bufferDesc_);
        }

        SubsetDesc(const SubsetFormat *format_, const std::vector<BufferDesc> &buffersDescs_, const DataType indexType_=DataType::Unknown, const BufferDesc indexBufferDesc_=BufferDesc())
            : format(format_), buffersDescs(buffersDescs_), indexType(indexType_), indexBufferDesc(indexBufferDesc_) {
        }
    };

    /**
     * @brief Interpretation information for geometry buffers
     */
    struct Envelope {
        //! The primitive used for render
        Primitive primitive;   

        //! The count of vertices
        std::size_t count;

        //! The start offset used for vertex counting
        std::size_t start = 0;

        Envelope(const Primitive primitive, const std::size_t count) 
            : primitive(primitive), count(count) {}

        Envelope(const Primitive primitive, const std::size_t count, const std::size_t start) 
            : primitive(primitive), count(count), start(start) {}
    };

    class XE_API GraphicsDevice {
    public:
        virtual ~GraphicsDevice() {}

        virtual InputManager* getInputManager() = 0;

        virtual SubsetPtr createSubset(const SubsetFormat *format, std::vector<BufferPtr> buffers, const DataType indexType, BufferPtr indexBuffer) = 0;
        
        virtual SubsetPtr createSubset(const SubsetDesc &subsetDesc);
        
        virtual BufferPtr createBuffer(const BufferType type, const std::size_t size, const void *data=nullptr) = 0;

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

        virtual void setSubset(Subset *subset) = 0;

        virtual void draw(const Envelope &envelope) = 0;

        virtual void draw(const std::vector<Envelope> &envelopes);

        virtual void beginFrame(const ClearFlags flags=ClearFlags::All, const ClearParams &params=ClearParams()) = 0;

        virtual void endFrame() = 0;

        virtual void setUniformMatrix(int location, int total, bool transpose, float *values) = 0;

        virtual void setUniform(const Uniform &desc, const void* uniform) = 0;

        virtual void setUniform(const UniformFormat* format, const void *uniforms);
    };

    typedef std::unique_ptr<GraphicsDevice> GraphicsDevicePtr;
}

#endif
