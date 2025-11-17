/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** ILight
*/

#pragma once
#include "Utils/Vector3.hpp"

namespace Raytracer {
    /**
     * @class ILight
     * @brief Interface for all light sources in the raytracer.
     *
     * Defines the common interface that all light implementations must provide.
     * This abstract class serves as the base for different light types
     * (directional, point, ambient, etc.) in the rendering system.
     */
    class ILight {
    public:
        /**
         * @brief Virtual destructor for proper polymorphic destruction.
         */
        virtual ~ILight() = default;

        /**
         * @brief Gets the light direction from a specific point in space.
         * @param point The 3D point from which to calculate light direction.
         * @return Normalized direction vector from the point to the light source.
         * @note For ambient lights, this may return a zero vector.
         */
        virtual Vector3 getDirectionFrom(const Vector3 &point) const = 0;

        /**
         * @brief Gets the light intensity at a surface point.
         * @return The light intensity value (typically between 0.0 and 1.0).
         * @note For directional lights, this is usually constant.
         *       For point lights, this may vary with distance.
         */
        virtual float getIntensity() const = 0;
    };
}