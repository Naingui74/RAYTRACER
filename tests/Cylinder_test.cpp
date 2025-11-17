#include <catch2/catch_all.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "Primitives/Cylinder.hpp"
#include "Maths/Ray.hpp"

using namespace Raytracer;

TEST_CASE("Cylinder operations", "[cylinder]") {
    Vector3 baseCenter(0.0f, 0.0f, 0.0f);
    float radius = 2.0f;
    float height = 4.0f;
    Vector3 rotation(0.0f, 0.0f, 0.0f); // Pas de rotation
    Material material;
    material.setColor(Color(0, 255, 0)); // Vert
    
    Cylinder cylinder(baseCenter, radius, height, rotation, material);
    
    SECTION("Getters") {
        Vector3 center = cylinder.getCenter();
        // Le centre est à mi-hauteur
        REQUIRE_THAT(center.y, Catch::Matchers::WithinRel(height / 2.0f));
        
        REQUIRE(cylinder.getColor().getR() == 0);
        REQUIRE(cylinder.getColor().getG() == 255);
        REQUIRE(cylinder.getColor().getB() == 0);
        
        Vector3 base = cylinder.getBaseCenter();
        REQUIRE(base.x == 0.0f);
        REQUIRE(base.y == 0.0f);
        REQUIRE(base.z == 0.0f);
    }
    
    SECTION("Ray intersection - hit curved surface") {
        // Rayon qui frappe la surface courbe du cylindre
        Ray ray(Vector3(3.0f, 2.0f, 0.0f), Vector3(-1.0f, 0.0f, 0.0f));
        float t;
        
        bool hit = cylinder.intersect(ray, t);
        
        REQUIRE(hit == true);
        // La distance devrait être proche de 1 (rayon commence à x=3, cylindre a r=2)
        REQUIRE_THAT(t, Catch::Matchers::WithinRel(1.0f));
    }
    
    SECTION("Ray intersection - hit base") {
        // Rayon qui frappe la base du cylindre
        Ray ray(Vector3(0.0f, -2.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));
        float t;
        
        bool hit = cylinder.intersect(ray, t);
        
        REQUIRE(hit == true);
        REQUIRE_THAT(t, Catch::Matchers::WithinRel(2.0f));
    }
    
    SECTION("Ray intersection - hit top") {
        // Rayon qui frappe le haut du cylindre
        Ray ray(Vector3(0.0f, 6.0f, 0.0f), Vector3(0.0f, -1.0f, 0.0f));
        float t;
        
        bool hit = cylinder.intersect(ray, t);
        
        REQUIRE(hit == true);
        REQUIRE_THAT(t, Catch::Matchers::WithinRel(2.0f));
    }
    
    SECTION("Ray intersection - miss") {
        // Rayon qui passe à côté du cylindre
        Ray ray(Vector3(5.0f, 2.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));
        float t;
        
        bool hit = cylinder.intersect(ray, t);
        
        REQUIRE(hit == false);
    }
    
    SECTION("Normal calculation - curved surface") {
        // Un point sur la surface courbe du cylindre
        Vector3 point(2.0f, 2.0f, 0.0f);
        
        Vector3 normal = cylinder.getNormal(point);
        
        // La normale doit pointer vers l'extérieur (le long de l'axe X)
        REQUIRE_THAT(normal.x, Catch::Matchers::WithinRel(1.0f));
        REQUIRE_THAT(normal.y, Catch::Matchers::WithinRel(0.0f));
        REQUIRE_THAT(normal.z, Catch::Matchers::WithinRel(0.0f));
    }
    
    SECTION("Normal calculation - base") {
        // Un point sur la base du cylindre
        Vector3 point(0.5f, 0.0f, 0.5f);
        
        Vector3 normal = cylinder.getNormal(point);
        
        // La normale de la base pointe vers le bas
        REQUIRE_THAT(normal.y, Catch::Matchers::WithinRel(-1.0f));
    }
    
    SECTION("Normal calculation - top") {
        // Un point sur le haut du cylindre
        Vector3 point(0.5f, height, 0.5f);
        
        Vector3 normal = cylinder.getNormal(point);
        
        // La normale du haut pointe vers le haut
        REQUIRE_THAT(normal.y, Catch::Matchers::WithinRel(1.0f));
    }
} 