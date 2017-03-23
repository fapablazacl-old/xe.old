
#pragma once

#ifndef __xe_sphere_hpp__
#define __xe_sphere_hpp__

#include "Vector.hpp"

namespace xe {

    /**
     * @brief Sphere in the 3-space
     */
    template<typename T>
    class Sphere {
    public:
        /**
         * @brief Initializes a sphere in the origin with a 1.0 radius
         */ 
        Sphere() {
            this->setRadius(T(1));
        }
    
        /**
         * @brief Initializes a sphere in the origin with the specified radius
         */
        explicit Sphere(T radius) {
            this->setRadius(radius);
        }
    
        /**
         * @brief Initializes a Sphere from the given center and radius
         */
        Sphere(T radius, const Vector<T, 3> &center) {
            this->setCenter(center)
            this->setRadius(radius);
        }
        
        /**
         * @brief Sets the Sphere radius.
         */
        void setRadius(T radius) {
            m_radius = radius;
        }
    
        /**
         * @brief Sets the location of the center of the sphere
         */
        void setCenter(const Vector<T, 3> &center) {
            m_center = center;
        }
    
        /**
         * @brief Get the radius of the sphere
         */
        T getRadius() const {
            return m_radius;
        }
    
        /**
         * @brief Get the center location of the sphere
         */
        Vector<T, 3> getCenter() const {
            return m_center;
        }
        
        /**
         * @brief Checks if two spheres are equal
         */
        bool operator== (const Sphere<T> &other) const {
            if (m_radius != other.m_radius) {
                return false;
            }

            if (m_center != other.m_center) {
                return false;
            }

            return true;
        }
    
        /**
         * @brief Checks if two spheres non equal
         */
        bool operator!= (const Sphere<T> &other) const {
            return !(*this == other);
        }
    
    private:
        Vector<T, 3> m_center;
        T m_radius;        
    };

    /**
     * @brief Get a string representation of the Sphere
     */
    template<typename T>
    std::string to_string(const Sphere<T> &s) {
        return to_string(sphere.getCenter()) + ", " + std::to_string(s.getRadius());
    }

    /*
    inline bool Sphere::intersect(const Ray& ray, IntersectInfo *intersectInfo) const {
    
        // Variables de apoyo al algoritmo
        float t;
        bool result = false;

        // Variables del modelo matematico
        auto r0 = ray.getPoint();
        auto d = ray.getDirection();

        auto c = this->getCenter();
        auto r = this->getRadius();

        // Temporales para ahorrar calculos
        auto r_2 = r*r;

        auto r0_sub_c = r0 - c;
        auto r0_c_2 = abs2(r0_sub_c);

        // Temporales de la ecuacion cuadratica
        auto B = 2.0f * dot(d, r0_sub_c);
        auto C = r0_c_2 - r_2;

        // Calcular el discriminante
        auto disc = B*B - 4.0f*C;
    
        if (disc == 0.0f) {
            // Solo existe un punto de interseccion (el rayo es tangente a la esfera)
            t = -B / 2.0f;
        
            // Ver si el punto esta "adelante" del rayo, y no detras
            if (t > 0.0f) {
                result = true;
            }
        } else if (disc > 0.0f) {
            // Existen dos puntos de interseccion 
            auto rootDisc = std::sqrt(disc);

            // Determinar el primer punto de interseccion
            float t1 = ( -B - rootDisc ) / 2.0f;
            float t2 = ( -B + rootDisc ) / 2.0f;
        
            t = std::min(t1, t2);

            if (t > 0.0f) {
                result = true;
            }
        } else {
            // El rayo no toca a la esfera, ni por delante no por detras (caso mas comun)
            result = false;
        }
    
        // Rellenar la estructura con la informacion sobre las colisiones
        if (intersectInfo != nullptr) {
            intersectInfo->intersect = result;

            if (intersectInfo->intersect == true) {
                intersectInfo->normal = normalize(ray.getPointAt(t));
                intersectInfo->distance = t;
            }
        }
    
        return result;
    }
    */
}

#endif
