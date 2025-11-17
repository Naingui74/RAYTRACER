/**
 * @file Torus.hpp
 * @brief Torus primitive implementation for the raytracer
 * @author EPITECH
 * @date 2025
 *
 * This file contains the Torus class which implements the IPrimitive interface.
 * It represents a torus (donut shape) in 3D space that can be rendered in the raytracing engine.
 * The torus is defined by its center, major radius, minor radius, and rotation.
 */

#pragma once
#include <cmath>
#include <vector>
#include "Primitives/IPrimitive.hpp"
#include "Utils/Color.hpp"
#include "Utils/Vector3.hpp"
#include "Material/Material.hpp"

namespace Raytracer {
    /**
     * @class Torus
     * @brief Represents a torus primitive for raytracing
     *
     * The Torus class defines a torus (donut shape) in 3D space, characterized by its center,
     * major radius (radius from the center of the torus to the center of the tube),
     * minor radius (radius of the tube), and orientation. It provides methods for ray-torus 
     * intersection testing and normal vector calculation which are essential for the raytracing process.
     */
    class Torus : public IPrimitive {
    public:
      /**
       * @brief Constructs a torus primitive
       * 
       * @param center The center position of the torus
       * @param majorRadius The radius from the center of the torus to the center of the tube
       * @param minorRadius The radius of the tube itself
       * @param rotation The rotation of the torus in degrees (x, y, z angles)
       * @param material The material properties of the torus
       */
      Torus(const Vector3& center, float majorRadius, float minorRadius, const Vector3& rotation, const Material& material);
      
      /**
       * @brief Tests if a ray intersects with this torus
       * 
       * Calculates if and where a ray intersects with this torus using
       * quartic equation solving. The intersection distance is stored in
       * the parameter t if an intersection is found.
       * 
       * @param ray The ray to test for intersection
       * @param t Output parameter that will contain the distance to intersection if found
       * @return true If the ray intersects with the torus
       * @return false If no intersection is found
       */
      bool intersect(const Ray& ray, float& t) const override;
      
      /**
       * @brief Calculates the normal vector at a point on the torus
       * 
       * The normal of a torus at any point is calculated based on the relative position
       * of the point to the central ring of the torus.
       * 
       * @param point The point on the torus's surface
       * @return Vector3 The normalized normal vector
       */
      Vector3 getNormal(const Vector3& point) const override;
      
      /**
       * @brief Gets the color of the torus
       * 
       * @return Color The color derived from the torus's material
       */
      Color getColor() const override;
      
      /**
       * @brief Gets the center point of the torus
       * 
       * @return Vector3 The center point of the torus
       */
      Vector3 getCenter() const override;
      
      /**
       * @brief Gets the material of the torus
       * 
       * @return const Material& Reference to the torus's material
       */
      const Material& getMaterial() const override;

      /**
       * @brief Gets the base center of the torus (same as center for a torus)
       * 
       * @return Vector3 The center point of the torus
       */
      Vector3 getBaseCenter() const;

    private:
      Vector3 m_center;       ///< The center position of the torus
      float m_majorRadius;    ///< The radius from the center to the center of the tube
      float m_minorRadius;    ///< The radius of the tube itself
      Vector3 m_rotation;     ///< The rotation of the torus in degrees
      Material m_material;    ///< The material properties of the torus
      
      /**
       * @brief Transforms a point from world space to torus space
       * 
       * @param point The point in world space
       * @return Vector3 The point in torus space
       */
      Vector3 worldToLocal(const Vector3& point) const;
      
      /**
       * @brief Transforms a direction from world space to torus space
       * 
       * @param dir The direction in world space
       * @return Vector3 The direction in torus space
       */
      Vector3 worldToLocalDirection(const Vector3& dir) const;
    };
}
