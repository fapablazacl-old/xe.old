
#pragma once

#ifndef __xe_vector_hpp__
#define __xe_vector_hpp__

#include "Array.hpp"
#include <cstring>
#include <string>
#include <cmath>

namespace xe { 
    template<typename T, size_t Count>
    struct VectorStorage {
        T values[Count];

        VectorStorage() {}
    };
    
    template<typename T>
    struct VectorStorage<T, 2> {
        union {
            T values[2];

            struct {T x, y;};
        };

        VectorStorage() {}

        VectorStorage(T x, T y) {
            this->x = x;
            this->y = y;
        }
    };

    template<typename T>
    struct VectorStorage<T, 3> {
        union {
            T values[3];

            struct {T x, y, z;};
        };

        VectorStorage() {}

        VectorStorage(T x, T y, T z) {
            this->x = x;
            this->y = y;
            this->z = z;
        }
    };

    template<typename T>
    struct VectorStorage<T, 4> {
        union {
            T values[4];

            struct {T x, y, z, w;};
        };

        VectorStorage() {}

        VectorStorage(T x, T y, T z, T w) {
            this->x = x;
            this->y = y;
            this->z = z;
            this->w = w;
        }
    };

    template<typename T, size_t C> 
    struct Vector : public VectorStorage<T, C> {
        using VectorStorage<T, C>::VectorStorage;

        Vector() {}
        
        Vector(const Vector<T, C-1> &other, T last) {
            for (size_t i=0; i<C-1; i++) {
                this->values[i] = other.values[i];
            }
            
            this->values[C-1] = last;
        }
        
        Vector(T first, const Vector<T, C-1> &remaining) {
            this->values[0] = first;
            
            for (size_t i=0; i<C-1; i++) {
                this->values[i + 1] = remaining.values[i];
            }
        }
        
        explicit Vector(const T* values) {
            std::memcpy(this->values, values, sizeof(T) * C);
        }

        explicit Vector(const T value) {
            for (size_t i=0; i<C; i++) {
                this->values[i] = value;
            }
        }
        
        explicit operator const T*() const {
            return this->values;
        }

        // array-like interface
        T& operator[](const size_t index) {
            assert(index < C);
            return this->values[index];
        }

        const T operator[](const size_t index) const {
            assert(index < C);
            return this->values[index];
        }

        constexpr size_t size() const {
            return C;
        }

        bool isZero() const {
            for (const auto value : this->values) {
                if (value != T(0)) {
                    return false;
                }
            }

            return true;
        }
    };

    template<typename T, size_t C> 
    Vector<T, C> operator+ (const Vector<T, C> &v1, const Vector<T, C> &v2) {
        return add(v1, v2);
    }

    template<typename T, size_t C> 
    Vector<T, C> operator- (const Vector<T, C> &v1, const Vector<T, C> &v2) {
        return sub(v1, v2);
    }
    
    template<typename T, size_t C> 
    Vector<T, C> operator- (const Vector<T, C> &v) {
        return v * T(-1);
    }
    
    template<typename T, size_t C> 
    Vector<T, C> operator* (const Vector<T, C> &v1, const Vector<T, C> &v2) {
        return mul(v1, v2);
    }

    template<typename T, size_t C> 
    Vector<T, C> operator/ (const Vector<T, C> &v1, const Vector<T, C> &v2) {
        return div(v1, v2);
    }
    
    template<typename T, size_t C> 
    Vector<T, C> operator* (const Vector<T, C> &v1, const T value) {
        return mul<Vector, T, C>(v1, value);
    }

    template<typename T, size_t C> 
    Vector<T, C> operator* (const T value, const Vector<T, C> &v1) {
        return mul(v1, value);
    }

    template<typename T, size_t C> 
    Vector<T, C> operator/ (const Vector<T, C> &v1, const T value) {
        return div(v1, value);
    }

    template<typename T, size_t C> 
    Vector<T, C>& operator+= (Vector<T, C> &v1, const Vector<T, C> &v2) {
        return v1 = add(v1, v2);
    }

    template<typename T, size_t C> 
    Vector<T, C>& operator-= (Vector<T, C> &v1, const Vector<T, C> &v2) {
        return v1 = sub(v1, v2);
    }

    template<typename T, size_t C> 
    Vector<T, C>& operator*= (Vector<T, C> &v1, const Vector<T, C> &v2) {
        return v1 = mul(v1, v2);
    }

    template<typename T, size_t C> 
    Vector<T, C>& operator/= (Vector<T, C> &v1, const Vector<T, C> &v2) {
        return v1 = div(v1, v2);
    }

    template<typename T, size_t C> 
    Vector<T, C>& operator*= (Vector<T, C> &v1, const T value) {
        return v1 = mul(v1, value);
    }

