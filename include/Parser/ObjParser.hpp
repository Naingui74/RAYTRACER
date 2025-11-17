/**
 * @file ObjParser.hpp
 * @brief OBJ file format parser for the raytracer
 * @author EPITECH
 * @date 2025
 *
 * This file contains the ObjParser class which provides functionality
 * for loading 3D models from Wavefront OBJ file format. It extracts
 * geometric data and converts it into triangle primitives that can
 * be used in the raytracing engine.
 */
#pragma once
#include <vector>
#include "Utils/Vector3.hpp"

namespace Raytracer {

    /**
     * @struct ParsedTriangle
     * @brief Represents a triangle parsed from an OBJ file
     *
     * This structure stores the three vertices of a triangle extracted
     * from an OBJ file, in the form of 3D vector coordinates.
     */
    struct ParsedTriangle {
        Vector3 a; /**< First vertex of the triangle */
        Vector3 b; /**< Second vertex of the triangle */
        Vector3 c; /**< Third vertex of the triangle */
    };

    /**
     * @class ObjParser
     * @brief Parser utility for Wavefront OBJ files
     *
     * This class provides static methods for loading and parsing OBJ files,
     * converting the mesh data into a collection of triangles that can be
     * used for raytracing.
     */
    class ObjParser {
    public:
        /**
         * @brief Load triangles from an OBJ file with transformation options
         *
         * @param filename Path to the OBJ file to be loaded
         * @param scale Uniform scale factor to apply to the model (default: 1.0)
         * @param offset Translation vector to apply to the model (default: origin)
         * @param rotation Rotation vector in radians for X, Y, and Z axes (default: no rotation)
         * @return std::vector<ParsedTriangle> Collection of triangles extracted from the file
         *
         * This method reads an OBJ file, extracts the mesh data, applies the
         * specified transformations (scaling, translation, and rotation),
         * and returns the resulting triangles.
         */
        static std::vector<ParsedTriangle> loadFromFile(const std::string &filename, float scale = 1.0f, const Vector3 &offset = Vector3(0.0f, 0.0f, 0.0f), const Vector3 &rotation = Vector3(0.0f, 0.0f, 0.0f));
    };

}