/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Cone
*/

#include "Utils/PolynomialSolver.hpp"
#include <ostream>
#include <iostream>

namespace Raytracer {

    int PolynomialSolver::solveQuadratic(float a, float b, float c, float roots[2]) {
        if (std::abs(a) < EPSILON) {
            if (std::abs(b) < EPSILON)
                return 0;  // No solution
            roots[0] = -c / b;
            return 1;  // One root
        }

        float discriminant = b * b - 4 * a * c;
        if (discriminant < -EPSILON)  // Ensure small negative discriminants are treated as no real roots
            return 0;  // No real roots

        if (discriminant < EPSILON) {  // Single root when discriminant is close to zero
            roots[0] = -b / (2 * a);
            return 1;
        }

        float sqrt_discr = std::sqrt(discriminant);
        roots[0] = (-b - sqrt_discr) / (2 * a);
        roots[1] = (-b + sqrt_discr) / (2 * a);
        return 2;  // Two real roots
    }


    int PolynomialSolver::solveCubic(float a, float b, float c, float d, float roots[3]) {
        if (std::abs(a) < EPSILON)
            return solveQuadratic(b, c, d, roots);

        b /= a;
        c /= a;
        d /= a;
        a = 1.0f;

        float Q = (b * b - 3 * c) / 9.0f;
        float R = (2 * b * b * b - 9 * b * c + 27 * d) / 54.0f;
        float Q3 = Q * Q * Q;
        float D = Q3 - R * R;

        if (D < -EPSILON)  // Ensure small negative discriminant values are treated as no real roots
            return 0;  // No real roots

        if (D >= 0) {
            float theta = std::acos(std::clamp(R / std::sqrt(Q3), -1.0f, 1.0f));
            float sqrtQ = std::sqrt(Q);
            roots[0] = -2 * sqrtQ * std::cos(theta / 3) - b / 3;
            roots[1] = -2 * sqrtQ * std::cos((theta + 2 * M_PI) / 3) - b / 3;
            roots[2] = -2 * sqrtQ * std::cos((theta - 2 * M_PI) / 3) - b / 3;
            return 3;  // Three real roots
        } else {
            float A = -std::cbrt(std::abs(R) + std::sqrt(-D));
            if (R < 0) A = -A;
            float B = (std::abs(A) < EPSILON) ? 0.0f : Q / A;

            roots[0] = (A + B) - b / 3;
            return 1;  // One real root
        }
    }
}