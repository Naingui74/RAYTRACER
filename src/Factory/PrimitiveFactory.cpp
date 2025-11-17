/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** PrimitiveFactory
*/

#include "Factory/PrimitiveFactory.hpp"
#include "Material/Material.hpp"
#include "Primitives/Cone.hpp"
#include "Primitives/Cylinder.hpp"
#include "Primitives/Plane.hpp"
#include "Primitives/Torus.hpp"
#include "Primitives/Sphere.hpp"
#include "Primitives/Triangle.hpp"
#include "Primitives/Torus.hpp"
#include "Primitives/TangleCube.hpp"
#include "Primitives/CompositePrimitive.hpp"

std::shared_ptr<Raytracer::IPrimitive> Raytracer::PrimitiveFactory::createSphere(const Vector3& center, float radius, const Material& material) {
  return std::make_shared<Sphere>(center, radius, material);
}

std::shared_ptr<Raytracer::IPrimitive> Raytracer::PrimitiveFactory::createPlane(const Vector3& normal, float position, const Material& material) {
  return std::make_shared<Plane>(normal, position, material);
}

std::shared_ptr<Raytracer::IPrimitive> Raytracer::PrimitiveFactory::createCylinder(const Vector3& baseCenter, float radius, float height, const Vector3& rotation, const Material& material) {
  return std::make_shared<Cylinder>(baseCenter, radius, height, rotation, material);
}

std::shared_ptr<Raytracer::IPrimitive> Raytracer::PrimitiveFactory::createCone(const Vector3& baseCenter, float radius, float height, const Vector3& rotation, const Material& material) {
  return std::make_shared<Cone>(baseCenter, radius, height, rotation, material);
}

std::shared_ptr<Raytracer::IPrimitive> Raytracer::PrimitiveFactory::createTriangle(const Vector3& a, const Vector3& b, const Vector3& c, const Material& material) {
  return std::make_shared<Triangle>(a, b, c, material);
}

std::shared_ptr<Raytracer::IPrimitive> Raytracer::PrimitiveFactory::createTorus(const Vector3& center, float majorRadius, float minorRadius, const Vector3& rotation, const Material& material)
{
    return std::make_shared<Torus>(center, majorRadius, minorRadius, rotation, material);
}

std::shared_ptr<Raytracer::IPrimitive> Raytracer::PrimitiveFactory::createTangleCube(const Vector3& center, float size, const Material& material)
{
    return std::make_shared<TangleCube>(center, size, material);
}

std::shared_ptr<Raytracer::IPrimitive> Raytracer::PrimitiveFactory::createCompositePrimitive(const Material& material)
{
    return std::make_shared<CompositePrimitive>(material);
}
