/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** PrimitiveFactory.hpp
*/

#pragma once

#include <memory>
#include "Material/Material.hpp"
#include "Primitives/IPrimitive.hpp"
#include "Utils/Vector3.hpp"

namespace Raytracer {
    /**
     * @class PrimitiveFactory
     * @brief Factory class for creating geometric primitives in a 3D scene.
     *
     * Provides static methods to create various geometric shapes that implement
     * the IPrimitive interface. Implements the Factory design pattern to
     * encapsulate object creation logic.
     */
    class PrimitiveFactory {
    public:
      static std::shared_ptr<IPrimitive> createSphere(const Vector3& center, float radius, const Material& material);

      static std::shared_ptr<IPrimitive> createPlane(const Vector3& normal, float position, const Material& material);

      static std::shared_ptr<IPrimitive> createCylinder(const Vector3& baseCenter, float radius, float height, const Vector3& rotation, const Material& material);
      
      static std::shared_ptr<IPrimitive> createCone(const Vector3& baseCenter, float radius, float height, const Vector3& rotation, const Material& material);

      static std::shared_ptr<IPrimitive> createTriangle(const Vector3& a, const Vector3& b, const Vector3& c, const Material& material);
  
      static std::shared_ptr<IPrimitive> createTorus(const Vector3& center, float majorRadius, float minorRadius, const Vector3& rotation, const Material& material);

      static std::shared_ptr<IPrimitive> createTangleCube(const Vector3& center, float size, const Material& material);

      static std::shared_ptr<IPrimitive> createCompositePrimitive(const Material& material);
  };}
