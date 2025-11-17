/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** main
*/

#include <iostream>
#include "Core/Scene.hpp"
#include "GlobalException.hpp"
#include "Parser/SceneParser.hpp"
#include "Renderer/Renderer.hpp"
#include "Utils/PpmWriter.hpp"

#ifdef USE_SFML
#include "Graphics/Graphics.hpp"
#endif

int main(const int argc, const char **argv) {
    if (argc != 2)
        return std::cerr << "USAGE: ./raytracer <SCENE_FILE>" << std::endl, 84;

    try {
        Raytracer::Scene scene;
        Raytracer::SceneParser parser(argv[1], scene);

        if (!parser.parse())
            throw GlobalException("Error [main] Failed to parse scene file.");

        const Raytracer::Camera &camera = scene.getCamera();
        int width = camera.getWidth();
        int height = camera.getHeight();

        Raytracer::Renderer renderer(scene, width, height);
        renderer.render(); // ⬅️ très important, sinon image vide

        if (!Raytracer::PPMWriter::write("output.ppm", renderer.getImage()))
            throw GlobalException("Error [main] Failed to write image to file.");

#ifdef USE_SFML
        Raytracer::Graphics graphics(width, height);
        graphics.run(scene, renderer);
#else
        std::cout << "✅ Image saved as output.ppm (SFML disabled)" << std::endl;
#endif

    } catch (GlobalException &e) {
        std::cerr << "raytracer: " << e.what() << std::endl;
        return 84;
    }

    return 0;
}