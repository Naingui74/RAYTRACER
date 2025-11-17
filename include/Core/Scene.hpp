/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Scene
*/

#pragma once

#include <memory>
#include <vector>
#include "Core/Camera.hpp"
#include "Lights/ILight.hpp"
#include "Primitives/IPrimitive.hpp"
#include "Primitives/CompositePrimitive.hpp"
#include "Lights/CompositeLight.hpp"

namespace Raytracer {
    /**
     * @class Scene
     * @brief Represents a 3D scene containing camera, objects, and lights.
     *
     * The Scene class manages all elements of a 3D scene including the camera,
     * geometric primitives (objects), light sources, and ambient lighting.
     */
    class Scene {
    public:
      Scene();
      void setCamera(const Camera& cam);
      const Camera& getCamera() const;
      
      // Méthodes pour ajouter des primitives
      void addPrimitive(std::shared_ptr<IPrimitive> primitive);
      const std::vector<std::shared_ptr<IPrimitive>>& getPrimitives() const;
      
      // Accès au composite principal des primitives
      std::shared_ptr<CompositePrimitive> getRootCompositePrimitive() const;
      
      // Méthodes pour ajouter des lumières
      void addLight(std::shared_ptr<ILight> light);
      const std::vector<std::shared_ptr<ILight>>& getLights() const;
      
      // Accès au composite principal des lumières
      std::shared_ptr<CompositeLight> getRootCompositeLight() const;
      
      void setAmbientIntensity(float intensity);
      Camera& getCamera();
      float getAmbientIntensity() const;

    private:
      Camera m_camera;
      std::vector<std::shared_ptr<IPrimitive>> m_primitives;
      std::shared_ptr<CompositePrimitive> m_rootCompositePrimitive;
      std::vector<std::shared_ptr<ILight>> m_lights;
      std::shared_ptr<CompositeLight> m_rootCompositeLight;
      float m_ambientIntensity = 0.0f;
  };
}
