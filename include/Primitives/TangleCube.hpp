/**
 * @file TangleCube.hpp
 * @brief TangleCube primitive implementation for the raytracer
 * @author EPITECH
 * @date 2025
 *
 * This file contains the TangleCube class which implements the IPrimitive interface.
 * It represents a specialized implicit surface known as a "Tangle Cube" in 3D space.
 * This is a mathematical surface defined by a fourth-degree polynomial equation.
 */

#pragma once
#include "Primitives/IPrimitive.hpp"
#include "Utils/Color.hpp"
#include "Utils/Vector3.hpp"
#include "Material/Material.hpp"

namespace Raytracer {
    /**
     * @class TangleCube
     * @brief Represents a Tangle Cube primitive for raytracing
     *
     * The TangleCube class defines an implicit surface known as a Tangle Cube,
     * which is characterized by its center point and size. The surface is defined
     * by the equation: x⁴ - 5x² + y⁴ - 5y² + z⁴ - 5z² + 11.8 = 0.
     * This creates a cube-like shape with rounded edges and corners.
     */
    class TangleCube : public IPrimitive {
    public:
      /**
       * @brief Constructs a TangleCube primitive
       * 
       * @param center The center position of the TangleCube
       * @param size The overall size/scale of the TangleCube
       * @param material The material properties of the TangleCube
       */
      TangleCube(const Vector3& center, float size, const Material& material);
      
      /**
       * @brief Tests if a ray intersects with this TangleCube
       * 
       * Uses numerical methods (ray marching) to find intersections with the implicit surface.
       * The intersection distance is stored in the parameter t if an intersection is found.
       * 
       * @param ray The ray to test for intersection
       * @param t Output parameter that will contain the distance to intersection if found
       * @return true If the ray intersects with the TangleCube
       * @return false If no intersection is found
       */
      bool intersect(const Ray& ray, float& t) const override;
      
      /**
       * @brief Calculates the normal vector at a point on the TangleCube
       * 
       * For implicit surfaces, the normal is calculated as the gradient of the 
       * defining function at the given point.
       * 
       * @param point The point on the TangleCube's surface
       * @return Vector3 The normalized normal vector
       */
      Vector3 getNormal(const Vector3& point) const override;
      
      /**
       * @brief Gets the color of the TangleCube
       * 
       * @return Color The color derived from the TangleCube's material
       */
      Color getColor() const override;
      
      /**
       * @brief Gets the center point of the TangleCube
       * 
       * @return Vector3 The center point of the TangleCube
       */
      Vector3 getCenter() const override;
      
      /**
       * @brief Gets the material of the TangleCube
       * 
       * @return const Material& Reference to the TangleCube's material
       */
      const Material& getMaterial() const override;

      /**
       * @brief Gets the base center of the TangleCube
       * 
       * @return Vector3 The center point (same as getCenter)
       */
      Vector3 getBaseCenter() const;

    private:
      Vector3 m_center; ///< The center position of the TangleCube
      float m_size;     ///< The size/scale factor of the TangleCube
      Material m_material; ///< The material properties of the TangleCube
      
      /**
       * @brief Evaluates the TangleCube defining function at a given point
       * 
       * The function is: x⁴ - 5x² + y⁴ - 5y² + z⁴ - 5z² + 11.8 = 0
       * 
       * @param point The point to evaluate
       * @return float The function value (0 means on the surface)
       */
      float tangle_cube_equation(const Vector3& point) const;

      /**
       * @brief Calculates the gradient of the TangleCube function at a given point
       * 
       * This is used to determine the normal vector at a point on the surface.
       * 
       * @param point The point to evaluate
       * @return Vector3 The normalized gradient vector
       */
      Vector3 tangle_cube_gradient(const Vector3& point) const;
    };
} 
