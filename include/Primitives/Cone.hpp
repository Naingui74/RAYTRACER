/**
 * @file Cone.hpp
 * @brief Cone primitive implementation for the raytracer
 * @author EPITECH
 * @date 2025
 *
 * This file contains the Cone class which implements the IPrimitive interface.
 * It represents a cone in 3D space that can be rendered in the raytracing engine.
 * The cone can be truncated to a finite height and can be rotated in 3D space.
 */

#pragma once

#include "Primitives/IPrimitive.hpp"
#include "Utils/Color.hpp"
#include "Utils/Vector3.hpp"
#include "Material/Material.hpp"

namespace Raytracer {
    /**
     * @class Cone
     * @brief Represents a cone primitive for raytracing
     *
     * The Cone class defines a cone in 3D space, characterized by its base center,
     * radius, height, and orientation. It provides methods for ray-cone intersection 
     * testing and normal vector calculation which are essential for the raytracing process.
     */
    class Cone : public IPrimitive {
    public:
      /**
       * @brief Constructs a cone primitive
       * 
       * @param baseCenter The center of the cone's base
       * @param radius The radius of the cone's base
       * @param height The height of the cone (can be infinite)
       * @param rotation The rotation of the cone in degrees (x, y, z angles)
       * @param material The material properties of the cone
       */
      Cone(const Vector3& baseCenter, float radius, float height, const Vector3& rotation, const Material& material);
      
      /**
       * @brief Tests if a ray intersects with this cone
       * 
       * Calculates if and where a ray intersects with this cone, considering
       * both the conical surface and the base (for finite cones).
       * The intersection distance is stored in the parameter t if an intersection is found.
       * 
       * @param ray The ray to test for intersection
       * @param t Output parameter that will contain the distance to intersection if found
       * @return true If the ray intersects with the cone
       * @return false If no intersection is found
       */
      bool intersect(const Ray& ray, float& t) const override;
      
      /**
       * @brief Calculates the normal vector at a point on the cone
       * 
       * Determines the normal based on whether the point is on the conical surface
       * or on the base.
       * 
       * @param point The point on the cone's surface
       * @return Vector3 The normalized normal vector
       */
      Vector3 getNormal(const Vector3& point) const override;
      
      /**
       * @brief Gets the color of the cone
       * 
       * @return Color The color derived from the cone's material
       */
      Color getColor() const override;
      
      /**
       * @brief Gets the center point of the cone
       * 
       * Returns the center of the cone, which is at a point 1/3 of the height
       * from the base to the apex, along the central axis.
       * 
       * @return Vector3 The center point of the cone
       */
      Vector3 getCenter() const override;
      
      /**
       * @brief Gets the material of the cone
       * 
       * @return const Material& Reference to the cone's material
       */
      const Material& getMaterial() const override;

      /**
       * @brief Gets the base center of the cone
       * 
       * @return Vector3 The center of the cone's base
       */
      Vector3 getBaseCenter() const;

    private:
      Vector3 m_baseCenter; ///< The center of the cone's base
      float m_radius;       ///< The radius of the cone's base
      float m_height;       ///< The height of the cone
      Vector3 m_axis;       ///< The direction from base to apex (normalized)
      Vector3 m_apex;       ///< The position of the cone's apex
      Material m_material;  ///< The material properties of the cone
      Vector3 m_rotation;   ///< The rotation of the cone in degrees (x, y, z)
      bool m_infinite;      ///< Whether the cone extends infinitely
      
      /**
       * @brief Transforms a point from world space to cone space
       * 
       * @param point The point in world space
       * @return Vector3 The point in cone space
       */
      Vector3 worldToLocal(const Vector3& point) const;
      
      /**
       * @brief Transforms a direction from world space to cone space
       * 
       * @param dir The direction in world space
       * @return Vector3 The direction in cone space
       */
      Vector3 worldToLocalDirection(const Vector3& dir) const;
    };
}  // namespace Raytracer
