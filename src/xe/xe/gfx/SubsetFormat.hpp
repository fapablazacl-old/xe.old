
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
    struct SubsetAttrib : public Field {
        //! Wich buffer has the attribute
        int bufferIndex = 0;

        //! The used inside a shader
        std::string name;
        
        SubsetAttrib() {}

        SubsetAttrib(const int bufferIndex_, const DataType type_, const std::size_t dim_) {
            bufferIndex = bufferIndex_;
            type = type_;
            dim = dim_;
            name = "";
        }

        SubsetAttrib(const int bufferIndex_, const DataType type_, const std::size_t dim_, const std::string &name_) {
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
        SubsetFormat();

        SubsetFormat(std::initializer_list<SubsetAttrib> fields);

        SubsetFormat(const SubsetFormat &other);

        ~SubsetFormat();

        /**
         * @brief 
         */
        std::size_t getAttribCount() const;

        /**
         * @brief 
         */
        const SubsetAttrib& getAttrib(const std::size_t index) const;

        /**
         * @brief 
         */
        bool isEmpty() const {
            return this->getAttribCount() == 0;
        }

        /**
         * @brief 
         */
        const std::set<int>& getBufferIndices() const;

        /**
         * @brief 
         */
        const std::vector<SubsetAttrib>& getAttribArray(const int bufferIndex) const;
        
        SubsetFormat& operator= (const SubsetFormat &other);

    private:
        struct Private;
        Private *m_impl = nullptr;
    };

    typedef std::unique_ptr<SubsetFormat> SubsetFormatPtr;
}

#endif
