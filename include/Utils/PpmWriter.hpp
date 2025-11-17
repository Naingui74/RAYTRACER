/**
 * @file PpmWriter.hpp
 * @brief PPM image file writer for the ray tracer
 *
 * @details
 * The PPMWriter class handles the export of rendered images to PPM (Portable PixMap) format.
 * It supports both direct saving from a Renderer instance and static writing of image buffers.
 * The PPM format is used for its simplicity and compatibility with many image viewers.
 *
 * @author [Your Name]
 * @date 2025 (EPITECH PROJECT)
 * @version 1.0.0
 * @copyright EPITECH PROJECT, 2025
 *
 * @note Outputs PPM files in binary format (P6)
 * @todo Add support for other image formats (PNG, JPEG)
 */

#pragma once

#include <string>
#include "Renderer/Renderer.hpp"

namespace Raytracer {

/**
 * @class PPMWriter
 * @brief Handles writing of images to PPM format files
 *
 * Provides functionality to save rendered images from the ray tracer
 * to PPM files. Can operate either with a Renderer reference or
 * directly with an image buffer.
 */
    class PPMWriter {
    public:
        /**
         * @brief Construct a new PPMWriter object
         * @param renderer Reference to the renderer containing the image to save
         */
        PPMWriter(const Renderer& renderer);

        /**
         * @brief Save the renderer's image to a PPM file
         * @param filename Path to the output file
         * @return true if file was successfully written, false otherwise
         */
        bool saveToFile(const std::string& filename) const;

        /**
         * @brief Static method to write any image buffer to PPM format
         * @param filename Path to the output file
         * @param image 2D vector of Colors representing the image
         * @return true if file was successfully written, false otherwise
         *
         * @note This static method can be used without instantiating PPMWriter
         */
        static bool write(const std::string& filename, const std::vector<std::vector<Color>>& image);

    private:
        const Renderer& m_renderer; ///< Reference to the renderer containing the image data
    };

} // namespace Raytracer