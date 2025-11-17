/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** DirectionalLight
*/

#pragma once

#include "Lights/ILight.hpp"
#include "Utils/Vector3.hpp"

namespace Raytracer {
    /**
     * @class DirectionalLight
     * @brief Implements directional lighting for a 3D scene.
     *
     * DirectionalLight represents a light source with parallel rays coming from
     * a specific direction, simulating distant light sources like the sun.
     * The light intensity is constant regardless of distance from the source.
     */
    class DirectionalLight : public ILight {
    public:
      DirectionalLight(const Vector3 &position, const Vector3 &direction, float intensity = 1.0f);

        /**
         * @brief Gets the light direction from any point in space.
         * @param point The point in space (unused for directional light).
         * @return Constant light direction vector (normalized).
         * @note The direction is the same for all points in space.
         */
        Vector3 getDirectionFrom(const Vector3 &point) const override;

        /**
         * @brief Gets the intensity of the directional light.
         * @return Constant intensity value (1.0 by default for directional lights).
         */
        float getIntensity() const override;

    private:
        Vector3 m_position;   ///< Origin position of the light source
        Vector3 m_direction;  ///< Normalized direction vector of light rays
        float m_intensity;    ///< Constant light intensity (default 1.0)
    };
}