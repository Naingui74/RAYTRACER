#include <catch2/catch_all.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "Primitives/Cone.hpp"
#include "Maths/Ray.hpp"

using namespace Raytracer;

TEST_CASE("Cone operations", "[cone]") {
    Vector3 baseCenter(0.0f, 0.0f, 0.0f);
    float radius = 2.0f;
    float height = 5.0f;
    Vector3 rotation(0.0f, 0.0f, 0.0f); // Pas de rotation
    Material material;
    material.setColor(Color(255, 0, 0)); // Rouge
    
    Cone cone(baseCenter, radius, height, rotation, material);
    
    SECTION("Getters") {
        Vector3 center = cone.getCenter();
        // Le centre est à 1/3 de la hauteur depuis la base
        REQUIRE_THAT(center.y, Catch::Matchers::WithinRel(height / 3.0f));
        
        REQUIRE(cone.getColor().getR() == 255);
        REQUIRE(cone.getColor().getG() == 0);
        REQUIRE(cone.getColor().getB() == 0);
        
        Vector3 base = cone.getBaseCenter();
        REQUIRE(base.x == 0.0f);
        REQUIRE(base.y == 0.0f);
        REQUIRE(base.z == 0.0f);
    }
    
    SECTION("Ray intersection - hit side") {
        // Rayon qui frappe le côté du cône
        Ray ray(Vector3(3.0f, 2.5f, 0.0f), Vector3(-1.0f, 0.0f, 0.0f));
        float t;
        
        bool hit = cone.intersect(ray, t);
        
        REQUIRE(hit == true);
    }
    
    SECTION("Ray intersection - hit base") {
        // Rayon qui frappe la base du cône
        Ray ray(Vector3(0.0f, -2.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));
        float t;
        
        bool hit = cone.intersect(ray, t);
        
        REQUIRE(hit == true);
    }
    
    SECTION("Ray intersection - miss") {
        // Rayon qui passe à côté du cône
        Ray ray(Vector3(5.0f, 2.5f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));
        float t;
        
        bool hit = cone.intersect(ray, t);
        
        REQUIRE(hit == false);
    }
    
    SECTION("Normal calculation - side") {
        // Un point sur le côté du cône
        Vector3 point(1.0f, 2.5f, 0.0f);
        
        Vector3 normal = cone.getNormal(point);
        
        // La normale ne doit pas être parallèle à l'axe du cône (0,1,0)
        REQUIRE(normal.y != 1.0f);
        REQUIRE(normal.length() > 0.99f); // La normale doit être normalisée
    }
    
    SECTION("Normal calculation - base") {
        // Un point sur la base du cône
        Vector3 point(0.5f, 0.0f, 0.5f);
        
        Vector3 normal = cone.getNormal(point);
        
        // La normale de la base pointe vers le bas
        REQUIRE(normal.y < 0.0f);
        REQUIRE_THAT(normal.length(), Catch::Matchers::WithinRel(1.0f));
    }
} 