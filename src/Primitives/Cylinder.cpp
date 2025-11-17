#include "Primitives/Cylinder.hpp"
#include <cmath>
#include <limits>
#include <algorithm>

namespace Raytracer {

Raytracer::Cylinder::Cylinder(const Vector3& baseCenter, float radius, float height, const Vector3& rotation, const Material& material)
    : m_baseCenter(baseCenter), m_radius(radius), m_height(height), m_rotation(rotation), m_material(material) {}

static Vector3 rotateAroundX(const Vector3& v, float angle)
{
    float rad = angle * M_PI / 180.0f;
    return {
        v.x,
        v.y * std::cos(rad) - v.z * std::sin(rad),
        v.y * std::sin(rad) + v.z * std::cos(rad)
    };
}

static Vector3 rotateAroundY(const Vector3& v, float angle)
{
    float rad = angle * M_PI / 180.0f;
    return {
        v.x * std::cos(rad) + v.z * std::sin(rad),
        v.y,
        -v.x * std::sin(rad) + v.z * std::cos(rad)
    };
}

static Vector3 rotateAroundZ(const Vector3& v, float angle)
{
    float rad = angle * M_PI / 180.0f;
    return {
        v.x * std::cos(rad) - v.y * std::sin(rad),
        v.x * std::sin(rad) + v.y * std::cos(rad),
        v.z
    };
}

static Vector3 applyInverseRotation(const Vector3& v, const Vector3& rotation)
{
    Vector3 out = rotateAroundZ(v, -rotation.z);
    out = rotateAroundY(out, -rotation.y);
    out = rotateAroundX(out, -rotation.x);
    return out;
}

bool Cylinder::intersect(const Ray& ray, float& t) const
{
    Vector3 origin = applyInverseRotation(ray.getOrigin() - m_baseCenter, m_rotation);
    Vector3 dir = applyInverseRotation(ray.getDirection(), m_rotation);
    float a = dir.x * dir.x + dir.z * dir.z;
    float b = 2.0f * (origin.x * dir.x + origin.z * dir.z);
    float c = origin.x * origin.x + origin.z * origin.z - m_radius * m_radius;
    float discriminant = b * b - 4 * a * c;
    float t_cylinder = -1;

    if (discriminant >= 0 && std::abs(a) > 1e-6f) {
        float sqrtDisc = std::sqrt(discriminant);
        float t0 = (-b - sqrtDisc) / (2.0f * a);
        float t1 = (-b + sqrtDisc) / (2.0f * a);
        for (float temp : {t0, t1}) {
            if (temp > 0) {
                Vector3 hit = origin + dir * temp;
                if (m_height == std::numeric_limits<float>::infinity() ||
                    (hit.y >= 0 && hit.y <= m_height)) {
                    t_cylinder = temp;
                    break;
                }
            }
        }
    }
    float t_cap = -1;
    if (m_height != std::numeric_limits<float>::infinity()) {
        for (int i = 0; i < 2; ++i) {
            float y_cap = (i == 0 ? 0 : m_height);
            float denom = dir.y;
            if (std::abs(denom) > 1e-6f) {
                float t_temp = (y_cap - origin.y) / denom;
                Vector3 p = origin + dir * t_temp;
                if (p.x * p.x + p.z * p.z <= m_radius * m_radius && t_temp > 0) {
                    if (t_cap < 0 || t_temp < t_cap)
                        t_cap = t_temp;
                }
            }
        }
    }
    float final_t = -1;
    if (t_cylinder > 0 && (t_cap < 0 || t_cylinder < t_cap))
        final_t = t_cylinder;
    else if (t_cap > 0)
        final_t = t_cap;

    if (final_t > 0) {
        t = final_t;
        return true;
    }
    return false;
}

Vector3 Cylinder::getNormal(const Vector3& point) const
{
    Vector3 local = applyInverseRotation(point - m_baseCenter, m_rotation);

    if (m_height != std::numeric_limits<float>::infinity()) {
        if (std::abs(local.y - 0.0f) < 1e-3f)
            return rotateAroundX(rotateAroundY(rotateAroundZ(Vector3(0, -1, 0), m_rotation.z), m_rotation.y), m_rotation.x);
        if (std::abs(local.y - m_height) < 1e-3f)
            return rotateAroundX(rotateAroundY(rotateAroundZ(Vector3(0, 1, 0), m_rotation.z), m_rotation.y), m_rotation.x);
    }

    Vector3 normal(local.x, 0, local.z);
    return rotateAroundX(rotateAroundY(rotateAroundZ(normal.normalized(), m_rotation.z), m_rotation.y), m_rotation.x);
}

Color Cylinder::getColor() const
{
    return m_material.getColor();
}

const Material& Cylinder::getMaterial() const
{
    return m_material;
}

Vector3 Cylinder::getBaseCenter() const
{
    return m_baseCenter;
}

Vector3 Cylinder::getCenter() const
{
    return m_baseCenter + Vector3(0, m_height * 0.5f, 0);
}
}
