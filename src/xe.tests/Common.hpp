
#pragma once

#ifndef __xe_common_hpp__
#define __xe_common_hpp__

#include <ostream>
#include <xe/math/Vector.hpp>
#include <xe/math/Quaternion.hpp>
#include <xe/math/Matrix.hpp>

namespace std {
    template<typename T, int C>
    std::ostream& operator<< (std::ostream& os, const xe::Vector<T, C> &other) {
        return (os << xe::to_string(other));
    }

    template<typename T>
    std::ostream& operator<< (std::ostream& os, const xe::Quaternion<T> &other) {
        return (os << xe::to_string(other));
    }

    template<typename T, int C, int R>
    std::ostream& operator<< (std::ostream& os, const xe::Matrix<T, C, R> &other) {
        return (os << xe::to_string(other));
    }
}

#endif
