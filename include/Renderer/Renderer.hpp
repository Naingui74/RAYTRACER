/**
 * @file Renderer.hpp
 * @brief Core rendering system for the ray tracer
 *
 * @details
 * The Renderer class handles the complete rendering pipeline from scene description
 * to final image. It implements recursive ray tracing with Blinn-Phong shading model,
 * reflections, and shadows. The renderer processes the scene pixel by pixel,
 * computing ray directions through a virtual camera and accumulating lighting effects.
 *
 * @author [Your Name]
 * @date 2025 (EPITECH PROJECT)
 * @version 1.0.0
 * @copyright EPITECH PROJECT, 2025
 *
 * @note Uses recursive ray tracing with configurable maximum depth
 * @todo Implement anti-aliasing and acceleration structures
 */

#pragma once
#include <vector>
#include "Core/Scene.hpp"
#include "Maths/Ray.hpp"
#include "Utils/Color.hpp"
#include "Utils/Vector3.hpp"
#include "Material/Material.hpp"
namespace Raytracer {

/**
 * @class Renderer
 * @brief Main rendering engine that converts a Scene into a 2D image
 *
 * The Renderer takes a Scene description and produces a 2D image by shooting rays
 * through each pixel, computing intersections with scene objects, and applying
 * lighting calculations. It supports:
 * - Primary ray casting
 * - Recursive reflections
 * - Blinn-Phong shading model
 * - Hard shadows
 * - Camera transformations
 */
    class Renderer {
    public:
        /**
         * @brief Construct a new Renderer object
         * @param scene Reference to the scene to render
         * @param width Output image width in pixels
         * @param height Output image height in pixels
         */
        Renderer(const Scene& scene, int width, int height);

        /**
         * @brief Executes the complete rendering process
         *
         * Iterates over all pixels in the output image, computes ray directions,
         * traces rays through the scene, and stores the resulting colors.
         */
        void render();

        /**
         * @brief Get the rendered image buffer
         * @return const std::vector<std::vector<Color>>& 2D array of computed pixel colors
         */
        const std::vector<std::vector<Color>>& getImage() const;

    private:
        const Scene& m_scene;                           ///< Reference to the scene being rendered
        int m_width;                                    ///< Output image width
        int m_height;                                   ///< Output image height
        std::vector<std::vector<Color>> m_image;        ///< Output image buffer

        /**
         * @brief Computes ray direction for a given pixel coordinate
         * @param x Pixel x-coordinate (0 to width-1)
         * @param y Pixel y-coordinate (0 to height-1)
         * @return Vector3 Normalized ray direction in world space
         */
        Vector3 computeRayDirection(int x, int y) const;

        /**
         * @brief Traces a ray through the scene recursively
         * @param ray Ray to trace
         * @param depth Current recursion depth
         * @return Color Computed color for this ray path
         */
        Color traceRay(const Ray& ray, int depth) const;

        /**
         * @brief Computes reflection color at a hit point
         * @param hitPoint World-space intersection point
         * @param normal Surface normal at hit point
         * @param ray Incident ray
         * @param depth Current recursion depth
         * @return Color Reflection color contribution
         */
        Color getReflectionColor(const Vector3& hitPoint, const Vector3& normal, const Ray& ray, int depth) const;
        // Éclaire le point d'intersection selon Blinn-Phong + ombres
        Color shadeHit(const Vector3& hitPoint, const Vector3& normal, const Color& baseColor, const Color& reflectionColor, const Material& material) const;
        // Écrit la couleur 'color' au pixel (x,y) de m_image
        void setPixel(int x, int y, const Color& color);

        /**
         * @brief Rotates a vector around X axis
         * @param v Vector to rotate
         * @param a Angle in radians
         * @return Vector3 Rotated vector
         */
        Vector3 rotateX(const Vector3& v, float a) const;

        /**
         * @brief Rotates a vector around Y axis
         * @param v Vector to rotate
         * @param a Angle in radians
         * @return Vector3 Rotated vector
         */
        Vector3 rotateY(const Vector3& v, float a) const;

        /**
         * @brief Rotates a vector around Z axis
         * @param v Vector to rotate
         * @param a Angle in radians
         * @return Vector3 Rotated vector
         */
        Vector3 rotateZ(const Vector3& v, float a) const;
    };

} // namespace Raytracer