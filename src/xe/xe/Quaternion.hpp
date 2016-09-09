
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

    template<typename Type>
    struct Quaternion {
        union {
            struct {
                Vector<Type, 3> v;
                Type w;
            };
            Vector<Type, 4> q;
            Type values[4];
        };

        Quaternion(const xe::Vector<Type, 3> &v_={0, 0, 0}, Type w_=Type(0)) {
            v.x = v_.x;
            v.y = v_.y;
            v.z = v_.z;
            w = w_;
        }

        Quaternion(const xe::Vector<Type, 3> &v1, const xe::Vector<Type, 3> &v2) {
            v = cross(v1, v2);
            w = std::sqrt(dot(v1, v1) * dot(v2, v2)) + dot(v1, v2);

            *this = normalize(*this);
        }

        explicit Quaternion(const xe::Vector<Type, 4> &q_) {
            q = q_;
        }

        explicit Quaternion(const Rotation<Type> &r) {
            v = r.axis;
            w = std::cos(r.angle * Type(0.5));

            *this = normalize(*this);
        }

        operator Rotation<Type>() const {
            Type angle = Type(2) * std::acos(w);

            if (angle == Type(0)) {
                return {angle, {Type(1), Type(0), Type(0)}};
            } else {    
                return {angle, normalize(v)};
            }
        }

        Quaternion<Type> operator* (const Quaternion<Type> &other) const {
            return Quaternion (
                cross(v, other.v) + other.v*w + v*other.w,
                w*other.w - dot(v, other.v)
            );
        }

        //Quaternion<Type> operator* (const Quaternion<Type> &other) const {
        //    return *this * inverse(other);
        //}

        Quaternion<Type> operator* (Type s) const {
            return Quaternion(v * s);
        }
        
        Quaternion<Type> operator/ (Type s) const {
            return Quaternion(v * (Type(1) / s));
        }

        Quaternion<Type>& operator*= (const Quaternion<Type> &other) {
            *this = *this * other;
            return *this;
        }

        friend Quaternion<Type> inverse(const Quaternion<Type> &q) {
            return conj(q) * norm_pow2(q);
        }

        friend Quaternion<Type> conj(const Quaternion<Type> &q) {
            return {-q.v, q.w};
        }

        friend Type norm_pow2(const Quaternion<Type> &q) {
            return dot(q.q, q.q);
        }

        friend Type norm(const Quaternion<Type> &q) {
            return std::abs(norm_pow2(q));
        }

        friend Quaternion<Type> normalize(const Quaternion<Type> &q) {
            return q / norm(q);
        }

        friend Vector<Type, 3> transform (const Quaternion<Type> &q, const Vector<Type, 3> &v) {
            auto quat = q * Quaternion(v, Type(0)) * inverse(q);
            return quat.v;
        }
    };
}

#endif 
