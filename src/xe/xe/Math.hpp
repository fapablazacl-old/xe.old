
#pragma once

#ifndef __xe_math_hpp__
#define __xe_math_hpp__

#include <cmath>

namespace xe {
    static const float pi = 3.14159265358979f;

    inline float radians(const float degrees) {
        return pi * degrees / 180.0f;
    }

    inline float degrees(const float radians) {
        return radians * 180.0f / pi;
    }
}

#endif 
