#include "Primitives/Cone.hpp"
#include <cmath>
#include <limits>
#include <algorithm>

namespace Raytracer {

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

Cone::Cone(const Vector3 &baseCenter, float radius, float height, const Vector3& rotation, const Material& material)
    : m_baseCenter(baseCenter), m_radius(radius), m_height(std::abs(height)), m_rotation(rotation), m_material(material) {
    m_infinite = std::isinf(height);
    m_axis = height >= 0 ? Vector3(0, 1, 0) : Vector3(0, -1, 0);
    m_apex = m_infinite ? Vector3(0, 0, 0) : m_baseCenter + m_axis * m_height;
}

bool Cone::intersect(const Ray &ray, float &t) const
{
    Vector3 origin = applyInverseRotation(ray.getOrigin() - m_baseCenter, m_rotation);
    Vector3 dir = applyInverseRotation(ray.getDirection(), m_rotation);
    Vector3 apex = m_infinite ? (m_baseCenter + m_axis * 1.0f) : m_apex;
    Vector3 co = origin - (apex - m_baseCenter);
    float k = m_infinite ? 1.0f : m_radius / m_height;
    float k2 = k * k;
    float dx = dir.x;
    float dy = dir.y;
    float dz = dir.z;
    float ox = co.x;
    float oy = co.y;
    float oz = co.z;
    float a = dx * dx + dz * dz - k2 * dy * dy;
    float b = 2 * (dx * ox + dz * oz - k2 * dy * oy);
    float c = ox * ox + oz * oz - k2 * oy * oy;
    float discriminant = b * b - 4 * a * c;
    float t_body = -1;

    if (discriminant >= 0 && std::abs(a) > 1e-6f) {
        float sqrtDisc = std::sqrt(discriminant);
        float t0 = (-b - sqrtDisc) / (2 * a);
        float t1 = (-b + sqrtDisc) / (2 * a);
        for (float temp : {t0, t1}) {
            if (temp > 0) {
                Vector3 hit = origin + dir * temp;
                if (!m_infinite && (hit.y < 0 || hit.y > m_height))
                    continue;
                t_body = temp;
                break;
            }
        }
    }
    float t_cap = -1;
    if (!m_infinite && std::abs(dir.y) > 1e-6f) {
        float t_temp = -origin.y / dir.y;
        if (t_temp > 0) {
            Vector3 p = origin + dir * t_temp;
            if (p.x * p.x + p.z * p.z <= m_radius * m_radius) {
                t_cap = t_temp;
            }
        }
    }
    float final_t = -1;
    if (t_body > 0 && (t_cap < 0 || t_body < t_cap))
        final_t = t_body;
    else if (t_cap > 0)
        final_t = t_cap;
    if (final_t > 0) {
        t = final_t;
        return true;
    }
    return false;
}

Vector3 Cone::getNormal(const Vector3 &point) const
{
    Vector3 local = applyInverseRotation(point - m_baseCenter, m_rotation);
    Vector3 apex = m_infinite ? (m_baseCenter + m_axis * 1.0f) : m_apex;
    Vector3 apexToPoint = local - (apex - m_baseCenter);
    float r = std::sqrt(apexToPoint.x * apexToPoint.x + apexToPoint.z * apexToPoint.z);
    float slope = m_radius / m_height;

    Vector3 normal;
    if (!m_infinite && std::abs(local.y - 0.0f) < 1e-3f)
        normal = Vector3(0, -1, 0);
    else
        normal = Vector3(apexToPoint.x, slope * r, apexToPoint.z).normalized();
    return rotateAroundX(rotateAroundY(rotateAroundZ(normal, m_rotation.z), m_rotation.y), m_rotation.x);
}

Color Cone::getColor() const
{
    return m_material.getColor();
}

const Material& Cone::getMaterial() const
{
    return m_material;
}

Vector3 Cone::getBaseCenter() const
{
    return m_baseCenter;
}

Vector3 Cone::getCenter() const
{
    return m_baseCenter + m_axis * (m_height / 2);
}

}
