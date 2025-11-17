/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Vector3
*/

#include "Utils/Vector3.hpp"

Raytracer::Vector3::Vector3() : x(0), y(0), z(0) {
}

Raytracer::Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {
}

Raytracer::Vector3 Raytracer::Vector3::operator+(const Vector3 &other) const {
  return Vector3(x + other.x, y + other.y, z + other.z);
}

Raytracer::Vector3 Raytracer::Vector3::operator-(const Vector3 &other) const {
  return Vector3(x - other.x, y - other.y, z - other.z);
}

Raytracer::Vector3 Raytracer::Vector3::operator-() const {
  return Vector3(-x, -y, -z);
}

Raytracer::Vector3 Raytracer::Vector3::operator*(float scalar) const {
  return Vector3(x * scalar, y * scalar, z * scalar);
}

Raytracer::Vector3 Raytracer::Vector3::operator/(float scalar) const {
  return Vector3(x / scalar, y / scalar, z / scalar);
}

Raytracer::Vector3 &Raytracer::Vector3::operator+=(const Vector3 &other) {
  x += other.x;
  y += other.y;
  z += other.z;
  return *this;
}

Raytracer::Vector3 &Raytracer::Vector3::operator-=(const Vector3 &other) {
  x -= other.x;
  y -= other.y;
  z -= other.z;
  return *this;
}

Raytracer::Vector3 &Raytracer::Vector3::operator*=(float scalar) {
  x *= scalar;
  y *= scalar;
  z *= scalar;
  return *this;
}

Raytracer::Vector3 &Raytracer::Vector3::operator/=(float scalar) {
  x /= scalar;
  y /= scalar;
  z /= scalar;
  return *this;
}

float Raytracer::Vector3::length() const {
  return std::sqrt(x * x + y * y + z * z);
}

float Raytracer::Vector3::dot(const Vector3 &other) const {
  return x * other.x + y * other.y + z * other.z;
}

Raytracer::Vector3 Raytracer::Vector3::cross(const Vector3 &other) const {
  return Vector3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
}

Raytracer::Vector3 Raytracer::Vector3::normalized() const {
  float len = length();
  return len != 0 ? *this / len : Vector3(0, 0, 0);
}

std::ostream &operator<<(std::ostream &os, const Raytracer::Vector3 &vec) {
  os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
  return os;
}
