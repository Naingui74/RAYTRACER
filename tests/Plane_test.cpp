#include <catch2/catch_all.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "Primitives/Plane.hpp"
#include "Maths/Ray.hpp"

using namespace Raytracer;

TEST_CASE("Plane operations", "[plane]") {
    Vector3 normal(0.0f, 1.0f, 0.0f);
    float distance = 2.0f;
    Material material;
    material.setColor(Color(0, 255, 0)); // Vert
    
    Plane plane(normal, distance, material);
    
    SECTION("Getters") {
        Vector3 surfaceNormal = plane.getNormal(Vector3(0.0f, 0.0f, 0.0f));
        REQUIRE(surfaceNormal.x == 0.0f);
        REQUIRE(surfaceNormal.y == 1.0f);
        REQUIRE(surfaceNormal.z == 0.0f);
        
        REQUIRE(plane.getColor().getG() == 255);
        
        Vector3 center = plane.getCenter();
        REQUIRE(center.x == 0.0f);
        REQUIRE(center.y == 2.0f);
        REQUIRE(center.z == 0.0f);
    }
    
    SECTION("Ray intersection - hit") {
        Ray ray(Vector3(0.0f, 5.0f, 0.0f), Vector3(0.0f, -1.0f, 0.0f));
        float t;
        
        bool hit = plane.intersect(ray, t);
        
        REQUIRE(hit == true);
        REQUIRE_THAT(t, Catch::Matchers::WithinRel(3.0f));
    }
    
    SECTION("Ray intersection - miss (parallel)") {
        Ray ray(Vector3(0.0f, 5.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f));
        float t;
        
        bool hit = plane.intersect(ray, t);
        
        REQUIRE(hit == false);
    }
    
    SECTION("Ray intersection - miss (wrong direction)") {
        Ray ray(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));
        float t;
        
        bool hit = plane.intersect(ray, t);
        
        REQUIRE(hit == false);
    }
} 