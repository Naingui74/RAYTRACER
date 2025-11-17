/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** CompositeLight
*/

#include "Lights/CompositeLight.hpp"
#include <algorithm>
#include <numeric>

Raytracer::CompositeLight::CompositeLight() : m_currentLightIndex(0) {
}

void Raytracer::CompositeLight::addLight(std::shared_ptr<ILight> light) {
    m_lights.push_back(light);
}

Raytracer::Vector3 Raytracer::CompositeLight::getDirectionFrom(const Vector3 &point) const {
    if (m_lights.empty()) {
        return Vector3(0, 1, 0);
    }
    
    size_t index = 0;
    if (m_lights.size() > 1) {
        index = (static_cast<size_t>(m_currentLightIndex) + 1) % m_lights.size();
    }
    
    return m_lights[index]->getDirectionFrom(point);
}

float Raytracer::CompositeLight::getIntensity() const {
    if (m_lights.empty()) {
        return 0.0f;
    }
    
    float totalIntensity = 0.0f;
    for (const auto& light : m_lights) {
        totalIntensity += light->getIntensity();
    }
    
    return std::min(totalIntensity, 1.0f);
}

std::vector<std::shared_ptr<Raytracer::ILight>> Raytracer::CompositeLight::getLights() const {
    return m_lights;
}

size_t Raytracer::CompositeLight::getSize() const {
    return m_lights.size();
}
