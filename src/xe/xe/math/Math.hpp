
#pragma once

#ifndef __xe_math_hpp__
#define __xe_math_hpp__

#include <cmath>

namespace xe {
    template<typename T>
    static const T pi = T(3.14159265358979);

    template<typename T>
    inline T radians(const T degrees) {
        return pi<T> * degrees / T(180.0);
    }

    template<typename T>
    inline T degrees(const T radians) {
        return radians * T(180.0) / pi<T>;
    }
}

#endif 
