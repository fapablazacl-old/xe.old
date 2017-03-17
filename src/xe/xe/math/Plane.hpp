
#pragma once

#ifndef __xe_plane_hpp__
#define __xe_plane_hpp__

#include "Vector.hpp"

namespace xe {
    
    /**
     * @brief Plane on 3-space.
     */
    template<typename T>
    class Plane {
    public:

        /**
         * @brief Initialize a default plane located at the origin of the space, pointing on the positive Y-Axis.
         */
        Plane() {
            m_position = {T(0.0), T(0.0), T(0.0)};
            m_normal = {T(0.0), T(1.0, T(0.0)};
        }
    
        /**
         * @brief Initialize a plane with position and normal specified by the application.
         */
        Plane(const xe::Vector<T, 3>& position, const xe::Vector<T, 3>& normal) {
            this->setPosition(position);
            this->setNormal(normal);
        }
        
        /**
         * @brief Initialize a plane from three points. These points must be coplanar.
         */
        Plane(const xe::Vector<T, 3>& p1, const xe::Vector<T, 3>& p2, const xe::Vector<T, 3>& p3) {
            const float factor = 1.0f/3.0f;
            
            this->setPosition(factor * (p1 + p2 + p3));
            this->setNormal(cross(p2 - p1, p3 - p1));
        }

        /**
         * @brief Set the location of the plane
         */
        void setPosition(const xe::Vector<T, 3> &position) {
            m_position = position;
        }

        /**
         * @brief Set the normal of the plane
         */
        void setNormal(const xe::Vector<T, 3> &normal) {
            m_normal = normal;
        }

        /**
         * @brief Get the location of the plane
         */
        Vector<T, 3> getPosition() const {
            return m_position;
        }

        /**
         * @brief Get the normal of the plane
         */
        Vector<T, 3> getNormal() const {
            return m_normal;
        }

        /**
         * @brief Check if the current plane intersects with the 
         */
        /*
        inline bool Plane::intersect(const Ray& ray, IntersectInfo* intersectInfo) const {
            auto p = this->point;
            auto n = this->normal;
        
            auto r = ray.point;
            auto d = ray.direction;
        
            auto t = dot(n, p - r) / dot(n, d);
            
            bool result = false;
        
            if (t > 0.0f) {
                result = true;
            }
        
            if (intersectInfo) {
                intersectInfo->intersect = result;
                intersectInfo->distance = t;
                intersectInfo->normal = this->normal;
                intersectInfo->point = ray.getPointAt(t);
            }
        
            return result;
        }
        */
    private:
        xe::Vector<T, 3> m_position;
        xe::Vector<T, 3> m_normal;
    };

    /**
     * @brief Plane specialization for floats
     */
    typedef Plane<float> Plane_f;

    /**
     * @brief Plane specialization for doubles
     */
    typedef Plane<double> Plane_d;

    /**
     * @brief Get a string representation of a plane.
     */
    template<typename T>
    std::string to_string(const Plane<T> &plane) {
        return os << "Point : {" << plane.point << "}, Normal : {" << plane.normal << "}";
    }
}

#endif
