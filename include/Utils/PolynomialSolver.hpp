/**
 * @file PolynomialSolver.hpp
 * @brief Polynomial equation solver for ray-object intersections
 *
 * @details
 * The PolynomialSolver class provides static methods for solving quadratic, cubic,
 * and quartic polynomial equations. These are essential for calculating ray-object
 * intersections in the ray tracer, particularly for complex shapes like toruses.
 * The solver uses a combination of analytical methods and Newton-Raphson refinement.
 *
 * @author [Your Name]
 * @date 2025 (EPITECH PROJECT)
 * @version 1.0.0
 * @copyright EPITECH PROJECT, 2025
 *
 * @note Uses Newton-Raphson method for root refinement
 * @warning Solutions may be approximate due to floating-point precision
 * @todo Implement more robust numerical methods for ill-conditioned polynomials
 */

#pragma once

#include <array>
#include <cmath>
#include <algorithm>

namespace Raytracer {

/**
 * @class PolynomialSolver
 * @brief Static class for solving polynomial equations up to degree 4
 *
 * Provides numerical methods for finding real roots of:
 * - Quadratic equations (degree 2)
 * - Cubic equations (degree 3)
 * - Quartic equations (degree 4)
 *
 * Used primarily for computing ray-object intersection points.
 */
    class PolynomialSolver {
    public:
        /**
         * @brief Solves a quartic equation ax⁴ + bx³ + cx² + dx + e = 0
         * @param a x⁴ coefficient
         * @param b x³ coefficient
         * @param c x² coefficient
         * @param d x coefficient
         * @param e Constant term
         * @param roots Array to store found roots
         * @return int Number of real roots found
         */
        static int solveQuartic(float a, float b, float c, float d, float e, float roots[4]);

        /**
         * @brief Solves a cubic equation ax³ + bx² + cx + d = 0
         * @param a x³ coefficient
         * @param b x² coefficient
         * @param c x coefficient
         * @param d Constant term
         * @param roots Array to store found roots
         * @return int Number of real roots found
         */
        static int solveCubic(float a, float b, float c, float d, float roots[3]);

        /**
         * @brief Solves a quadratic equation ax² + bx + c = 0
         * @param a x² coefficient
         * @param b x coefficient
         * @param c Constant term
         * @param roots Array to store found roots
         * @return int Number of real roots found (0, 1, or 2)
         */
        static int solveQuadratic(float a, float b, float c, float roots[2]);

    private:
        static constexpr float EPSILON = 1e-6f;      ///< Tolerance for root validation
        static constexpr int MAX_ITERATIONS = 100;   ///< Maximum Newton-Raphson iterations

        /**
         * @brief Refines a root guess using Newton-Raphson method
         * @param a-d Polynomial coefficients
         * @param guess Initial root estimate
         * @return float Refined root approximation
         */
        static float newtonRaphson(float a, float b, float c, float d, float e, float guess);

        /**
         * @brief Validates if a value is a proper root of the polynomial
         * @param x Potential root to test
         * @param a-e Polynomial coefficients
         * @return true if x is a valid root within EPSILON tolerance
         */
        static bool isRootValid(float x, float a, float b, float c, float d, float e);
    };

} // namespace Raytracer