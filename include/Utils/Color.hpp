/**
 * @file Color.hpp
 * @brief RGB Color representation for the ray tracer
 *
 * @details
 * The Color class represents an RGB color with 8-bit precision per channel (0-255).
 * It provides basic color manipulation capabilities including component access,
 * modification, and value clamping to ensure valid color ranges.
 *
 * @author [Your Name]
 * @date 2025 (EPITECH PROJECT)
 * @version 1.0.0
 * @copyright EPITECH PROJECT, 2025
 *
 * @note All color components are stored as integers in range [0-255]
 * @todo Add color operations (addition, multiplication, blending)
 */

#pragma once

#include <algorithm>
#include <iostream>

namespace Raytracer {

/**
 * @class Color
 * @brief RGB color representation with 8-bit channels
 *
 * Stores and manipulates color information in RGB format.
 * Provides methods for component access and basic color operations.
 */
    class Color {
    public:
        /**
         * @brief Default constructor (initializes to black)
         */
        Color();

        /**
         * @brief Construct a new Color object with specified components
         * @param r Red component (0-255)
         * @param g Green component (0-255)
         * @param b Blue component (0-255)
         */
        Color(int r, int g, int b);

        /**
         * @brief Get the red component
         * @return int Red value (0-255)
         */
        int getR() const;

        /**
         * @brief Get the green component
         * @return int Green value (0-255)
         */
        int getG() const;

        /**
         * @brief Get the blue component
         * @return int Blue value (0-255)
         */
        int getB() const;

        /**
         * @brief Set the red component
         * @param r Red value (will be clamped to 0-255)
         */
        void setR(int r);

        /**
         * @brief Set the green component
         * @param g Green value (will be clamped to 0-255)
         */
        void setG(int g);

        /**
         * @brief Set the blue component
         * @param b Blue value (will be clamped to 0-255)
         */
        void setB(int b);

        /**
         * @brief Clamp all color components to valid range [0-255]
         */
        void clamp();
        
        /**
         * @brief Addition operator for colors
         * @param other The color to add
         * @return Color Result of addition (components are clamped to [0-255])
         */
        Color operator+(const Color& other) const;

        /**
         * @brief Subtraction operator for colors
         * @param other The color to subtract
         * @return Color Result of subtraction (components are clamped to [0-255])
         */
        Color operator-(const Color& other) const;

        /**
         * @brief Multiplication operator with scalar
         * @param scalar The scalar value to multiply by
         * @return Color Result of multiplication (components are clamped to [0-255])
         */
        Color operator*(float scalar) const;

        /**
         * @brief Multiplication operator with another color
         * @param other The color to multiply by (each component is treated as [0-1] range)
         * @return Color Result of multiplication (components are clamped to [0-255])
         */
        Color operator*(const Color& other) const;

    private:
        int m_r; ///< Red component (0-255)
        int m_g; ///< Green component (0-255)
        int m_b; ///< Blue component (0-255)
    };

/**
 * @brief Output stream operator for Color
 * @param os Output stream
 * @param color Color to output
 * @return std::ostream& Stream with color representation
 *
 * Outputs color in format "Color(r, g, b)"
 */
    std::ostream &operator<<(std::ostream &os, const Raytracer::Color &color);

} // namespace Raytracer