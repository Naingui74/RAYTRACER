/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** PointLight
*/

#include "Lights/PointLight.hpp"
#include "Utils/Vector3.hpp"

Raytracer::PointLight::PointLight(const Vector3 &position, float intensity)
: m_position(position), m_intensity(intensity) {}

Raytracer::Vector3 Raytracer::PointLight::getDirectionFrom(const Vector3 &point) const
{
    return (m_position - point).normalized();
}

float Raytracer::PointLight::getIntensity() const
{
    return m_intensity;
}
