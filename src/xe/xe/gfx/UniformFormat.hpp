
#pragma once

#include "xe/DataType.hpp"
#include "xe/DataFormat.hpp"

namespace xe {
    struct UniformDescriptor : public xe::Attrib {
        size_t count = 0;   //! How many elements has the array

        size_t getSize() const {
            return count * xe::Attrib::getSize();
        }

        UniformDescriptor() {}

        UniformDescriptor(const std::string name_, size_t dim_, DataType type_, size_t count_=1) {
            name = name_;
            dim = dim_;
            type = type_;
            count = count_;
        }
    };
    
    typedef xe::DataFormat<UniformDescriptor> UniformFormat;
}
