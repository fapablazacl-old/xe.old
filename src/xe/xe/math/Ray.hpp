
#pragma once

#ifndef __xe_ray_hpp__
#define __xe_ray_hpp__

#include <cassert>
#include "Vector.hpp"

namespace xe {

    /**
     * @brief Ray with normalized direction in the 3-space
     */
    template<typename T>
    class Ray {
    public:
        /**
         * @brief Initializes the ray, positioned around the origin, and pointing in the positive Z-axis.
         */
        Ray() {
            m_point = {T(0.0), T(0.0), T(0.0)};
            m_direction = {T(0.0), T(0.0), T(1.0)};    
        }
    
        /**
         * @brief Initialize the ray, orientated around a arbitrary origin and direction.
         */
        Ray(const xe::Vector<T, 3>& position, const xe::Vector<T, 3>& direction) {
            this->setPosition(position);
            this->setDirection(direction);
        }

        /**
         * @brief Computes the point of the ray at 't' distance from the starting point, to the 
         * direction of the ray.
         */
        Vector<T, 3> evaluate(const T t) const {
            return m_position + t*m_direction;
        }
        
        /**
         * @brief Set the starting position of the Ray.
         */
        void setPosition(const xe::Vector<T, 3> &value) {
            m_position = value;
        }

        /**
         * @brief Set the direction of the Ray. This direction must be normalized.
         */         
        void setDirection(const xe::Vector<T, 3> &value) {
            m_direction = value;
        }

        /**
         * @brief Get the starting position of the ray.
         */
        xe::Vector<T, 3> getPosition() const {
            return m_position;
        }

        /**
         * @brief Get the direction of the ray. This direction is normalized.
         */
        xe::Vector<T, 3> getDirection() const {
            return m_direction;
        }

    private:
        Vector<T, 3> m_position;
        Vector<T, 3> m_direction;
    };

    /**
     * @brief Ray template specialization for the float type
     */
    typedef Ray<float> Ray_f;

    /**
     * @brief Ray template specialization for the double type
     */
    typedef Ray<double> Ray_d;

    /**
     * @brief Get a string representation for a templated ray class
     */
    template<typename T>
    std::string to_string(const Ray<T> &ray) {
        return "Point : {" + to_string(ray.point) << "}, Direction : {" << to_string(ray.direction) << "}";
    }
}

#endif 
