/**
 * @file PointLight.hpp
 * @brief Point light implementation for the raytracer
 * @author EPITECH
 * @date 2025
 *
 * This file contains the PointLight class which implements the ILight interface.
 * It represents a point light source in 3D space that emits light equally in all directions.
 * The light intensity decreases with distance according to the inverse square law.
 */

#pragma once

#include "Lights/ILight.hpp"
#include "Utils/Vector3.hpp"

namespace Raytracer {
    class PointLight : public ILight {
    public:
      PointLight(const Vector3 &position, float intensity = 1.0f);

        /**
         * @brief Get the direction vector from a point to this light
         *
         * @param point The point from which to calculate the direction
         * @return Vector3 Normalized direction vector pointing toward the light
         */
        Vector3 getDirectionFrom(const Vector3 &point) const override;

        /**
         * @brief Get the intensity of the light
         *
         * @return float The intensity value of the light
         */
        float getIntensity() const override;

        /**
         * @brief Get the position of the light source
         *
         * @return Vector3 The 3D position of the light
         */
        Vector3 getPosition() const
        {return m_position;}
    private:
        Vector3 m_position;  /**< The position of the light in 3D space */
        float m_intensity;   /**< The base intensity of the light */
    };
}