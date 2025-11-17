/**
 * @file Vector3.hpp
 * @brief 3D vector implementation for geometric calculations
 *
 * @details
 * The Vector3 class represents a 3-dimensional vector with common operations
 * needed for ray tracing and 3D graphics. It provides both component-wise access
 * and mathematical operations including dot product, cross product, and normalization.
 *
 * @author [Your Name]
 * @date 2025 (EPITECH PROJECT)
 * @version 1.0.0
 * @copyright EPITECH PROJECT, 2025
 *
 * @note All operations are component-wise unless otherwise specified
 * @todo Add more geometric operations (reflection, refraction)
 */

#pragma once

#include <cmath>
#include <iostream>

namespace Raytracer {

/**
 * @class Vector3
 * @brief 3D vector with common mathematical operations
 *
 * Represents a vector in 3D space with x, y, z components.
 * Provides essential operations for vector mathematics including:
 * - Arithmetic operations
 * - Dot and cross products
 * - Vector normalization
 * - Length calculations
 */
    class Vector3 {
    public:
        float x; ///< X component of the vector
        float y; ///< Y component of the vector
        float z; ///< Z component of the vector

        /**
         * @brief Default constructor (initializes to zero vector)
         */
        Vector3();

        /**
         * @brief Construct a new Vector3 with specified components
         * @param x X component
         * @param y Y component
         * @param z Z component
         */
        Vector3(float x, float y, float z);

        /**
         * @brief Vector addition
         * @param other Vector to add
         * @return Vector3 Resulting vector
         */
        Vector3 operator+(const Vector3 &other) const;

        /**
         * @brief Vector subtraction
         * @param other Vector to subtract
         * @return Vector3 Resulting vector
         */
        Vector3 operator-(const Vector3 &other) const;

        /**
         * @brief Vector negation
         * @return Vector3 Negated vector
         */
        Vector3 operator-() const;

        /**
         * @brief Scalar multiplication
         * @param scalar Multiplication factor
         * @return Vector3 Scaled vector
         */
        Vector3 operator*(float scalar) const;

        /**
         * @brief Scalar division
         * @param scalar Division factor
         * @return Vector3 Scaled vector
         * @warning Division by zero is not checked
         */
        Vector3 operator/(float scalar) const;

        /**
         * @brief Compound vector addition
         * @param other Vector to add
         * @return Vector3& Reference to modified vector
         */
        Vector3 &operator+=(const Vector3 &other);

        /**
         * @brief Compound vector subtraction
         * @param other Vector to subtract
         * @return Vector3& Reference to modified vector
         */
        Vector3 &operator-=(const Vector3 &other);

        /**
         * @brief Compound scalar multiplication
         * @param scalar Multiplication factor
         * @return Vector3& Reference to modified vector
         */
        Vector3 &operator*=(float scalar);

        /**
         * @brief Compound scalar division
         * @param scalar Division factor
         * @return Vector3& Reference to modified vector
         * @warning Division by zero is not checked
         */
        Vector3 &operator/=(float scalar);

        /**
         * @brief Calculate vector length (magnitude)
         * @return float Length of the vector
         */
        float length() const;

        /**
         * @brief Calculate dot product with another vector
         * @param other Vector to compute dot product with
         * @return float Dot product result
         */
        float dot(const Vector3 &other) const;

        /**
         * @brief Calculate cross product with another vector
         * @param other Vector to compute cross product with
         * @return Vector3 Cross product result
         */
        Vector3 cross(const Vector3 &other) const;

        /**
         * @brief Get normalized version of the vector
         * @return Vector3 Unit vector in same direction
         * @warning Returns zero vector if length is zero
         */
        Vector3 normalized() const;

        /**
         * @brief Output stream operator for Vector3
         * @param os Output stream
         * @param vec Vector to output
         * @return std::ostream& Stream with vector representation
         *
         * Outputs vector in format "Vector3(x, y, z)"
         */
        friend std::ostream &operator<<(std::ostream &os, const Vector3 &vec);
    };

    /**
     * @brief Scalar multiplication (left side)
     * @param scalar Scalar to multiply by
     * @param vec Vector to scale
     * @return Vector3 Scaled vector
     */
    inline Vector3 operator*(float scalar, const Vector3 &vec) {
        return vec * scalar;
    }

} // namespace Raytracer