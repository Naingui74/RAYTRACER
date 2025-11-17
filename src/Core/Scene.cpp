/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Scene
*/

#include "Core/Scene.hpp"
#include "Factory/PrimitiveFactory.hpp"
#include "Factory/LightFactory.hpp"

Raytracer::Scene::Scene()
    : m_ambientIntensity(0.0f)
{
    // Initialisation des composites racines
    m_rootCompositePrimitive = std::make_shared<CompositePrimitive>();
    m_rootCompositeLight = std::make_shared<CompositeLight>();
    // Ne pas ajouter les composites racines aux collections pour éviter une récursion
}

void Raytracer::Scene::setCamera(const Camera &cam)
{
    m_camera = cam;
}

Raytracer::Camera& Raytracer::Scene::getCamera()
{
    return m_camera;
}

const Raytracer::Camera& Raytracer::Scene::getCamera() const
{
    return m_camera;
}

void Raytracer::Scene::addPrimitive(std::shared_ptr<IPrimitive> primitive)
{
    // Ajouter à la fois au composite racine et à la liste des primitives
    m_rootCompositePrimitive->addPrimitive(primitive);
    m_primitives.push_back(primitive);
}

const std::vector<std::shared_ptr<Raytracer::IPrimitive>>& Raytracer::Scene::getPrimitives() const
{
    return m_primitives;
}

std::shared_ptr<Raytracer::CompositePrimitive> Raytracer::Scene::getRootCompositePrimitive() const
{
    return m_rootCompositePrimitive;
}

void Raytracer::Scene::addLight(std::shared_ptr<ILight> light)
{
    // Ajouter à la fois au composite racine et à la liste des lumières
    m_rootCompositeLight->addLight(light);
    m_lights.push_back(light);
}

const std::vector<std::shared_ptr<Raytracer::ILight>>& Raytracer::Scene::getLights() const
{
    return m_lights;
}

std::shared_ptr<Raytracer::CompositeLight> Raytracer::Scene::getRootCompositeLight() const
{
    return m_rootCompositeLight;
}

void Raytracer::Scene::setAmbientIntensity(float intensity)
{
    m_ambientIntensity = intensity;
}

float Raytracer::Scene::getAmbientIntensity() const
{
    return m_ambientIntensity;
}
