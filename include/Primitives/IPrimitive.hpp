/**
 * @file IPrimitive.hpp
 * @brief Interface for all geometric primitives in the raytracer
 * @author EPITECH
 * @date 2025
 *
 * This file defines the IPrimitive interface which serves as the base for all
 * geometric primitives in the raytracer system. It declares the essential methods
 * that any renderable primitive object must implement, including intersection testing,
 * normal calculation, and property accessors.
 */

#pragma once

#include "Material/Material.hpp"
#include "Maths/Ray.hpp"
#include "Utils/Color.hpp"
#include "Utils/Vector3.hpp"

namespace Raytracer {
    /**
     * @class IPrimitive
     * @brief Interface for all geometric primitives
     *
     * This abstract class defines the interface that all renderable primitives
     * (spheres, planes, cylinders, etc.) must implement to be compatible with
     * the raytracing engine. It provides pure virtual methods for ray intersection,
     * normal calculation, and basic property access.
     */
    class IPrimitive {
    public:
      /**
       * @brief Virtual destructor for proper polymorphic cleanup
       */
      virtual ~IPrimitive() = default;
      
      /**
       * @brief Tests if a ray intersects with this primitive
       * 
       * This method determines whether a ray hits this primitive, and if so, at what
       * distance from the ray origin.
       * 
       * @param ray The ray to test for intersection
       * @param t Output parameter that will contain the distance to intersection if found
       * @return true If the ray intersects with the primitive
       * @return false If no intersection is found
       */
      virtual bool intersect(const Ray& ray, float& t) const = 0;
      
      /**
       * @brief Calculates the surface normal at a given point
       * 
       * The normal vector is perpendicular to the surface of the primitive
       * at the specified point and is typically normalized.
       * 
       * @param point The point on the surface to calculate the normal at
       * @return Vector3 The normalized surface normal vector
       */
      virtual Vector3 getNormal(const Vector3& point) const = 0;
      
      /**
       * @brief Gets the color of the primitive
       * 
       * @note This is a legacy method. Use getMaterial().getColor() instead
       * for material-based rendering.
       * 
       * @return Color The color of the primitive
       */
      virtual Color getColor() const = 0;
      
      /**
       * @brief Gets the material of the primitive
       * 
       * The material defines how the primitive interacts with light, including
       * its color, reflectivity, transparency, etc.
       * 
       * @return const Material& Reference to the primitive's material
       */
      virtual const Material& getMaterial() const = 0;
      
      /**
       * @brief Gets the center point of the primitive
       * 
       * For primitives like spheres or cubes, this returns their center.
       * For primitives without a well-defined center (like planes), implementations
       * may return a representative point.
       * 
       * @return Vector3 The center point or representative position
       */
      virtual Vector3 getCenter() const = 0;
  };
}
