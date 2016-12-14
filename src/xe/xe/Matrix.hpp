
#pragma once

#ifndef __xe_matrix__
#define __xe_matrix__

#include <cassert>
#include <cmath>
#include <iostream>
#include <cassert>
#include <xe/Vector.hpp>

namespace xe {
    template<typename T, int R, int C>
    class Matrix {
    public:
        typedef Matrix<T, R, C> MatrixType;
        typedef Matrix<T, R, C> M;
        
        static const int ValueCount = R * C;
        
        static const int RowCount = R;
        static const int ColumnCount = C;

    public:
        Matrix() = default;
        
        Matrix(std::initializer_list<T> params) {
            assert(params.size() == R * C);
            
            std::copy(params.begin(), params.end(), values);
        }
        
        Matrix(std::initializer_list<Vector<T, C>> params) {
            assert(params.size() == R);
            
            int i = 0;
            for (const Vector<T, C> row : params) {
                this->setRow(i++, row);
            }
        }
        
        // accessors
        const T& get(const int i, const int j) const {
            return values[offset(i, j)];
        }

        T& get(const int i, const int j) {
            return values[offset(i, j)];
        }
        
        template<int i, int j>
        const T& get() const {
            return values[offset(i, j)];
        }

        template<int i, int j>
        T& get() {
            return values[offset(i, j)];
        }

        Vector<T, R> getColumn(const int j) const {
            assert(j >= 0);
            assert(j < R);

            Vector<T, R> result;

            for (int i=0; i<R; i++) {
                result[i] = this->get(i, j);
            }

            return result;
        }

        Vector<T, C> getRow(const int i) const {
            assert(i >= 0);
            assert(i < R);

            Vector<T, C> result;

            for (int j=0; j<C; j++) {
                result[j] = this->get(i, j);
            }

            return result;
        }

        void setColumn(const int j, const Vector<T, R> &v) {
            assert(j >= 0);
            assert(j < R);

            for (int i=0; i<R; i++) {
                this->get(i, j) = v[i];
            }
        }

        void setRow(const int i, const Vector<T, C> &v) {
            assert(i >= 0);
            assert(i < R);

            for (int j=0; j<C; j++) {
                this->get(i, j) = v[j];
            }
        }

        Matrix<T, R - 1, C - 1> getSubMatrix(const int row, const int column) const {
            assert(row >= 0);
            assert(row < R);

            assert(column >= 0);
            assert(column < C);

            Matrix<T, R-1, C-1> result;

            int ii = 0, jj = 0;

            for (int i=0; i<R; ++i) {
                if (i == row) {
                    continue;
                }

                for(int j=0; j<C; ++j) {
                    if (j == column) {
                        continue;
                    }

                    result(ii, jj) = this->get(i, j); 
                    ++jj;
                }
            
                ++ii;
                jj = 0;
            }
    
            return result;

        }

        T* getPtr() {
            return values;
        }

        const T* getPtr() const {
            return values;
        }

        // operators
        friend std::ostream& operator<< (std::ostream &os, const Matrix<T, R, C>& Other) {
            os << std::endl;

            for (int i=0; i<R; ++i) {
                os << "[";
            
                for(int j=0; j<C; ++j) {
                    os << std::fixed << std::setprecision( 4 ) << Other.get(i, j);
                
                    if (j + 1 != C) {
                        os << ", ";
                    }
                }
                os << "]" << std::endl;
            }

            os << std::endl;

            return os;
        }

        const T& operator() (const int i, const int j) const {
            return this->get(i, j);
        }

        T& operator() (const int i, const int j) {
            return this->get(i, j);
        }

        MatrixType operator*(const T factor) const {
            MatrixType result;

            for (int i=0; i<ValueCount; i++) {
                result.values[i] = factor * values[i];
            }
            
            return result;
        }

        friend MatrixType operator*(const T factor, const MatrixType &m) {
            return m * factor;
        }

        MatrixType operator/(const T factor) const {
            return (*this) * (T(1)/factor);
        }

