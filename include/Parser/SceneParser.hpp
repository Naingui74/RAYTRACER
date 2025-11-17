/**
 * @file SceneParser.hpp
 * @brief Configuration file parser for raytracer scenes
 * @author EPITECH
 * @date 2025
 *
 * This file contains the SceneParser class which is responsible for loading and
 * parsing scene configuration files. It uses the libconfig++ library to read
 * structured configuration data and populates a Scene object with cameras,
 * lights, and primitive objects defined in the configuration.
 */

#pragma once

#include <libconfig.h++>
#include <string>
#include "Core/Scene.hpp"
#include "Utils/Vector3.hpp"

namespace Raytracer {
    /**
     * @class SceneParser
     * @brief Parser for scene configuration files
     *
     * This class provides functionality to read and parse scene description files in libconfig
     * format. It extracts scene elements such as camera properties, lights, and various
     * geometric primitives, then populates a Scene object with these elements.
     */
    class SceneParser {
    public:
        /**
         * @brief Construct a new Scene Parser object
         *
         * @param filename Path to the scene configuration file
         * @param scene Reference to the Scene object to be populated
         */
        SceneParser(const std::string &filename, Scene &scene);

        /**
         * @brief Parse the configuration file and populate the scene
         *
         * @return bool True if parsing was successful, false otherwise
         */
        bool parse();

    private:
      bool parseCamera(const libconfig::Setting &root);
      bool parseLights(const libconfig::Setting &root);
      bool parsePrimitives(const libconfig::Setting &root);
      void parseSpheres(const libconfig::Setting &prims);
      void parsePlanes(const libconfig::Setting &prims);
      Vector3 parseVector3(const libconfig::Setting &setting);
      Material parseMaterial(const libconfig::Setting &setting, const Color &defaultColor);

    private:
      std::string m_filename;
      libconfig::Config m_cfg;
      Scene &m_scene;
  };
}  // namespace Raytracer
