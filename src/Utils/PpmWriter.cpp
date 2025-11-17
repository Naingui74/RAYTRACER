/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** PPMWriter
*/

#include "Utils/PpmWriter.hpp"
#include <fstream>
#include <iostream>

Raytracer::PPMWriter::PPMWriter(const Renderer& renderer) : m_renderer(renderer) {
}

bool Raytracer::PPMWriter::write(const std::string& filename, const std::vector<std::vector<Color>>& image) {
  std::ofstream ofs(filename);
  if (!ofs.is_open())
    return false;

  int height = image.size();
  int width = height > 0 ? image[0].size() : 0;

  ofs << "P3\n" << width << " " << height << "\n255\n";
  for (const auto& row : image) {
    for (const auto& pixel : row) {
      ofs << pixel.getR() << " " << pixel.getG() << " " << pixel.getB() << " ";
    }
    ofs << "\n";
  }

  ofs.close();
  return true;
}

bool Raytracer::PPMWriter::saveToFile(const std::string& filename) const {
   try {
        std::ofstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open file for writing.");
            return false;
        }

        const auto& image = m_renderer.getImage();
        int height = image.size();
        int width = height > 0 ? image[0].size() : 0;

        file << "P3\n" << width << " " << height << "\n255\n";

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                Color color = image[y][x];
                color.clamp();
                file << color.getR() << " " << color.getG() << " " << color.getB() << " ";
            }
            file << "\n";
        }

        file.close();
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[PPMWriter] Exception while saving file '" << filename << "': " << e.what() << std::endl;
        return false;
    }
}