        MatrixType operator+() const {
            return *this;
        }

        MatrixType operator-() const {
            return (*this) * T(-1);
        }

        MatrixType operator+(const MatrixType &other) const {
            MatrixType result;

            for (int i=0; i<ValueCount; i++) {
                result.values[i] = values[i] + other.values[i];
            }
            
            return result;
        }

        MatrixType operator-(const MatrixType &other) const {
            return *this + (-other);
        }   
        
        Matrix<T, R, C> operator*(const Matrix<T, R, C> &other) const {
            Matrix<T, R, C> result;

            for (int i=0; i<R; i++) {
                for (int j=0; j<C; j++) {
                    result(i, j) = dot(this->getRow(i), other.getColumn(j));
                }
            }

            return result;
        }
        
        template<int OtherR, int OtherC>
        Matrix<T, R, OtherC> operator*(const Matrix<T, OtherR, OtherC> &other) const {
            static_assert(C == OtherR, "");
            
            Matrix<T, R, OtherC> result;
            
            for (int i=0; i<R; i++) {
                for (int j=0; j<OtherC; j++) {
                    
                    const auto row = this->getRow(i);
                    const auto col = other.getColumn(j);
                    
                    result(i, j) = dot(row, col);
                }
            }

            return result;
        }
        
        MatrixType& operator+= (const MatrixType &other) {
            *this = *this + other;

            return *this;
        }

        MatrixType& operator-= (const MatrixType &other) {
            *this = *this - other;

            return *this;
        }

        MatrixType& operator*= (const MatrixType &other) {
            *this = *this * other;

            return *this;
        }

        MatrixType& operator/= (const MatrixType &other) {
            *this = *this / other;

            return *this;
        }

        MatrixType& operator*= (T factor) {
            *this = *this * factor;

            return *this;
        }

        MatrixType& operator/= (T factor) {
            *this = *this / factor;

            return *this;
        }

        MatrixType operator/ (const MatrixType &other) const {
            return (*this) * inverse(other);
        }

        bool operator== (const MatrixType &other) const {
            for (int i=0; i<ValueCount; i++) {
                if (values[i] != other.values[i]) {
                    return false;
                }
            }

            return true;
        }

        bool operator!= (const MatrixType &other) const {
            return ! (*this == other);
        }

    private:
        template<typename Type_, int Count>
        struct Determinant {
            static Type_ compute(const Matrix<Type_, Count, Count> &m) {
                Type_ factor = Type_(1);
                Type_ result = Type_(0);
                
                const int row = 0;
                
                for (int column=0; column<Count; ++column) {
                    factor = (column+1)%2 ? Type_(-1) : Type_(1);

                    Type_ subDet = abs(m.getSubMatrix(row, column));

                    result += factor * m.get(row, column) * subDet;
                }
                
                return result;
            }
        };

        template<typename Type_>
        struct Determinant<Type_, 2> {
            static Type_ compute(const Matrix<Type_, 2, 2> &m) {
                return m(0, 0)*m(1, 1) - m(1, 0)*m(0, 1);
            }
        };

    public:
        friend T abs(const Matrix<T, R, C> &m) {
            static_assert(R == C, "");

            return Determinant<T, R>::compute(m);
        }

        friend M adjoint(const M &matrix) {
            M result;
        
            for(int i=0; i<R; ++i) {
                for(int j=0; j<C; ++j) {
                    T factor = ((i+j)%2 == 1) ? T(1) : T(-1);
                    result(i, j) = factor * abs(matrix.getSubMatrix(i, j));
                }
            }
        
            return result;
        }
        
        friend Matrix<T, C, R> transpose(const Matrix<T, R, C> &other) {
            Matrix<T, C, R> result;
            
            for (int i=0; i<R; ++i) {
                for (int j=0; j<C; ++j) {
                    result.get(j, i) = other.get(i, j);
                }
            }
        
            return result;
        }

        friend MatrixType inverse(const MatrixType &m, T det) {
            return transpose(adjoint(m)) / det;
        }
        
