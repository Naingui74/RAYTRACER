/**
 * @file Sphere.hpp
 * @brief Sphere primitive implementation for the raytracer
 * @author EPITECH
 * @date 2025
 *
 * This file contains the Sphere class which implements the IPrimitive interface.
 * It represents a sphere in 3D space that can be rendered in the raytracing engine.
 * A sphere is one of the fundamental geometric primitives in raytracing, defined by
 * its center point and radius.
 */

#pragma once

#include "Primitives/IPrimitive.hpp"
#include "Utils/Color.hpp"
#include "Utils/Vector3.hpp"

namespace Raytracer {
    /**
     * @class Sphere
     * @brief Represents a sphere primitive for raytracing
     *
     * The Sphere class defines a sphere in 3D space, characterized by its center point and radius.
     * It provides methods for ray-sphere intersection testing and normal vector calculation
     * which are essential for the raytracing process.
     */
    class Sphere : public IPrimitive {
    public:
      /**
       * @brief Constructs a sphere primitive
       * 
       * @param center The center position of the sphere in 3D space
       * @param radius The radius of the sphere
       * @param material The material properties of the sphere
       */
      Sphere(const Vector3& center, float radius, const Material& material);
      
      /**
       * @brief Tests if a ray intersects with this sphere
       * 
       * Calculates if and where a ray intersects with this sphere using
       * the quadratic formula. The intersection distance is stored in
       * the parameter t if an intersection is found.
       * 
       * @param ray The ray to test for intersection
       * @param t Output parameter that will contain the distance to intersection if found
       * @return true If the ray intersects with the sphere
       * @return false If no intersection is found
       */
      bool intersect(const Ray& ray, float& t) const override;
      
      /**
       * @brief Calculates the normal vector at a point on the sphere
       * 
       * The normal of a sphere at any point is simply the normalized vector
       * from the sphere's center to that point.
       * 
       * @param point The point on the sphere's surface
       * @return Vector3 The normalized normal vector
       */
      Vector3 getNormal(const Vector3& point) const override;
      
      /**
       * @brief Gets the color of the sphere
       * 
       * @return Color The color derived from the sphere's material
       */
      Color getColor() const override;
      
      /**
       * @brief Gets the center position of the sphere
       * 
       * @return Vector3 The center point of the sphere
       */
      Vector3 getCenter() const override;
      
      /**
       * @brief Gets the material of the sphere
       * 
       * @return const Material& Reference to the sphere's material
       */
      const Material& getMaterial() const override;

    private:
      Vector3 m_center;  ///< The center position of the sphere
      float m_radius;    ///< The radius of the sphere
      Material m_material; ///< The material properties of the sphere
  };}
