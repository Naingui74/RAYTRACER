/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** LightFactory.cpp
*/

#include "Factory/LightFactory.hpp"
#include "Lights/PointLight.hpp"
#include "Lights/DirectionalLight.hpp"
#include "Lights/AmbientLight.hpp"
#include "Lights/CompositeLight.hpp"


std::shared_ptr<Raytracer::ILight> Raytracer::LightFactory::createPointLight(
    const Vector3& position, float intensity)
{
    return std::make_shared<PointLight>(position, intensity);
}

std::shared_ptr<Raytracer::ILight> Raytracer::LightFactory::createDirectionalLight(
    const Vector3& position, const Vector3& direction, float intensity)
{
    return std::make_shared<DirectionalLight>(position, direction, intensity);
}

std::shared_ptr<Raytracer::ILight> Raytracer::LightFactory::createAmbientLight(
    const Vector3& position, float intensity)
{
    return std::make_shared<AmbientLight>(position, intensity);
}

std::shared_ptr<Raytracer::ILight> Raytracer::LightFactory::createCompositeLight()
{
    return std::make_shared<CompositeLight>();
}

