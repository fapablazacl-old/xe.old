
#include "BufferType.hpp"
#include <cassert>

namespace xe {
    XE_API std::string to_string(const BufferType type) {
        switch (type) {
        case xe::BufferType::Unknown:   return "xe::BufferType::Unknown";
        case xe::BufferType::Vertex:    return "xe::BufferType::Vertex";
        case xe::BufferType::Index:     return "xe::BufferType::Index";
        default: assert(false);
        }
    }
}
