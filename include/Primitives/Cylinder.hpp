/**
 * @file Cylinder.hpp
 * @brief Cylinder primitive implementation for the raytracer
 * @author EPITECH
 * @date 2025
 *
 * This file contains the Cylinder class which implements the IPrimitive interface.
 * It represents a cylinder in 3D space that can be rendered in the raytracing engine.
 * The cylinder can be finite or infinite in height and can be rotated in 3D space.
 */

#pragma once

#include "Primitives/IPrimitive.hpp"
#include "Utils/Color.hpp"
#include "Utils/Vector3.hpp"
#include "Material/Material.hpp"

namespace Raytracer {
    /**
     * @class Cylinder
     * @brief Represents a cylinder primitive for raytracing
     *
     * The Cylinder class defines a cylinder in 3D space, characterized by its base center,
     * radius, height, and orientation. It provides methods for ray-cylinder intersection 
     * testing and normal vector calculation which are essential for the raytracing process.
     */
    class Cylinder : public IPrimitive {
    public:
      /**
       * @brief Constructs a cylinder primitive
       * 
       * @param baseCenter The center of the cylinder's base
       * @param radius The radius of the cylinder
       * @param height The height of the cylinder (can be infinite)
       * @param rotation The rotation of the cylinder in degrees (x, y, z angles)
       * @param material The material properties of the cylinder
       */
      Cylinder(const Vector3& baseCenter, float radius, float height, const Vector3& rotation, const Material& material);
      
      /**
       * @brief Tests if a ray intersects with this cylinder
       * 
       * Calculates if and where a ray intersects with this cylinder, considering
       * both the curved surface and the end caps (for finite cylinders).
       * The intersection distance is stored in the parameter t if an intersection is found.
       * 
       * @param ray The ray to test for intersection
       * @param t Output parameter that will contain the distance to intersection if found
       * @return true If the ray intersects with the cylinder
       * @return false If no intersection is found
       */
      bool intersect(const Ray& ray, float& t) const override;
      
      /**
       * @brief Calculates the normal vector at a point on the cylinder
       * 
       * Determines the normal based on whether the point is on the curved surface
       * or one of the end caps.
       * 
       * @param point The point on the cylinder's surface
       * @return Vector3 The normalized normal vector
       */
      Vector3 getNormal(const Vector3& point) const override;
      
      /**
       * @brief Gets the color of the cylinder
       * 
       * @return Color The color derived from the cylinder's material
       */
      Color getColor() const override;
      
      /**
       * @brief Gets the center point of the cylinder
       * 
       * Returns the center of the cylinder, which is halfway between the base
       * and the top along the central axis.
       * 
       * @return Vector3 The center point of the cylinder
       */
      Vector3 getCenter() const override;
      
      /**
       * @brief Gets the material of the cylinder
       * 
       * @return const Material& Reference to the cylinder's material
       */
      const Material& getMaterial() const override;

      /**
       * @brief Gets the base center of the cylinder
       * 
       * @return Vector3 The center of the cylinder's base
       */
      Vector3 getBaseCenter() const;

    private:
      Vector3 m_baseCenter; ///< The center of the cylinder's base
      float m_radius;       ///< The radius of the cylinder
      float m_height;       ///< The height of the cylinder
      Vector3 m_rotation;   ///< The rotation of the cylinder in degrees (x, y, z)
      Material m_material;  ///< The material properties of the cylinder
      
      /**
       * @brief Transforms a point from world space to cylinder space
       * 
       * @param point The point in world space
       * @return Vector3 The point in cylinder space
       */
      Vector3 worldToLocal(const Vector3& point) const;
      
      /**
       * @brief Transforms a direction from world space to cylinder space
       * 
       * @param dir The direction in world space
       * @return Vector3 The direction in cylinder space
       */
      Vector3 worldToLocalDirection(const Vector3& dir) const;
    };
}
