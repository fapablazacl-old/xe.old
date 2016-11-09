
/**
 * @file Quaternion.hpp
 * @brief Inline definition of the Quaternion structure and related functions.
 */

#pragma once

#ifndef __xe_quaternion_hpp__
#define __xe_quaternion_hpp__

#include <xe/Vector.hpp>

namespace xe {
    template<typename Type>
    struct Rotation {
        Type angle = Type(0);
        Vector<Type, 3> axis = {Type(0), Type(0), Type(0)};
    };

    template<typename T>
    struct Quaternion {
        union {
            struct {
                Vector<T, 3> v;
                T w;
            };
            
            Vector<T, 4> q;
            T values[4];
            
            struct {
                T x;
                T y;
                T z;
            };
        };

        Quaternion() = default;
        
        explicit Quaternion(const T *values_) {
            std::memcpy(values, values_, sizeof(Quaternion<T>));
        }
        
        Quaternion(const T x, const T y, const T z, const T w_) {
            v.x = x;
            v.y = y;
            v.z = z;
            w = w_;
        }
        
        explicit Quaternion(const xe::Vector<T, 3> &v_) {
            v = v_;
            w = T(0);
        }
        
        Quaternion(const xe::Vector<T, 3> &v_={0, 0, 0}, T w_=T(0)) {
            v = v_;
            w = w_;
        }

        explicit Quaternion(const xe::Vector<T, 4> &q_) {
            q = q_;
        }
        
        operator Rotation<T>() const {
            T angle = T(2) * std::acos(w);

            if (angle == T(0)) {
                return {angle, {T(1), T(0), T(0)}};
            } else {    
                return {angle, normalize(v)};
            }
        }
        
        bool operator== (const Quaternion<T> &other) const {
            return q == other.q;
        }
        
        bool operator!= (const Quaternion<T> &other) const {
            return !(*this == other);
        }
        
        static Quaternion<T> makeZero() {
            return Quaternion<T>({T(0), T(0), T(0)}, T(0));
        }
        
        static Quaternion<T> makeIdentity() {
            return Quaternion<T>({T(0), T(0), T(0)}, T(1));
        }
        
        static Quaternion<T> makeRotation(const T radians, const Vector<T, 3> &axis) {
            auto q = Quaternion<T>(axis, std::cos(radians / T(2)));
            
            return normalize(q);
        }
        
        static Quaternion<T> makeRotation(const Vector<T, 3> &v1, const Vector<T, 3> &v2) {
            auto v = cross(v1, v2);
            auto w = std::sqrt(dot(v1, v1) * dot(v2, v2)) + dot(v1, v2);
            
            return normalize(Quaternion<T>(v, w));
        }
    };
    
    typedef Quaternion<float> Quaternionf;
    typedef Quaternion<double> Quaterniond;
    
    template<typename T>
    Quaternion<T> operator+ (const Quaternion<T> &q1, const Quaternion<T> &q2) {
        return {q1.v + q2.v, q1.w + q2.w};
    }
    
    template<typename T>
    Quaternion<T> operator- (const Quaternion<T> &q1, const Quaternion<T> &q2) {
        return {q1.v - q2.v, q1.w - q2.w};
    }
    
    template<typename T>
    Quaternion<T> operator- (const Quaternion<T> &q) {
        return {-q.v, -q.w};
    }
    
    template<typename T>
    Quaternion<T> operator+ (const Quaternion<T> &q) {
        return q;
    }
    
    template<typename T>
    Quaternion<T> operator * (const Quaternion<T> &q1, const Quaternion<T> &q2) {
        return {
            cross(q1.v, q2.v) + q2.v*q1.w + q1.v*q2.w,
            q1.w*q2.w - dot(q1.v, q2.v)
        };
    }
    
    template<typename T>
    Quaternion<T> operator / (const Quaternion<T> &q1, const Quaternion<T> &q2) {
        return q1 * inverse(q2);
    }
    
    template<typename T>
    Quaternion<T> operator * (const Quaternion<T> &q, const T s) {
        return {q.v*s, q.w*s};
    }
    
    template<typename T>
    Quaternion<T> operator * (const T s, const Quaternion<T> &q) {
        return q * s;
    }
    
    template<typename T>
    Quaternion<T> operator / (const Quaternion<T> &q, const T s) {
        return q * (T(1) / s);
    }
    
    template<typename T>
    Quaternion<T>& operator *= (Quaternion<T> &q, const Quaternion<T> &other) {
        return q = q * other;
    }
    
    template<typename T>
    Quaternion<T> inverse(const Quaternion<T> &q) {
        return conj(q) * norm_pow2(q);
    }

    template<typename T>
    Quaternion<T> conj(const Quaternion<T> &q) {
        return {-q.v, q.w};
    }
    
    template<typename T>
    T dot(const Quaternion<T> &q1, const Quaternion<T> &q2) {
        return dot(q1.q, q2.q);
    }
    
    template<typename T>
    T norm_pow2(const Quaternion<T> &q) {
        return dot(q, q);
    }

    template<typename T>
    T norm(const Quaternion<T> &q) {
        return std::abs(norm_pow2(q));
    }

    template<typename T>
    Quaternion<T> normalize(const Quaternion<T> &q) {
        return q / norm(q);
    }

    template<typename T>
    Vector<T, 3> transform (const Quaternion<T> &q, const Vector<T, 3> &v) {
        auto quat = q * Quaternion<T>(v) * inverse(q);
        return quat.v;
    }
}

#include <iostream>
#include <iomanip>

namespace std {
    template<typename T>
    inline std::ostream& operator<< (std::ostream &os, const xe::Quaternion<T> &q) {
        return (os << q.q);
    }
}

#endif 