        friend MatrixType inverse(const MatrixType &m) {
            return inverse(m, abs(m));
        }

    public:
        /**
         * @brief Build a matrix initialized with zeros.
         */
        static Matrix<T, R, C> makeZero() {
            Matrix<T, R, C> result;
            
            for(int i=0; i<R; ++i) {
                for(int j=0; j<C; ++j) {
                    result(i, j) = T(0);
                }
            }
            
            return result;
        }
        
        /**
         * @brief Build a identity matrix. Must be square.
         */
        static M makeIdentity() {
            auto result = Matrix<T, R, C>::makeZero();
            
            for (int i=0; i<R; ++i) {
                result(i, i) = T(1);
            }
            
            return result;
        }
        
        static M makeScale(const Vector<T, R> &scale) {
            auto result = M::makeIdentity();
            
            for (int i=0; i<R; ++i) {
                result(i, i) = scale[i];
            }
            
            return result;
        }
        
        static M makeTranslate(const Vector<T, R> &displace) {
            auto result = M::makeIdentity();
            
            result.setColumn(C - 1, displace);
            
            return result;
        }
        
        static M makeTranslate(const Vector<T, R - 1> &displace) {
            return M::makeTranslate(Vector<T, R>(displace, T(1)));
        }

        static M makeRotateX(const T radians) {
            auto result = M::makeIdentity();
            
            T Cos = std::cos(radians);
            T Sin = std::sin(radians);
            
            result.get(1, 1) = Cos;
            result.get(2, 2) = Cos;
            result.get(2, 1) = -Sin;
            result.get(1, 2) = Sin;
            
            return result;
        }
        
        static M makeRotateY(const T radians) {
            auto result = M::makeIdentity();
            
            T Cos = std::cos(radians);
            T Sin = std::sin(radians);
            
            result.get(0, 0) = Cos;
            result.get(2, 2) = Cos;
            result.get(2, 0) = -Sin;
            result.get(0, 2) = Sin;
            
            return result;
        }
        
        static M makeRotateZ(const T radians) {
            auto result = M::makeIdentity();
            
            T Cos = std::cos(radians);
            T Sin = std::sin(radians);
            
            result.get(0, 0) = Cos;
            result.get(1, 1) = Cos;
            result.get(1, 0) = Sin;
            result.get(0, 1) = -Sin;
            
            return result;
        }
        
        /**
         * @brief Build a arbitrary rotation matrix 
         */
        static Matrix<T, R, C> makeRotate(T radians, const Vector<T, 3> &Axis) {
            assert(!std::isnan(radians));
            assert(!std::isinf(radians));
            assert(!Axis.isZero());

            T Cos = std::cos(radians);
            T Sin = std::sin(radians);
            
            auto U = Axis;
            auto V = normalize(Axis);
            
            //auto MatS = Matrix<T, 3, 3>::makeZero();
            auto MatUut = Matrix<T, 3, 3>::makeZero();
            auto MatId = Matrix<T, 3, 3>::makeIdentity();
            
            //Iniciar S
            Matrix<T, 3, 3> MatS = {
                T(0), -V.z, V.y,
                V.z , T(0), -V.x, 
                -V.y, V.x , T(0), 
            };
            
            //auto matU = Matrix<T, 1, 3>{V};
            //auto matU_Ut = transpose(matU) * matU;
            
            //Iniciar u*ut
            MatUut.get(0, 0) = V.x * V.x;
            MatUut.get(1, 0) = V.y * V.x;
            MatUut.get(2, 0) = V.z * V.x;
        
            MatUut.get(0, 1) = V.x * V.y;
            MatUut.get(1, 1) = V.y * V.y;
            MatUut.get(2, 1) = V.z * V.y;
            
            MatUut.get(0, 2) = V.x * V.z;
            MatUut.get(1, 2) = V.y * V.z;
            MatUut.get(2, 2) = V.z * V.z;
            
            auto tempResult = MatUut + Cos * (MatId - MatUut) + Sin * MatS;
            
            auto result = M::makeIdentity();
            
            for (int i=0; i<3; ++i) {
                for (int j=0; j<3; ++j) {
                    result(i, j) = tempResult(i, j);
                }
            }
            
            return result;
        }
        
