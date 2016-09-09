/**
 * @file Vector.hpp
 * @brief Vector class and companion functions definition and implementation.
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

// #define EXENG_EXPERIMENTAL

#ifndef EXENG_EXPERIMENTAL

#ifndef __EXENG_VECTOR_HPP__
#define __EXENG_VECTOR_HPP__

#include <iostream> //! TODO: Make it optional
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <cstring>

#include <xe/DataType.hpp>

#if defined(EXENG_DEBUG)
#include <stdexcept>
#endif

namespace xe { 
    template<typename Type, int size>
    struct VectorBase {
        Type values[size];
    };

    template<typename Type> 
    struct VectorBase<Type, 1> {
        union {
            Type values[1];
            struct { Type x; };
        };

        void set(Type x) {
            this->x = x;
        }

        void set(Type x, Type y) {
            this->set(x);
        }

        void set(Type x, Type y, Type z) {
             this->set(x);
        }

         void set(Type x, Type y, Type z, Type w) {
            this->set(x);
        }
    };

    template<typename Type> 
    struct VectorBase<Type, 2> {
        union {
            Type values[2];
            struct { Type x, y; };
        };

        void set(Type x, Type y) {
            this->x = x;
            this->y = y;
        }

        void set(Type x, Type y, Type z) {
             this->set(x, y);
        }

         void set(Type x, Type y, Type z, Type w) {
            this->set(x, y);
        }
    };

    template<typename Type> 
    struct VectorBase<Type, 3> {
        union {
            Type values[3];
            struct { Type x, y, z; };
        };

        void set(Type x, Type y, Type z) {
            this->x = x;
            this->y = y;
            this->z = z;
        }

         void set(Type x, Type y, Type z, Type w) {
            this->set(x, y, z);
        }
    };

    template<typename Type> 
    struct VectorBase<Type, 4> {
        union {
            Type values[4];
            struct { Type x, y, z, w; };
        };

        void set(Type x, Type y, Type z, Type w) {
            this->x = x;
            this->y = y;
            this->z = z;
            this->w = w;
        }
    };

    /**
     * @brief Base vector class
     */
    template<typename Type, int Size>
    class Vector : public VectorBase<Type, Size> {
    public:
        typedef Type type;
        static const int size = Size;

    private:
        typedef Vector<Type, Size> VectorType;

    public:
        using VectorBase<Type, Size>::set;

        Vector() {}

        Vector( const Vector<Type, Size - 1> &v, Type value) {
            for (int i=0; i<Size-1; i++) {
                VectorBase<Type, Size>::values[i] = v[i];
            }

            VectorBase<Type, Size>::values[Size-1] = value;
        }

        explicit Vector(const Type *arrayValues) {
            this->set(arrayValues);
        }

        explicit Vector(Type value) {
            this->set(value);
        }

        Vector(Type x, Type y) {
            this->set(Type());

            this->x = x;
            this->y = y;
        }

        Vector(Type x, Type y, Type z) {
            this->set(Type());

            this->x = x;
            this->y = y;
            this->z = z;
        }

        Vector(Type x, Type y, Type z, Type w) {
            this->set(Type());

            this->x = x;
            this->y = y;
            this->z = z;
            this->w = w;
        }

        void set(const Type *values) {
#if defined(EXENG_DEBUG)
            if (values == nullptr) {
                throw std::runtime_error("Vector<Type, Size>::set: Input value is a null pointer.");
            }
#endif
            std::memcpy(this->values, values, sizeof(Type)*Size);
        }

        void set(Type Value) {
            for(int i=0; i<Size; ++i) {
                this->values[i] = Value;
            }    
        }

        Type* getPtr() {
            return this->values;
        }
        
        const Type* getPtr() const {
            return this->values;
        }
        
        Type& operator[] (int index) {
#if defined(EXENG_DEBUG)
            if (index < 0 || index >= Size) {
                throw std::runtime_error("Vector<Type, Size>::operator[]: Index out of bounds.");
            }
#endif
            return this->values[index];
        }

        const Type& operator[] (int index) const {
#if defined(EXENG_DEBUG)
            if (index < 0 || index >= Size) {
                throw std::runtime_error("Vector<Type, Size>::operator[]: Index out of bounds.");
            }
#endif
            return this->values[index];
        }

        Vector operator+ (const Vector &rhs) const {
            Vector<Type, Size> result;

            for(int i=0; i<Size; ++i) {
                result.values[i] = this->values[i] + rhs.values[i];
            }
    
            return result;
        }

        Vector& operator+= (const Vector &rhs) {
            *this = *this + rhs;

            return *this;
        }

        Vector operator- (const Vector &rhs) const {
            Vector<Type, Size> result;

            for(int i=0; i<Size; ++i) {
                result.values[i] = this->values[i] - rhs.values[i];
            }
    
            return result;
        }
        
        Vector& operator-= (const Vector &rhs) {
            *this = *this - rhs;

            return *this;
        }

        Vector operator* (Type rhs) const {
            Vector<Type, Size> result;

            for(int i=0; i<Size; ++i) {
                result.values[i] = this->values[i] * rhs;
            }
    
            return result;
        }

        Vector& operator*= (Type rhs) {
            *this = *this * rhs;

            return *this;
        }

        template<typename OtherType>
        friend Vector<OtherType, Size> operator* (Type Number, const Vector& Other)  {
            return Other*Number;
        }
    
        Vector operator/ (Type rhs) const {
            Vector<Type, Size> result;

            for(int i=0; i<Size; ++i) {
                result.values[i] = this->values[i] / rhs;
            }
    
            return result;
        }
    
        Vector& operator/= (Type rhs) {
            *this = *this / rhs;

            return *this;
        }

        Vector operator* (const Vector &rhs) const {
            Vector<Type, Size> result;

            for (int i=0; i<Size; ++i) {
                result.values[i] = this->values[i] * rhs.values[i];
            }
    
            return result;
        }

        Vector& operator*= (const Vector &rhs) {
            *this = *this * rhs;

            return *this;
        }

        Vector operator/ (const Vector &rhs) const {
            Vector<Type, Size> result;

            for(int i=0; i<Size; ++i) {
                result.values[i] = this->values[i] / rhs.values[i];
            }
    
            return result;
        }

        Vector& operator/= (const Vector rhs) {
            *this = *this / rhs;

            return *this;
        }

        Vector operator- () const {
            return Type(-1)* (*this);
        }

        bool operator== (const Vector &Other) const {
            for (int i=0; i<Size; i++){
                if (this->values[i] != Other.values[i]) {
                    return false;
                }
            }

            return true;
        }

        bool operator!= (const Vector &Other) const {
            return !(*this == Other);
        }

        friend Vector<Type, Size> operator* (Type scalar, const Vector<Type, Size>& other)  {
            return other * scalar;
        }
        
        template<typename OtherType, int OtherSize>
        operator Vector<OtherType, OtherSize>() const  {
            Vector<OtherType, OtherSize> result(static_cast<OtherType>(0));
            int minSize = std::min(OtherSize, Size);
        
            for(int i=0; i<minSize; ++i) {
                result[i] = static_cast<OtherType>( this->values[i] );
            }
        
            return result;
        }
    
        bool isZero() const  {
            return *this == Vector<Type, Size>::zero();
        }
        
        static Vector zero() {
            return Vector<Type, Size>(Type());
        }

        friend std::ostream& operator<< (std::ostream &os, const Vector<Type, Size> &v)  {
            for(int i=0; i<Size; ++i) {
                os << std::fixed << std::setprecision(2) << v[i];
        
                if (i+1 != Size) {
                    os << ", ";
                }
            }
            
            return os;
        }
    };

    template<typename Type, int Size>
    Type dot(const Vector<Type, Size> &v1, const Vector<Type, Size> &v2)  {
        Type result = static_cast<Type>(0);

        for(int i=0; i<Size; ++i) {
            result += v1[i]*v2[i];
        }
    
        return result;
    }

    template<typename Type, int Size>
    Vector<Type, Size> cross(const Vector<Type, Size> &v1, const Vector<Type, Size> &v2) {
        Vector<Type, Size> result = {
            v1.y*v2.z - v1.z*v2.y, 
            v1.z*v2.x - v1.x*v2.z, 
            v1.x*v2.y - v1.y*v2.x
        };

        return result;
    }

    template<typename Type, int Size>
    Type dot(const Vector<Type, Size> &v1, const Vector<Type, Size> &v2, const Vector<Type, Size> &v3)  {
        return dot(v1, cross(v2, v3));
    }

    template<typename Type, int Size>
    Vector<Type, Size> cross(const Vector<Type, Size> &v1, const Vector<Type, Size> &v2, const Vector<Type, Size> &v3) 
    {
        return cross(v1, cross(v2, v3));
    }
    
    template<typename Type, int Size>
    Type abs2(const Vector<Type, Size> &v) 
    {
        return dot(v, v);
    }
    
    template<typename Type, int Size>
    Type abs(const Vector<Type, Size> &v) 
    {
        return std::sqrt(abs2(v));
    }
    
    template<typename Type, int Size>
    Vector<Type, Size> normalize(const Vector<Type, Size> &v)
    {
        return v / abs(v);
    }
    
    template<typename Type, int Size>
    Vector<Type, Size> maximize(const Vector<Type, Size> &v1, const Vector<Type, Size> &v2) 
    {
        Vector<Type, Size> result;

        for (int i=0; i<Size; ++i) {
            result.values[i] = std::max(v1[i], v2[i]);
        }

        return result;
    }
    
    template<typename Type, int Size>
    Vector<Type, Size> minimize(const Vector<Type, Size> &v1, const Vector<Type, Size> &v2) 
    {
        Vector<Type, Size> result;

        for (int i=0; i<Size; ++i) {
            result.values[i] = std::min(v1[i], v2[i]);
        }

        return result;
    }
    
    template<typename Type, int Size>
    Type max(const Vector<Type, Size> &v) 
    {
        Type result = v[0];

        for (int i=1; i<Size; ++i) {
            result = std::max(result, v[i]);
        }

        return result;
    }
    
    template<typename Type, int Size>
    Type min(const Vector<Type, Size> &v) 
    {
        Type result = v[0];

        for (int i=1; i<Size; ++i) {
            result = std::min(result, v[i]);
        }

        return result;
    }

    template<typename Type, int Size>
    const Vector<Type, Size> proj(const Vector<Type, Size> &v1, const Vector<Type, Size> &v2) 
    {
        return v1 * ((dot(v1, v2)/abs2(v1, v1)));
        // return (this->dot(other) / this->getMagnitudeSq()) * (*this);
    }
    
    template<typename Type, int Size>
    Vector<Type, Size> lerp(const Vector<Type, Size>& v1, const Vector<Type, Size>& v2, Type t)
    {
        return t*v2 + v1*(Type(1) - t);
    }

    template<typename Type, typename Scalar>
    Type lerp(const Type &v1, const Type &v2, Scalar t) {
        return t*v2 + v1*(Scalar(1) - t);
    }

    template<typename Type, int Size>
    Vector<Type, Size> hermite (
        const Vector<Type, Size>& V1, const Vector<Type, Size>& T1, 
        const Vector<Type, Size>& V2, const Vector<Type, Size>& T2, 
        Type t)
    {
        Type ss = t*t;
        Type sss = ss*t;

        Type _2sss = sss+sss;
        Type _3ss = ss+ss+ss;
    
        return  V1*(_2sss - _3ss + Type(t))    + 
                V2*(_3ss - _2sss) + 
                T1*(sss - (ss+ss) + t) + 
                T2*(sss - ss);
    }
    
    template<typename Type, int Size>
    bool equals(const Vector<Type, Size> &v1, const Vector<Type, Size> &v2, Type epsilon=Type()) 
    {
        for (int i=0; i<Size; ++i) {
            if ( std::abs( v1[i] - v2[i] ) > epsilon ) {
                return false;
            }
        }
        
        return true;
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

#else

#include "Array.hpp"

#ifndef __xe_vector_hpp__
#define __xe_vector_hpp__

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

        explicit Vector(const T* values) {
            std::memcpy(this->values, values, sizeof(T) * C);
        }

        explicit Vector(const T value) {
            for (size_t i=0; i<C; i++) {
                values[i] = value;
            }
        }

        explicit operator const T*() const {
            return values;
        }

        // array-like interface
        T& operator[](const size_t index) {
            assert(index < C);
            return values[index];
        }

        const T& operator[](const size_t index) const {
            assert(index < C);
            return values[index];
        }

        constexpr size_t size() const {
            return count;
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
    T dot(const Vector<T, 3> &v1, const Vector<T, 3> &v2, const Vector<T, 3> &v3) {
        return dot(cross(v1, v2), v3);
    }

    template<typename T>
    Vector<T, 3> dot(const Vector<T, 3> &v1, const Vector<T, 3> &v2, const Vector<T, 3> &v3) {
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

#endif
