
#pragma once

#ifndef __xe_gfx_subset__
#define __xe_gfx_subset__

#include <xe/Buffer.hpp>
#include <xe/DataFormat.hpp>
#include <xe/gfx/BufferType.hpp>

namespace xe { namespace gfx {

    /**
     * @brief Mesh attribute descriptor.
     */
    struct MeshAttrib : public Attrib {
        int bufferIndex = 0;
        BufferType bufferType = BufferType::Unknown;

        MeshAttrib() {}

        MeshAttrib(const int bufferIndex_, const BufferType bufferType_, const DataType type_) {
            bufferIndex = bufferIndex_;
            bufferType = bufferType_;
            type = type_;
            dim = 1;
            name = "";
        }

        MeshAttrib(const int bufferIndex_, const BufferType bufferType_, const DataType type_, const std::size_t dim_, const std::string &name_) {
            bufferIndex = bufferIndex_;
            bufferType = bufferType_;
            type = type_;
            dim = dim_;
            name = name_;
        }

        static MeshAttrib VertexAttrib(const int bufferIndex, const DataType type, const std::size_t dim, const std::string &name) {
            return MeshAttrib(bufferIndex, BufferType::Vertex, type, dim, name);
        }

        static MeshAttrib IndexAttrib(const int bufferIndex, const DataType type) {
            assert(type == DataType::UInt16 || type == DataType::UInt32);

            return MeshAttrib(bufferIndex, BufferType::Index, type);
        }
    };

    typedef xe::DataFormat<MeshAttrib> MeshFormat;

    /**
     * @brief Abstract geometry mesh interface
     */
    class XE_API Mesh {
    public:
        virtual ~Mesh() {}

        virtual MeshFormat getFormat() const = 0;

        virtual std::size_t getBufferCount() const = 0;
        virtual Buffer* getBuffer(const std::size_t index) = 0;
        virtual const Buffer* getBuffer(const std::size_t index) const = 0;

        virtual bool isIndexed() const;
    };

    typedef std::unique_ptr<Mesh> MeshPtr;
}}

#endif 
