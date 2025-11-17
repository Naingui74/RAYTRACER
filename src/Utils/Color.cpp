/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Color
*/

#include "Utils/Color.hpp"

Raytracer::Color::Color() : m_r(0), m_g(0), m_b(0) {
}

Raytracer::Color::Color(int r, int g, int b) : m_r(r), m_g(g), m_b(b) {
}

int Raytracer::Color::getR() const {
  return m_r;
}
int Raytracer::Color::getG() const {
  return m_g;
}
int Raytracer::Color::getB() const {
  return m_b;
}

void Raytracer::Color::setR(int r) {
  m_r = r;
}
void Raytracer::Color::setG(int g) {
  m_g = g;
}
void Raytracer::Color::setB(int b) {
  m_b = b;
}

void Raytracer::Color::clamp() {
  m_r = std::clamp(m_r, 0, 255);
  m_g = std::clamp(m_g, 0, 255);
  m_b = std::clamp(m_b, 0, 255);
}

Raytracer::Color Raytracer::Color::operator+(const Raytracer::Color& other) const {
  Raytracer::Color result(
    m_r + other.m_r,
    m_g + other.m_g,
    m_b + other.m_b
  );
  result.clamp();
  return result;
}

Raytracer::Color Raytracer::Color::operator-(const Raytracer::Color& other) const {
  Raytracer::Color result(
    m_r - other.m_r,
    m_g - other.m_g,
    m_b - other.m_b
  );
  result.clamp();
  return result;
}

Raytracer::Color Raytracer::Color::operator*(float scalar) const {
  Raytracer::Color result(
    static_cast<int>(m_r * scalar),
    static_cast<int>(m_g * scalar),
    static_cast<int>(m_b * scalar)
  );
  result.clamp();
  return result;
}

Raytracer::Color Raytracer::Color::operator*(const Raytracer::Color& other) const {
  // Multiplier comme des couleurs (chaque composante dans l'interval [0,1])
  float r = (m_r / 255.0f) * (other.m_r / 255.0f) * 255.0f;
  float g = (m_g / 255.0f) * (other.m_g / 255.0f) * 255.0f;
  float b = (m_b / 255.0f) * (other.m_b / 255.0f) * 255.0f;
  
  Raytracer::Color result(
    static_cast<int>(r),
    static_cast<int>(g),
    static_cast<int>(b)
  );
  result.clamp();
  return result;
}

std::ostream &operator<<(std::ostream &os, const Raytracer::Color &color) {
  os << "(" << color.getR() << ", " << color.getG() << ", " << color.getB() << ")";
  return os;
}
