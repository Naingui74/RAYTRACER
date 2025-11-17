/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Sphere
*/

#include "Primitives/Sphere.hpp"
#include <cmath>
#include "Maths/Ray.hpp"

Raytracer::Sphere::Sphere(const Vector3 &center, float radius, const Material &material) : m_center(center), m_radius(radius), m_material(material) {
}

Raytracer::Vector3 Raytracer::Sphere::getCenter() const {
  return m_center;
}

Raytracer::Color Raytracer::Sphere::getColor() const {
  return m_material.getColor();
}

const Raytracer::Material& Raytracer::Sphere::getMaterial() const {
  return m_material;
}

Raytracer::Vector3 Raytracer::Sphere::getNormal(const Vector3 &point) const {
  return (point - m_center).normalized();
}

bool Raytracer::Sphere::intersect(const Ray &ray, float &t) const {
  Vector3 oc = ray.getOrigin() - m_center;
  float a = ray.getDirection().dot(ray.getDirection());
  float b = 2.0f * oc.dot(ray.getDirection());
  float c = oc.dot(oc) - m_radius * m_radius;
  float discriminant = b * b - 4 * a * c;
  if (discriminant < 0)
    return false;
  float sqrtDiscriminant = std::sqrt(discriminant);
  float t0 = (-b - sqrtDiscriminant) / (2.0f * a);
  float t1 = (-b + sqrtDiscriminant) / (2.0f * a);
  if (t0 > 0.001f) {
    t = t0;
    return true;
  }
  if (t1 > 0.001f) {
    t = t1;
    return true;
  }
  return false;
}
