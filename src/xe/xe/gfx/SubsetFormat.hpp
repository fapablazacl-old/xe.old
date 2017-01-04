
#pragma once 

#ifndef __xe_gfx_subsetformat_hpp__
#define __xe_gfx_subsetformat_hpp__

#include <set>
#include <memory>
#include <xe/PreDef.hpp>
#include <xe/DataFormat.hpp>
#include <xe/gfx/BufferType.hpp>

namespace xe {

    /**
     * @brief Mesh attribute descriptor.
     */
    struct MeshAttrib : public Attrib {
        int bufferIndex = 0;
        
        MeshAttrib() {}

        MeshAttrib(const int bufferIndex_, const DataType type_, const std::size_t dim_) {
            bufferIndex = bufferIndex_;
            type = type_;
            dim = dim_;
            name = "";
        }

        MeshAttrib(const int bufferIndex_, const DataType type_, const std::size_t dim_, const std::string &name_) {
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

    
    /**
     * @brief Describes the Vertex Structure of a Mesh 
     */
    class XE_API SubsetFormat {
    public:
        SubsetFormat(const SubsetFormat &other) = delete;

        SubsetFormat& operator=(const SubsetFormat &other) = delete;

    public:
        SubsetFormat(std::initializer_list<MeshAttrib> attribs);
        
        ~SubsetFormat();

        /**
         * @brief 
         */
        std::size_t getAttribCount() const;

        /**
         * 
         */
        const MeshAttrib* getAttrib(const std::size_t index) const;

        /**
         * 
         */
        bool isEmpty() const {
            return this->getAttribCount() == 0;
        }

        const std::set<int>& getBufferIndices() const;

        const std::vector<MeshAttrib>& getAttribs(const int bufferIndex) const;
        
    private:
        struct Private;
        Private *m_impl = nullptr;
    };

    typedef std::unique_ptr<SubsetFormat> MeshFormatPtr;
}

#endif
