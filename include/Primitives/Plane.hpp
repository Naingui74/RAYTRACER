/**
 * @file Plane.hpp
 * @brief Infinite plane primitive implementation for the raytracer
 * @author EPITECH
 * @date 2025
 *
 * This file contains the Plane class which implements the IPrimitive interface.
 * It represents an infinite plane in 3D space that can be rendered in the raytracing engine.
 * A plane is defined by its normal vector and distance from the origin along that normal.
 */

#pragma once

#include "Primitives/IPrimitive.hpp"
#include "Utils/Vector3.hpp"
#include "Utils/Color.hpp"

namespace Raytracer {
    /**
     * @class Plane
     * @brief Represents an infinite plane primitive for raytracing
     *
     * The Plane class defines an infinite plane in 3D space, characterized by its normal
     * vector and distance from the origin. It provides methods for ray-plane intersection
     * testing and normal vector access which are essential for the raytracing process.
     */
    class Plane : public IPrimitive {
    public:
      /**
       * @brief Constructs a plane primitive
       * 
       * @param normal The normal vector of the plane (should be normalized)
       * @param distance The distance from the origin along the normal
       * @param material The material properties of the plane
       */
      Plane(const Vector3& normal, float distance, const Material& material);
      
      /**
       * @brief Tests if a ray intersects with this plane
       * 
       * Calculates if and where a ray intersects with this infinite plane.
       * The intersection distance is stored in the parameter t if an intersection is found.
       * 
       * @param ray The ray to test for intersection
       * @param t Output parameter that will contain the distance to intersection if found
       * @return true If the ray intersects with the plane
       * @return false If no intersection is found (ray is parallel to the plane)
       */
      bool intersect(const Ray& ray, float& t) const override;
      
      /**
       * @brief Gets the normal vector of the plane
       * 
       * For a plane, the normal is constant everywhere on its surface.
       * 
       * @param point The point on the plane (unused for planes since normal is constant)
       * @return Vector3 The normal vector of the plane
       */
      Vector3 getNormal(const Vector3& point) const override;
      
      /**
       * @brief Gets the color of the plane
       * 
       * @return Color The color derived from the plane's material
       */
      Color getColor() const override;
      
      /**
       * @brief Gets a representative point on the plane
       * 
       * Since a plane has no center, this returns a point on the plane
       * at distance d along the normal vector from the origin.
       * 
       * @return Vector3 A point on the plane
       */
      Vector3 getCenter() const override;
      
      /**
       * @brief Gets the material of the plane
       * 
       * @return const Material& Reference to the plane's material
       */
      const Material& getMaterial() const override;

    private:
      Vector3 m_normal;   ///< The normal vector of the plane
      float m_distance;   ///< The distance from the origin along the normal
      Material m_material; ///< The material properties of the plane
    };
}
