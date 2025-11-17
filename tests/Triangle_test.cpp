#include <catch2/catch_all.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "Primitives/Triangle.hpp"
#include "Maths/Ray.hpp"

using namespace Raytracer;

TEST_CASE("Triangle operations", "[triangle]") {
    Vector3 a(0.0f, 0.0f, 0.0f);
    Vector3 b(2.0f, 0.0f, 0.0f);
    Vector3 c(1.0f, 2.0f, 0.0f);
    Material material;
    material.setColor(Color(255, 0, 255)); // Magenta
    
    Triangle triangle(a, b, c, material);
    
    SECTION("Getters") {
        // Le centre (centroïde) devrait être la moyenne des trois sommets
        Vector3 center = triangle.getCenter();
        REQUIRE_THAT(center.x, Catch::Matchers::WithinRel(1.0f));
        REQUIRE_THAT(center.y, Catch::Matchers::WithinRel(2.0f/3.0f));
        REQUIRE_THAT(center.z, Catch::Matchers::WithinRel(0.0f));
        
        REQUIRE(triangle.getColor().getR() == 255);
        REQUIRE(triangle.getColor().getG() == 0);
        REQUIRE(triangle.getColor().getB() == 255);
    }
    
    SECTION("Ray intersection - hit") {
        // Rayon qui frappe le triangle
        Ray ray(Vector3(1.0f, 1.0f, -1.0f), Vector3(0.0f, 0.0f, 1.0f));
        float t;
        
        bool hit = triangle.intersect(ray, t);
        
        REQUIRE(hit == true);
        REQUIRE_THAT(t, Catch::Matchers::WithinRel(1.0f));
    }
    
    SECTION("Ray intersection - miss (outside)") {
        // Rayon qui passe à côté du triangle
        Ray ray(Vector3(3.0f, 1.0f, -1.0f), Vector3(0.0f, 0.0f, 1.0f));
        float t;
        
        bool hit = triangle.intersect(ray, t);
        
        REQUIRE(hit == false);
    }
    
    SECTION("Ray intersection - miss (parallel)") {
        // Rayon parallèle au triangle
        Ray ray(Vector3(1.0f, 1.0f, 1.0f), Vector3(1.0f, 0.0f, 0.0f));
        float t;
        
        bool hit = triangle.intersect(ray, t);
        
        REQUIRE(hit == false);
    }
    
    SECTION("Normal calculation") {
        // La normale doit être perpendiculaire au plan du triangle
        Vector3 normal = triangle.getNormal(Vector3(0.0f, 0.0f, 0.0f));
        
        // Le triangle est dans le plan XY, donc la normale devrait pointer selon l'axe Z
        REQUIRE_THAT(normal.x, Catch::Matchers::WithinRel(0.0f));
        REQUIRE_THAT(normal.y, Catch::Matchers::WithinRel(0.0f));
        REQUIRE_THAT(normal.z, Catch::Matchers::WithinRel(1.0f));
    }
    
    SECTION("Base center equals center") {
        Vector3 baseCenter = triangle.getBaseCenter();
        Vector3 center = triangle.getCenter();
        
        REQUIRE_THAT(baseCenter.x, Catch::Matchers::WithinRel(center.x));
        REQUIRE_THAT(baseCenter.y, Catch::Matchers::WithinRel(center.y));
        REQUIRE_THAT(baseCenter.z, Catch::Matchers::WithinRel(center.z));
    }
} 