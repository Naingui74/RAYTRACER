/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Triangle (optimized intersection)
*/

#include "Primitives/Triangle.hpp"
#include <cmath>

namespace Raytracer {

Triangle::Triangle(const Vector3& a, const Vector3& b, const Vector3& c, const Material& material)
    : m_a(a), m_b(b), m_c(c), m_material(material),
      m_edge1(b - a), m_edge2(c - a),
      m_normal(m_edge1.cross(m_edge2).normalized()) 
{}

bool Triangle::intersect(const Ray& ray, float& t) const
{
    constexpr float EPSILON = 1e-6f;
    const Vector3& dir = ray.getDirection();
    const Vector3& orig = ray.getOrigin();

    Vector3 h = dir.cross(m_edge2);
    float a = m_edge1.dot(h);
    if (std::abs(a) < EPSILON)
        return false;
    float f = 1.0f / a;
    Vector3 s = orig - m_a;
    float u = f * s.dot(h);
    if (u < 0.0f || u > 1.0f)
        return false;
    Vector3 q = s.cross(m_edge1);
    float v = f * dir.dot(q);
    if (v < 0.0f || u + v > 1.0f)
        return false;
    t = f * m_edge2.dot(q);
    return t > EPSILON;
}

Vector3 Triangle::getNormal(const Vector3&) const
{
    return m_normal;
}

Color Triangle::getColor() const
{
    return m_material.getColor();
}

const Material& Triangle::getMaterial() const
{
    return m_material;
}

Vector3 Triangle::getCenter() const
{
    return Vector3(
        (m_a.x + m_b.x + m_c.x) * 0.33333333f,
        (m_a.y + m_b.y + m_c.y) * 0.33333333f,
        (m_a.z + m_b.z + m_c.z) * 0.33333333f
    );
}

Vector3 Triangle::getBaseCenter() const
{
    return getCenter();
}

}
