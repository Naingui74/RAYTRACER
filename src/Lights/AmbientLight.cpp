/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** AmbientLight.cpp
*/

#include "Lights/AmbientLight.hpp"
#include "Utils/Vector3.hpp"

Raytracer::AmbientLight::AmbientLight(const Vector3 &position, float intensity) : m_position(position), m_intensity(intensity) {
}

Raytracer::Vector3 Raytracer::AmbientLight::getDirectionFrom(const Vector3 &point) const {
  return (m_position - point).normalized();
}

float Raytracer::AmbientLight::getIntensity() const {
  return m_intensity;
}
