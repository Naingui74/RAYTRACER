/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Camera
*/

#pragma once

#include "Utils/Vector3.hpp"

namespace Raytracer {

    /**
     * @class Camera
     * @brief Represents a camera in the raytracer.
     *
     * Provides control over position, orientation, field of view, and resolution.
     */
    class Camera {
    public:
        /**
         * @brief Default constructor for the Camera class.
         */
        Camera();

        /**
         * @brief Set the camera's position in 3D space.
         * @param pos A Vector3 representing the new position.
         */
        void setPosition(const Vector3 &pos);

        /**
         * @brief Set the camera's rotation in degrees (pitch, yaw, roll).
         * @param rot A Vector3 representing the rotation.
         */
        void setRotation(const Vector3 &rot);

        /**
         * @brief Set the camera's field of view (FOV).
         * @param fov The field of view in degrees.
         */
        void setFieldOfView(float fov);

        /**
         * @brief Set the rendering resolution of the camera.
         * @param width The width in pixels.
         * @param height The height in pixels.
         */
        void setResolution(int width, int height);

        /**
         * @brief Get the current position of the camera.
         * @return A constant reference to the position Vector3.
         */
        const Vector3 &getPosition() const;

        /**
         * @brief Get the current rotation of the camera.
         * @return A constant reference to the rotation Vector3.
         */
        const Vector3 &getRotation() const;

        /**
         * @brief Get the field of view of the camera.
         * @return The FOV in degrees.
         */
        float getFieldOfView() const;

        /**
         * @brief Get the width of the resolution.
         * @return The width in pixels.
         */
        int getWidth() const;

        /**
         * @brief Get the height of the resolution.
         * @return The height in pixels.
         */
        int getHeight() const;

    private:
        Vector3 m_position;     ///< The position of the camera in 3D space.
        Vector3 m_rotation;     ///< The rotation of the camera (pitch, yaw, roll).
        float m_fieldOfView;    ///< The field of view in degrees.
        int m_width;            ///< The width of the resolution in pixels.
        int m_height;           ///< The height of the resolution in pixels.
    };

}
