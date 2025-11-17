/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** TangleCube
*/

#include "Primitives/TangleCube.hpp"
#include <cmath>
#include <algorithm>

namespace Raytracer {

TangleCube::TangleCube(const Vector3& center, float size, const Material& material)
    : m_center(center), m_size(size), m_material(material) {
}

float TangleCube::tangle_cube_equation(const Vector3& point) const
{
    Vector3 p = (point - m_center) / m_size;
    float x = p.x;
    float y = p.y;
    float z = p.z;

    return x*x*x*x - 5*x*x + y*y*y*y - 5*y*y + z*z*z*z - 5*z*z + 11.8f;
}

Vector3 TangleCube::tangle_cube_gradient(const Vector3& point) const
{
    Vector3 p = (point - m_center) / m_size;
    
    float x = p.x;
    float y = p.y;
    float z = p.z;
    float dx = 4*x*x*x - 10*x;
    float dy = 4*y*y*y - 10*y;
    float dz = 4*z*z*z - 10*z;
    
    Vector3 grad(dx, dy, dz);
    return grad.normalized();
}

bool TangleCube::intersect(const Ray& ray, float& t) const
{
    const float stepSize = 0.1f;
    const float minStep = 0.001f;
    const int maxSteps = 1000;
    const float hitThreshold = 0.001f;
    float currentT = 0.0f;
    Vector3 rayOrigin = ray.getOrigin();
    Vector3 rayDir = ray.getDirection();
    
    for (int i = 0; i < maxSteps; ++i) {
        Vector3 point = rayOrigin + rayDir * currentT;
        float dist = std::abs(tangle_cube_equation(point));
        if (dist < hitThreshold) {
            t = currentT;
            return true;
        }
        if (currentT > 1000.0f) {
            return false;
        }
        float step = std::max(dist * stepSize, minStep);
        currentT += step;
    }
    
    return false;
}

Vector3 TangleCube::getNormal(const Vector3& point) const
{
    return tangle_cube_gradient(point);
}

Color TangleCube::getColor() const
{
    return m_material.getColor();
}

const Material& TangleCube::getMaterial() const 
{
    return m_material;
}

Vector3 TangleCube::getCenter() const
{
    return m_center;
}

Vector3 TangleCube::getBaseCenter() const
{
    return m_center;
}

}
