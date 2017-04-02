
#pragma once

#ifndef __xe_dataformat_hpp__
#define __xe_dataformat_hpp__

#include <vector>
#include <string>
#include "xe/DataType.hpp"
#include "xe/Traits.hpp"

namespace xe {

    /**
     * @brief Structure field descriptor
     */
    struct Field {
        //! The data type for the field
        DataType type = DataType::Unknown;

        //! The number of elements for the field
        std::size_t dim = 1;
        
        /**
         * @brief Compute the storage size in bytes
         */
        std::size_t getSize() const {
            return dim * xe::getSize(type);
        }

        Field() {}

        Field(const DataType type) 
            : type(type) {}

        Field(const DataType type, const std::size_t dim) 
            : type(type), dim(dim) {}
    };

    /**
     * @brief Structure descriptor
     */
    template<typename FieldType>
    struct Struct {
        typedef std::vector<FieldType> FieldVector;

        FieldVector fields;
        
        Struct() {}
        Struct(const std::vector<FieldType> &attribs_) : fields(attribs_) {}
        
        /**
         * @brief Compute the storage size in bytes
         */
        std::size_t getSize() const {
            std::size_t size = 0;

            for (const DataAttrib &attrib : fields) {
                size += attrib.getSize();
            }

            return size;
        }
    };
}

#endif
