/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** CompositePrimitive
*/

#pragma once

#include "Primitives/IPrimitive.hpp"
#include <vector>
#include <memory>

namespace Raytracer {
  /**
   * @class CompositePrimitive
   * @brief Implements the Composite pattern for 3D primitives
   * 
   * This class allows grouping multiple primitives and treating them as a single entity.
   * It implements the Composite design pattern, enabling hierarchical organization of
   * scene objects. When a ray intersects with a composite, it tests intersection with
   * all contained primitives and returns the closest hit.
   */
  class CompositePrimitive : public IPrimitive {
    public:
      /**
       * @brief Default constructor
       * 
       * Creates an empty composite with no primitives
       */
      CompositePrimitive();
      
      /**
       * @brief Constructor with material
       * 
       * Creates an empty composite with the specified material
       * 
       * @param material The material to use for this composite
       */
      explicit CompositePrimitive(const Material& material);
      
      /**
       * @brief Virtual destructor
       */
      ~CompositePrimitive() override = default;

      /**
       * @brief Adds a primitive to this composite
       * 
       * @param primitive Shared pointer to a primitive to add
       */
      void addPrimitive(std::shared_ptr<IPrimitive> primitive);
      
      /**
       * @brief Tests if a ray intersects with any primitive in this composite
       * 
       * @param ray The ray to test for intersection
       * @param t Output parameter that will contain the distance to intersection if found
       * @return true If the ray intersects with any primitive
       * @return false If no intersection found
       */
      bool intersect(const Ray& ray, float& t) const override;
      
      /**
       * @brief Gets the surface normal at a point
       * 
       * For a composite, returns the normal of the last primitive that was hit
       * 
       * @param point The point on the surface to calculate the normal at
       * @return Vector3 The surface normal vector
       */
      Vector3 getNormal(const Vector3& point) const override;
      
      /**
       * @brief Gets the color of the primitive
       * 
       * For a composite, returns the color of the last primitive that was hit
       * 
       * @return Color The color of the primitive
       */
      Color getColor() const override;
      
      /**
       * @brief Gets the material of the primitive
       * 
       * For a composite, returns the material of the last primitive that was hit,
       * or its own material if no primitive was hit yet
       * 
       * @return const Material& Reference to the material
       */
      const Material& getMaterial() const override;
      
      /**
       * @brief Gets the center point of the primitive
       * 
       * For a composite, returns the average center of all contained primitives
       * 
       * @return Vector3 The center point
       */
      Vector3 getCenter() const override;
      
      /**
       * @brief Gets the number of primitives in this composite
       * 
       * @return size_t The number of primitives
       */
      size_t getSize() const;
      
      /**
       * @brief Gets a primitive at the specified index
       * 
       * @param index The index of the primitive to get
       * @return std::shared_ptr<IPrimitive> The primitive, or nullptr if index is out of bounds
       */
      std::shared_ptr<IPrimitive> getPrimitiveAt(size_t index) const;
      
    private:
      /** @brief Vector containing all child primitives */
      std::vector<std::shared_ptr<IPrimitive>> m_primitives;
      
      /** @brief Material for this composite */
      Material m_material;
      
      /** @brief Pointer to the last hit primitive
       * 
       * Used to return information about the specific primitive that was hit in a composite
       */
      mutable std::shared_ptr<IPrimitive> m_lastHitPrimitive;
  };
} 