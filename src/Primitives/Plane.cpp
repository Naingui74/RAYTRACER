/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Plane
*/

#include "Primitives/Plane.hpp"
#include <cmath>
#include "Material/Material.hpp"

namespace Raytracer {

Plane::Plane(const Vector3& normal, float d, const Material& material)
  : m_normal(normal.normalized())
  , m_distance(d)
  , m_material(material)
{
}

bool Plane::intersect(const Ray& ray, float& t) const
{
    float denom = ray.getDirection().dot(m_normal);
    if (std::fabs(denom) < 1e-6f)
        return false;

    // t = (d − origin·n) / (dir·n)
    t = (m_distance - ray.getOrigin().dot(m_normal)) / denom;
    return t >= 0.0f;
}

Vector3 Plane::getNormal(const Vector3& /*point*/) const
{
    return m_normal;
}

Color Plane::getColor() const
{
    return m_material.getColor();
}

const Material& Plane::getMaterial() const
{
    return m_material;
}

Vector3 Plane::getCenter() const
{
    // Un point quelconque sur le plan : d * n
    return m_normal * m_distance;
}

}