    template<typename T, size_t C> 
    Vector<T, C>& operator/= (Vector<T, C> &v1, const T value) {
        return v1 = div(v1, value);
    }

    template<typename T, size_t C>
    bool operator== (const Vector<T, C> &v1, const Vector<T, C> &v2) {
        auto result = compare<Vector, T, C, equal>(v1, v2);

        for (int i=0; i<C; i++) {
            if (!result[i]) {
                return false;
            }
        }

        return true;
    }

    template<typename T, size_t C>
    bool operator!= (const Vector<T, C> &v1, const Vector<T, C> &v2) {
        return ! (v1 == v2);
    }

    template<typename T, size_t C>
    T dot(const Vector<T, C> &v1, const Vector<T, C> &v2) {
        T result = T(0);

        for (size_t i=0; i<C; i++) {
            result += v1[i]*v2[i];
        }

        return result;
    }

    template<typename T>
    Vector<T, 3> cross(const Vector<T, 3> &v1, const Vector<T, 3> &v2) {
        return {
            v1.y*v2.z - v1.z*v2.y, 
            v1.z*v2.x - v1.x*v2.z, 
            v1.x*v2.y - v1.y*v2.x
        };
    }
    
    template<typename T>
    T cross(const Vector<T, 2> &v1, const Vector<T, 2> &v2) {
        return v1.x*v2.y - v1.y*v2.x;
    }
    
    template<typename T>
    T dot(const Vector<T, 3> &v1, const Vector<T, 3> &v2, const Vector<T, 3> &v3) {
        return dot(cross(v1, v2), v3);
    }

    template<typename T>
    Vector<T, 3> cross(const Vector<T, 3> &v1, const Vector<T, 3> &v2, const Vector<T, 3> &v3) {
        return cross(cross(v1, v2), v3);
    }

    template<typename T, size_t C>
    T norm_pow2(const Vector<T, C> &v) {
        return dot(v, v);
    }

    template<typename T, size_t C>
    T norm(const Vector<T, C> &v) {
        return std::sqrt(norm_pow2(v));
    }

    template<typename T, size_t C>
    Vector<T, C> normalize(const Vector<T, C> &v) {
        return v / norm(v);
    }

    template<typename T, size_t C>
    Vector<T, C> proj(const Vector<T, C> &v1, const Vector<T, C> &v2) {
        return v1 * ((dot(v1, v2) / norm_pow2(v1, v1)));
    }

    template<typename T, int C>
    Vector<T, C> lerp(const Vector<T, C>& v1, const Vector<T, C>& v2, T t) {
        return t*v2 + v1*(T(1) - t);
    }

    template<typename T, typename S>
    T lerp(const T &v1, const T &v2, S t) {
        return t*v2 + v1*(S(1) - t);
    }

    template<typename T, int C>
    Vector<T, C> hermite (const Vector<T, C>& V1, const Vector<T, C>& T1, const Vector<T, C>& V2, const Vector<T, C>& T2, T t) {
        T ss = t*t;
        T sss = ss*t;

        T _2sss = sss + sss;
        T _3ss = ss + ss + ss;
    
        return  V1*(_2sss - _3ss + T(t)) + 
                V2*(_3ss - _2sss) + 
                T1*(sss - (ss + ss) + t) + 
                T2*(sss - ss);
    }

    template<typename T, int C>
    Vector<T, C> maximize (const Vector<T, C> &v1, const Vector<T, C> &v2) {
        return operate<Vector, T, C, std::max>(v1, v2);
    }

    template<typename T, int C>
    Vector<T, C> minimize (const Vector<T, C> &v1, const Vector<T, C> &v2) {
        return operate<Vector, T, C, std::min>(v1, v2);
    }

    template<typename T, int C>
    std::string to_string(const Vector<T, C> &v) {
        std::string str;

        for(std::size_t i=0; i<C; ++i) {
            str += v[i];
    
            if (i+1 != C) {
                str += ", ";
            }
        }

        return str;
    }

    typedef Vector<float, 2> Vector2f;
    typedef Vector<float, 3> Vector3f;
    typedef Vector<float, 4> Vector4f;

    typedef Vector<double, 2> Vector2d;
    typedef Vector<double, 3> Vector3d;
    typedef Vector<double, 4> Vector4d;

    typedef Vector<int, 2> Vector2i;
    typedef Vector<int, 3> Vector3i;
    typedef Vector<int, 4> Vector4i;

    typedef Vector<unsigned char, 2> Vector2ub;
    typedef Vector<unsigned char, 3> Vector3ub;
    typedef Vector<unsigned char, 4> Vector4ub;
}

#endif
