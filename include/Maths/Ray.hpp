/**

 * @file Ray.hpp
 * @brief Ray class implementation for the raytracer
 * @author EPITECH
 * @date 2025
 *
 * This file contains the Ray class which represents a ray in 3D space.
 * A ray is defined by an origin point and a direction vector.
 */

#pragma once

#include "Utils/Vector3.hpp"

namespace Raytracer {
    /**
     * @class Ray
     * @brief Represents a ray in 3D space
     *
     * A ray is defined by an origin point and a direction vector.
     * It is used for ray-primitive intersection calculations in the raytracer.
     */
    class Ray {
    public:
        /**
         * @brief Construct a new Ray object
         *
         * @param origin The origin point of the ray
         * @param direction The direction vector of the ray (should be normalized)
         */
        Ray(const Vector3 &origin, const Vector3 &direction);

        /**
         * @brief Get the origin of the ray
         *
         * @return const Vector3& The origin point
         */
        const Vector3 &getOrigin() const;

        /**
         * @brief Get the direction of the ray
         *
         * @return const Vector3& The direction vector
         */
        const Vector3 &getDirection() const;

        /**
         * @brief Compute a point along the ray
         *
         * @param t The parameter along the ray (t >= 0)
         * @return Vector3 The point at origin + t * direction
         */
        Vector3 at(float t) const;

    private:
        Vector3 m_origin;    /**< The origin point of the ray */
        Vector3 m_direction; /**< The direction vector of the ray (normalized) */
    };
}