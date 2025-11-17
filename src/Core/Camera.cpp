/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Camera
*/

#include "Core/Camera.hpp"

Raytracer::Camera::Camera() : m_position(), m_rotation(), m_fieldOfView(60.0f), m_width(800), m_height(600) {
}

void Raytracer::Camera::setPosition(const Vector3 &pos) {
  m_position = pos;
}

void Raytracer::Camera::setRotation(const Vector3 &rot) {
  m_rotation = rot;
}

void Raytracer::Camera::setFieldOfView(float fov) {
  m_fieldOfView = fov;
}

void Raytracer::Camera::setResolution(int width, int height) {
  m_width = width;
  m_height = height;
}

const Raytracer::Vector3 &Raytracer::Camera::getPosition() const {
  return m_position;
}

const Raytracer::Vector3 &Raytracer::Camera::getRotation() const {
  return m_rotation;
}

float Raytracer::Camera::getFieldOfView() const {
  return m_fieldOfView;
}

int Raytracer::Camera::getWidth() const {
  return m_width;
}

int Raytracer::Camera::getHeight() const {
  return m_height;
}
