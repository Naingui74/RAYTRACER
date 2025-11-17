/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Torus with SDF and rotation
*/

#include "Primitives/Torus.hpp"
#include "Maths/Ray.hpp"
#include <cmath>
#include <limits>

namespace Raytracer {

Torus::Torus(const Vector3& center, float majorRadius, float minorRadius, const Vector3& rotation, const Material& material)
    : m_center(center), m_majorRadius(majorRadius), m_minorRadius(minorRadius), m_rotation(rotation), m_material(material) {}

static
Vector3 rotateAroundX(const Vector3& v, float angle)
{
    float rad = angle * M_PI / 180.0f;
    return {
        v.x,
        v.y * std::cos(rad) - v.z * std::sin(rad),
        v.y * std::sin(rad) + v.z * std::cos(rad)
    };
}

static
Vector3 rotateAroundY(const Vector3& v, float angle)
{
    float rad = angle * M_PI / 180.0f;
    return {
        v.x * std::cos(rad) + v.z * std::sin(rad),
        v.y,
        -v.x * std::sin(rad) + v.z * std::cos(rad)
    };
}

static
Vector3 rotateAroundZ(const Vector3& v, float angle)
{
    float rad = angle * M_PI / 180.0f;
    return {
        v.x * std::cos(rad) - v.y * std::sin(rad),
        v.x * std::sin(rad) + v.y * std::cos(rad),
        v.z
    };
}

static
Vector3 applyRotation(const Vector3& v, const Vector3& rotation)
{
    Vector3 out = rotateAroundX(v, rotation.x);
    out = rotateAroundY(out, rotation.y);
    out = rotateAroundZ(out, rotation.z);
    return out;
}

static
Vector3 applyInverseRotation(const Vector3& v, const Vector3& rotation)
{
    Vector3 out = rotateAroundZ(v, -rotation.z);
    out = rotateAroundY(out, -rotation.y);
    out = rotateAroundX(out, -rotation.x);
    return out;
}


bool Torus::intersect(const Ray& ray, float& t) const
{
    Vector3 localOrigin = applyInverseRotation(ray.getOrigin() - m_center, m_rotation);
    Vector3 localDir = applyInverseRotation(ray.getDirection(), m_rotation);
    Vector3 p = localOrigin;
    Vector3 d = localDir.normalized();
    float maxDistance = 1000.0f;
    float minDist = 1e-3f;
    float totalDist = 0.0f;

    for (int i = 0; i < 256; ++i) {
        Vector3 current = p + d * totalDist;
        float len = std::sqrt(current.x * current.x + current.z * current.z);
        float qx = len - m_majorRadius;
        float qy = current.y;
        float dist = std::sqrt(qx * qx + qy * qy) - m_minorRadius;
        if (std::abs(dist) < minDist) {
            t = totalDist;
            return true;
        }
        totalDist += dist;
        if (totalDist > maxDistance)
            break;
    }
    return false;
}

Vector3 Torus::getNormal(const Vector3& point) const
{
    Vector3 local = applyInverseRotation(point - m_center, m_rotation);

    float len = std::sqrt(local.x * local.x + local.z * local.z);
    Vector3 q = {
        len - m_majorRadius,
        local.y,
        0.0f
    };
    Vector3 n = {
        local.x * q.x / len,
        q.y,
        local.z * q.x / len
    };
    return applyRotation(n.normalized(), m_rotation);
}

Color Torus::getColor() const
{
    return m_material.getColor();
}

const Material& Torus::getMaterial() const 
{
    return m_material;    
} 

Vector3 Torus::getBaseCenter() const
{
    return m_center;
}

Vector3 Torus::getCenter() const
{
    return m_center;
}

}
