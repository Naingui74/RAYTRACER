/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** ObjParser
*/

#include "Parser/ObjParser.hpp"
#include "GlobalException.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <thread>
#include <future>
#include <cmath>
#include <algorithm>
#include <iostream>

#ifndef M_PI
#endif

namespace Raytracer {

    inline Vector3 applyRotation(const Vector3 &point, const Vector3 &rotation)
    {
        const float radX = rotation.x * M_PI / 180.0f;
        const float radY = rotation.y * M_PI / 180.0f;
        const float radZ = rotation.z * M_PI / 180.0f;
        float cosX = std::cos(radX), sinX = std::sin(radX);
        float cosY = std::cos(radY), sinY = std::sin(radY);
        float cosZ = std::cos(radZ), sinZ = std::sin(radZ);
        Vector3 p = point;
        float y1 = p.y * cosX - p.z * sinX;
        float z1 = p.y * sinX + p.z * cosX;
        p.y = y1; p.z = z1;
        float x2 = p.x * cosY + p.z * sinY;
        float z2 = -p.x * sinY + p.z * cosY;
        p.x = x2; p.z = z2;
        float x3 = p.x * cosZ - p.y * sinZ;
        float y3 = p.x * sinZ + p.y * cosZ;
        p.x = x3; p.y = y3;
        return p;
    }

    std::vector<ParsedTriangle> ObjParser::loadFromFile(const std::string &filename, float scale, const Vector3 &offset, const Vector3 &rotation)
    {
        std::ifstream file(filename);
        if (!file.is_open())
            throw GlobalException("ObjParser: Failed to open file: " + filename);
        std::vector<std::string> lines;
        std::string line;
        while (std::getline(file, line)) {
            if (!line.empty() && line[0] != '#')
                lines.push_back(std::move(line));
        }
        file.close();
        std::vector<size_t> vertexLineIndices;
        std::vector<const char*> faceLines;
        for (size_t i = 0; i < lines.size(); ++i) {
            const std::string &l = lines[i];
            if (l.size() > 1 && l[0] == 'v' && l[1] == ' ')
                vertexLineIndices.push_back(i);
            else if (l.size() > 1 && l[0] == 'f' && l[1] == ' ')
                faceLines.push_back(l.c_str());
        }
        size_t vertexCount = vertexLineIndices.size();
        std::vector<Vector3> vertices(vertexCount);
        unsigned int threadCount = std::thread::hardware_concurrency();
        if (threadCount == 0) threadCount = 4;
        size_t vertexChunkSize = (vertexCount + threadCount - 1) / threadCount;
        std::vector<std::future<void>> vertexFutures;
        for (size_t t = 0; t < threadCount; ++t) {
            size_t start = t * vertexChunkSize;
            size_t end = std::min(start + vertexChunkSize, vertexCount);
            vertexFutures.emplace_back(std::async(std::launch::async, [&, start, end, t]() {
                for (size_t i = start; i < end; ++i) {
                    if (i >= vertexLineIndices.size()) {
                        std::cerr << "[Thread " << t << "] Invalid vertexLineIndices index: " << i << "\n";
                        continue;
                    }
                    size_t lineIndex = vertexLineIndices[i];
                    if (lineIndex >= lines.size()) {
                        std::cerr << "[Thread " << t << "] Line index out of range: " << lineIndex << "\n";
                        continue;
                    }
                    const char* vLine = lines[lineIndex].c_str() + 2;
                    std::istringstream iss(vLine);
                    float x = 0, y = 0, z = 0;
                    iss >> x >> y >> z;
                    Vector3 v(x * scale, y * scale, z * scale);
                    v = applyRotation(v, rotation) + offset;
                    if (i >= vertices.size()) {
                        std::cerr << "[Thread " << t << "] Vertex index out of range on write: " << i << "\n";
                        continue;
                    }
                    vertices[i] = v;
                }
            }));
        }
        for (auto &f : vertexFutures) f.get();
        std::vector<std::vector<ParsedTriangle>> threadTriangles(threadCount);
        size_t faceCount = faceLines.size();
        size_t faceChunkSize = (faceCount + threadCount - 1) / threadCount;
        std::vector<std::future<void>> faceFutures;
        for (size_t t = 0; t < threadCount; ++t) {
            size_t start = t * faceChunkSize;
            size_t end = std::min(start + faceChunkSize, faceCount);
            faceFutures.emplace_back(std::async(std::launch::async, [&, start, end, t]() {
                std::vector<ParsedTriangle> &local = threadTriangles[t];
                for (size_t i = start; i < end; ++i) {
                    if (!faceLines[i]) {
                        std::cerr << "[Thread " << t << "] Null face line pointer at " << i << "\n";
                        continue;
                    }
                    const char* fLine = faceLines[i] + 2;
                    std::istringstream iss(fLine);
                    std::vector<int> indices;
                    std::string token;
                    while (iss >> token) {
                        size_t pos = token.find('/');
                        std::string idxStr = (pos == std::string::npos) ? token : token.substr(0, pos);
                        try {
                            int idx = std::stoi(idxStr) - 1;
                            indices.push_back(idx);
                        } catch (...) {
                            std::cerr << "[Thread " << t << "] Invalid face token: " << token << "\n";
                        }
                    }
                    if (indices.size() >= 3) {
                        for (size_t j = 1; j + 1 < indices.size(); ++j) {
                            int i0 = indices[0], i1 = indices[j], i2 = indices[j + 1];
                            if (i0 < 0 || i1 < 0 || i2 < 0 ||
                                i0 >= static_cast<int>(vertices.size()) ||
                                i1 >= static_cast<int>(vertices.size()) ||
                                i2 >= static_cast<int>(vertices.size())) {
                                std::cerr << "[Thread " << t << "] Face index out of bounds: "
                                          << i0 << ", " << i1 << ", " << i2 << "\n";
                                continue;
                            }
                            local.emplace_back(ParsedTriangle{
                                vertices[i0], vertices[i1], vertices[i2]
                            });
                        }
                    }
                }
            }));
        }
        for (auto &f : faceFutures) f.get();
        std::vector<ParsedTriangle> triangles;
        for (auto &local : threadTriangles)
            triangles.insert(triangles.end(), local.begin(), local.end());
        return triangles;
    }

}