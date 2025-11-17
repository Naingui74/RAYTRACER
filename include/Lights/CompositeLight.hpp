/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** CompositeLight
*/

#pragma once

#include "Lights/ILight.hpp"
#include <vector>
#include <memory>

namespace Raytracer {
  /**
   * @class CompositeLight
   * @brief Implements the Composite pattern for light sources
   * 
   * This class allows grouping multiple light sources and treating them as a single entity.
   * It's an implementation of the Composite design pattern, which enables creating a tree
   * structure of light objects in the scene.
   */
  class CompositeLight : public ILight {
    public:
      /**
       * @brief Constructor for CompositeLight
       * 
       * Initializes an empty composite light with no children
       */
      CompositeLight();
      
      /**
       * @brief Virtual destructor
       */
      ~CompositeLight() override = default;

      /**
       * @brief Adds a light source to this composite
       * 
       * @param light Shared pointer to a light object to be added to this composite
       */
      void addLight(std::shared_ptr<ILight> light);
      
      /**
       * @brief Gets the direction from a point to this light source
       * 
       * For a composite light, this cycles through child lights on subsequent calls
       * 
       * @param point The 3D point from which to calculate the light direction
       * @return Vector3 Direction vector from the point to the light
       */
      Vector3 getDirectionFrom(const Vector3 &point) const override;
      
      /**
       * @brief Gets the combined intensity of all contained lights
       * 
       * @return float The sum of all child light intensities, clamped to [0,1]
       */
      float getIntensity() const override;
      
      /**
       * @brief Gets all child lights contained in this composite
       * 
       * @return std::vector<std::shared_ptr<ILight>> List of all child lights
       */
      std::vector<std::shared_ptr<ILight>> getLights() const;
      
      /**
       * @brief Gets the number of lights in this composite
       * 
       * @return size_t Number of child lights
       */
      size_t getSize() const;
      
    private:
      /** @brief Vector containing all child light sources */
      std::vector<std::shared_ptr<ILight>> m_lights;
      
      /** @brief Current index used for cycling through lights 
       *  
       * This is marked as mutable to allow modification in const methods
       */
      mutable int m_currentLightIndex;
  };
} 