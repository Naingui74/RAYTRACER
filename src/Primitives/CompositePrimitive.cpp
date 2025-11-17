/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** CompositePrimitive
*/

#include "Primitives/CompositePrimitive.hpp"
#include <limits>
#include <numeric>
#include "Maths/Ray.hpp"

constexpr float COMP_EPSILON = 0.001f; // Epsilon pour éviter les auto-intersections

Raytracer::CompositePrimitive::CompositePrimitive() : m_lastHitPrimitive(nullptr) {
}

Raytracer::CompositePrimitive::CompositePrimitive(const Material& material) 
    : m_material(material), m_lastHitPrimitive(nullptr) {
}

void Raytracer::CompositePrimitive::addPrimitive(std::shared_ptr<IPrimitive> primitive) {
    // Éviter d'ajouter un composite dans lui-même (ce qui causerait une récursion infinie)
    if (primitive.get() == this)
        return;
        
    // Éviter les doublons
    for (const auto& prim : m_primitives) {
        if (prim.get() == primitive.get())
            return;
    }
    
    m_primitives.push_back(primitive);
}

bool Raytracer::CompositePrimitive::intersect(const Ray& ray, float& t) const {
    if (m_primitives.empty())
        return false;
        
    float closestT = std::numeric_limits<float>::infinity();
    bool anyHit = false;
    m_lastHitPrimitive = nullptr;

    for (const auto& prim : m_primitives) {
        // Ne pas tester l'intersection avec soi-même
        if (prim.get() == this)
            continue;
            
        float tempT;
        if (prim->intersect(ray, tempT) && tempT > COMP_EPSILON && tempT < closestT) {
            closestT = tempT;
            m_lastHitPrimitive = prim;
            anyHit = true;
        }
    }

    if (anyHit) {
        t = closestT;
        return true;
    }
    return false;
}

Raytracer::Vector3 Raytracer::CompositePrimitive::getNormal(const Vector3& point) const {
    if (m_lastHitPrimitive) {
        return m_lastHitPrimitive->getNormal(point);
    }
    return Vector3(0, 1, 0); // Normal par défaut si aucun hit
}

Raytracer::Color Raytracer::CompositePrimitive::getColor() const {
    if (m_lastHitPrimitive) {
        return m_lastHitPrimitive->getColor();
    }
    return m_material.getColor();
}

const Raytracer::Material& Raytracer::CompositePrimitive::getMaterial() const {
    if (m_lastHitPrimitive) {
        return m_lastHitPrimitive->getMaterial();
    }
    return m_material;
}

Raytracer::Vector3 Raytracer::CompositePrimitive::getCenter() const {
    if (m_primitives.empty()) {
        return Vector3(0, 0, 0);
    }
    
    // Calcule le centre comme moyenne des centres des primitives
    Vector3 sum(0, 0, 0);
    for (const auto& prim : m_primitives) {
        sum = sum + prim->getCenter();
    }
    return sum * (1.0f / m_primitives.size());
}

size_t Raytracer::CompositePrimitive::getSize() const {
    return m_primitives.size();
}

std::shared_ptr<Raytracer::IPrimitive> Raytracer::CompositePrimitive::getPrimitiveAt(size_t index) const {
    if (index < m_primitives.size()) {
        return m_primitives[index];
    }
    return nullptr;
} 