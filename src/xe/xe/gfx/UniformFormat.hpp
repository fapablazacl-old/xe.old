
#pragma once

#include "xe/DataType.hpp"
#include "xe/DataFormat.hpp"

namespace xe {
    /**
     * @brief The Uniform structure hold the information needed to interpret a memory address in the call GraphicsDevice::setUniform.
     */
    struct Uniform : public Field {

        //! The used inside a shader
        std::string name;

        //! How many elements has an Uniform.
        std::size_t count = 0; 

        std::size_t getSize() const {
            return count * Field::getSize();
        }

        Uniform() {}

        Uniform(const std::string name_, size_t dim_, DataType type_, size_t count_=1) {
            name = name_;
            dim = dim_;
            type = type_;
            count = count_;
        }
    };
    
    typedef xe::Struct<Uniform> UniformFormat;
}
