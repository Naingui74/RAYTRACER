/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** AmbientLight.hpp
*/

#pragma once

#include "ILight.hpp"
#include "Utils/Vector3.hpp"

namespace Raytracer {
    /**
     * @class AmbientLight
     * @brief Implements ambient lighting for a 3D scene.
     *
     * AmbientLight represents non-directional, uniform lighting that affects
     * all objects in the scene equally, simulating indirect illumination.
     * It inherits from ILight interface and provides basic ambient lighting functionality.
     */
    class AmbientLight : public ILight {
    public:
        /**
         * @brief Constructs an AmbientLight with specified position and intensity.
         * @param position The 3D position of the light source (though ambient light is non-directional).
         * @param intensity The intensity of the ambient light (typically between 0.0 and 1.0).
         */
        AmbientLight(const Vector3 &position, float intensity);

        /**
         * @brief Gets the light direction from a given point (always zero for ambient light).
         * @param point The point in space from which to calculate direction.
         * @return Zero vector since ambient light has no direction.
         * @note Overrides ILight::getDirectionFrom().
         */
        Vector3 getDirectionFrom(const Vector3 &point) const override;

        /**
         * @brief Gets the intensity of the ambient light.
         * @return The current intensity value.
         * @note Overrides ILight::getIntensity().
         */
        float getIntensity() const override;

    private:
        Vector3 m_position; ///< The position of the light source in 3D space
        float m_intensity;  ///< The intensity of the ambient light (0.0 to 1.0)
    };
}