/**
 * @file Triangle.hpp
 * @brief Triangle primitive implementation for the raytracer
 * @author EPITECH
 * @date 2025
 *
 * This file contains the Triangle class which implements the IPrimitive interface.
 * It represents a triangle in 3D space defined by three vertices.
 */

#pragma once
#include "Primitives/IPrimitive.hpp"
#include "Utils/Color.hpp"
#include "Utils/Vector3.hpp"
#include "Material/Material.hpp"

namespace Raytracer {
    /**
     * @class Triangle
     * @brief Represents a triangle primitive for raytracing
     *
     * The Triangle class defines a triangle in 3D space, characterized by three vertices.
     * It provides methods for ray-triangle intersection testing using the Möller–Trumbore algorithm
     * and normal vector calculation which are essential for the raytracing process.
     */
    class Triangle : public IPrimitive {
    public:
      /**
       * @brief Constructs a triangle primitive
       * 
       * @param a First vertex of the triangle
       * @param b Second vertex of the triangle
       * @param c Third vertex of the triangle
       * @param material The material properties of the triangle
       */
      Triangle(const Vector3& a, const Vector3& b, const Vector3& c, const Material& material);
      
      /**
       * @brief Tests if a ray intersects with this triangle
       * 
       * Calculates if and where a ray intersects with this triangle using
       * the Möller–Trumbore algorithm. The intersection distance is stored in
       * the parameter t if an intersection is found.
       * 
       * @param ray The ray to test for intersection
       * @param t Output parameter that will contain the distance to intersection if found
       * @return true If the ray intersects with the triangle
       * @return false If no intersection is found
       */
      bool intersect(const Ray& ray, float& t) const override;
      
      /**
       * @brief Calculates the normal vector of the triangle
       * 
       * The normal of a triangle is calculated as the cross product of two edges,
       * which is constant across the entire triangle unless smooth shading is used.
       * 
       * @param point The point on the triangle's surface (unused in flat shading)
       * @return Vector3 The normalized normal vector
       */
      Vector3 getNormal(const Vector3& point) const override;
      
      /**
       * @brief Gets the color of the triangle
       * 
       * @return Color The color derived from the triangle's material
       */
      Color getColor() const override;
      
      /**
       * @brief Gets the center point (centroid) of the triangle
       * 
       * Calculates the centroid of the triangle by averaging the three vertices.
       * 
       * @return Vector3 The center point (centroid) of the triangle
       */
      Vector3 getCenter() const override;
      
      /**
       * @brief Gets the material of the triangle
       * 
       * @return const Material& Reference to the triangle's material
       */
      const Material& getMaterial() const override;

      /**
       * @brief Gets the base center of the triangle (same as center)
       * 
       * @return Vector3 The center point of the triangle
       */
      Vector3 getBaseCenter() const;

    private:
      Vector3 m_a; ///< First vertex of the triangle
      Vector3 m_b; ///< Second vertex of the triangle
      Vector3 m_c; ///< Third vertex of the triangle
      Vector3 m_edge1; ///< First edge of the triangle (b - a)
      Vector3 m_edge2; ///< Second edge of the triangle (c - a) 
      Vector3 m_normal; ///< Precalculated normal of the triangle
      Material m_material; ///< The material properties of the triangle
    };
}  // namespace Raytracer
