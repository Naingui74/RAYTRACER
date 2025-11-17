/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Ray
*/

#include "Maths/Ray.hpp"

Raytracer::Ray::Ray(const Vector3 &origin, const Vector3 &direction)
    : m_origin(origin), m_direction(direction.normalized()) {}

const Raytracer::Vector3 &Raytracer::Ray::getOrigin() const
{
    return m_origin;
}

const Raytracer::Vector3 &Raytracer::Ray::getDirection() const
{
    return m_direction;
}

Raytracer::Vector3 Raytracer::Ray::at(float t) const
{
    return m_origin + m_direction * t;
}