        static Matrix<T, 4, 4> makeLookat(const Vector<T, 3> &Eye, const Vector<T, 3> &At, const Vector<T, 3> &Up) {
            const auto forward = normalize(At - Eye);
            const auto side = normalize(cross(forward, Up));
            const auto up = cross(side, forward);
            
            auto result = Matrix<T, 4, 4>::makeIdentity();
            
            result.get(0, 0) = side.x;
            result.get(0, 1) = side.y;
            result.get(0, 2) = side.z;
        
            result.get(1, 0) = up.x;
            result.get(1, 1) = up.y;
            result.get(1, 2) = up.z;
        
            result.get(2, 0) = -forward.x;
            result.get(2, 1) = -forward.y;
            result.get(2, 2) = -forward.z;
            
            result *= Matrix<T, 4, 4>::makeTranslate(-Eye);
            
            return result;
        }
        
        static Matrix<T, 4, 4> makePerspective(T fov_radians, T aspect, T znear, T zfar) {
            const T f = T(1) / std::tan(fov_radians / T(2));
            const T zdiff = znear - zfar;
            
            auto result = Matrix<T, 4, 4>::makeIdentity();
            
            result.get(0, 0) = f / aspect;
            result.get(1, 1) = f;
            result.get(2, 2) = (zfar + znear) / zdiff;
            result.get(3, 2) = T(-1);
            result.get(2, 3) = (T(2)*znear * zfar) / zdiff;
            
            return result;
        }
        
        static Matrix<T, 4, 4> makeOrtho(const Vector<T, 3> &pmin,  const Vector<T, 3> &pmax) {
            
            auto diff = pmax - pmin;
            auto result = Matrix<T, 4, 4>::makeIdentity();
            
            result.get(0, 0) = T(2) / diff.x;
            result.get(1, 1) = T(2) / diff.y;
            result.get(2, 2) = T(-2) / diff.z;
            result.get(3, 3) = T(1);
            
            result.get(0, 3) = -(pmax.x + pmin.x ) / diff.x;
            result.get(1, 3) = -(pmax.y + pmin.y ) / diff.y;
            result.get(2, 3) = -(pmax.z + pmin.z ) / diff.z;
            
            return result;
        }
        
    private:
        int offset(const int i, const int j) const {
            assert(i >= 0);
            assert(i < R);

            assert(j >= 0);
            assert(j < C);

            return j * R + i;
        }
        
        template<int i, int j>
        int offset() const {
            static_assert(i >= 0, "");
            static_assert(i < R, "");

            static_assert(j >= 0, "");
            static_assert(j < C, "");

            return j * R + i;
        }

    public:
        T values[ValueCount];
    };
    
    template<typename Type, int Size>
    Vector<Type, Size> transform(const Matrix<Type, Size, Size> &m, const Vector<Type, Size> &v) {
        Vector<Type, Size> result;

        for (int i=0; i<Size; i++) {
            result[i] = dot(m.getRow(i), v);
        }

        return result;
    }

    template<typename Type, int Size>
    Vector<Type, Size - 1> transform(const Matrix<Type, Size, Size> &m, const Vector<Type, Size - 1> &v) {
        Vector<Type, Size - 1> result;

        for (int i=0; i<Size - 1; i++) {
            result[i] = dot(m.getRow(i), Vector<Type, Size>(v, Type(1)));
        }

        return result;
    }

    typedef Matrix<float, 2, 2> Matrix2f;
    typedef Matrix<float, 3, 3> Matrix3f;
    typedef Matrix<float, 4, 4> Matrix4f;

    typedef Matrix<double, 2, 2> Matrix2d;
    typedef Matrix<double, 3, 3> Matrix3d;
    typedef Matrix<double, 4, 4> Matrix4d;
}

#endif
