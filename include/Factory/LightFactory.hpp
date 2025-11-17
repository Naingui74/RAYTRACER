/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** LightFactory.hpp
*/

#pragma once

#include <memory>
#include "Lights/ILight.hpp"
#include "Utils/Vector3.hpp"

namespace Raytracer {
    /**
     * @class LightFactory
     * @brief Factory class for creating different types of light sources.
     *
     * Provides static methods to create various types of lights used in the scene.
     * Implements the Factory design pattern to encapsulate light creation logic.
     */
    class LightFactory {
    public:
      static std::shared_ptr<ILight> createAmbientLight(const Vector3& position, float intensity = 0.1f);
      static std::shared_ptr<ILight> createPointLight(const Vector3& position, float intensity = 1.0f);
      static std::shared_ptr<ILight> createDirectionalLight(const Vector3& position, const Vector3& direction, float intensity = 1.0f);
      static std::shared_ptr<ILight> createCompositeLight();
  };
}
