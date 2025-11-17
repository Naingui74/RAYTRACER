/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** DirectionalLight
*/

#include "Lights/DirectionalLight.hpp"
#include "Utils/Vector3.hpp"

Raytracer::DirectionalLight::DirectionalLight(const Vector3 &position, const Vector3 &direction, float intensity) 
: m_position(position), m_direction(direction.normalized()), m_intensity(intensity) {
}

Raytracer::Vector3 Raytracer::DirectionalLight::getDirectionFrom(const Vector3 &point) const {
  (void)point;
  return m_direction;
}

float Raytracer::DirectionalLight::getIntensity() const {
  return m_intensity;
}
