
#pragma once 

#ifndef __xe_gfx_meshformat_hpp__
#define __xe_gfx_meshformat_hpp__

#include <set>
#include <xe/PreDef.hpp>
#include <xe/DataFormat.hpp>
#include <xe/gfx/BufferType.hpp>

namespace xe { namespace gfx {

    /**
     * @brief Mesh attribute descriptor.
     */
    struct MeshAttrib : public Attrib {
        BufferType bufferType;
        int bufferIndex = 0;
        
        MeshAttrib() {}

        MeshAttrib(const BufferType bufferType_, const int bufferIndex_, const DataType type_, const std::size_t dim_) {
            bufferType = bufferType_;
            bufferIndex = bufferIndex_;
            type = type_;
            dim = dim_;
            name = "";
        }

        MeshAttrib(const BufferType bufferType_, const int bufferIndex_, const DataType type_, const std::size_t dim_, const std::string &name_) {
            bufferType = bufferType_;
            bufferIndex = bufferIndex_;
            type = type_;
            dim = dim_;
            name = name_;
        }

        bool isValid() const {
            if (type == DataType::Unknown) {
                return false;
            }

            if (dim <= 0)  {
                return false;
            }

            return true;
        }
    };

    class XE_API MeshFormat {
    public:
        MeshFormat(const MeshFormat &other) = delete;

        MeshFormat& operator=(const MeshFormat &other) = delete;

    public:
        MeshFormat(std::initializer_list<MeshAttrib> attribs);
        
        ~MeshFormat();

        std::size_t getAttribCount() const;

        const MeshAttrib* getAttrib(const std::size_t index) const;

        bool isEmpty() const {
            return this->getAttribCount() == 0;
        }

        bool isValid() const;

        const std::set<int>& getBufferIndices() const;

        const std::vector<MeshAttrib>& getAttribs(const int bufferIndex) const;

        bool isIndexed() const;

    private:
        struct Private;
        Private *m_impl = nullptr;
    };
}}

#endif
