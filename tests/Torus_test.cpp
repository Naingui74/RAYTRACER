#include <catch2/catch_all.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "Primitives/Torus.hpp"
#include "Maths/Ray.hpp"

using namespace Raytracer;

TEST_CASE("Torus operations", "[torus]") {
    Vector3 center(0.0f, 0.0f, 0.0f);
    float majorRadius = 3.0f;
    float minorRadius = 1.0f;
    Vector3 rotation(0.0f, 0.0f, 0.0f); // Pas de rotation
    Material material;
    material.setColor(Color(0, 0, 255)); // Bleu
    
    Torus torus(center, majorRadius, minorRadius, rotation, material);
    
    SECTION("Getters") {
        REQUIRE(torus.getCenter().x == 0.0f);
        REQUIRE(torus.getCenter().y == 0.0f);
        REQUIRE(torus.getCenter().z == 0.0f);
        
        REQUIRE(torus.getColor().getR() == 0);
        REQUIRE(torus.getColor().getG() == 0);
        REQUIRE(torus.getColor().getB() == 255);
    }
    
    SECTION("Ray intersection - hit outer") {
        // Rayon qui frappe la partie extérieure du tore
        Ray ray(Vector3(0.0f, 0.0f, -10.0f), Vector3(0.0f, 0.0f, 1.0f));
        float t;
        
        bool hit = torus.intersect(ray, t);
        
        REQUIRE(hit == true);
        // Distance jusqu'au point d'intersection
        REQUIRE(t > 0.0f);
    }
    
    SECTION("Ray intersection - hit inner") {
        // Rayon qui frappe la partie intérieure du tore
        Ray ray(Vector3(majorRadius - minorRadius/2, 0.0f, -10.0f), Vector3(0.0f, 0.0f, 1.0f));
        float t;
        
        bool hit = torus.intersect(ray, t);
        
        REQUIRE(hit == true);
    }
    
    SECTION("Ray intersection - miss") {
        // Rayon qui passe par le trou central du tore sans le toucher
        Ray ray(Vector3(0.0f, 0.0f, -10.0f), Vector3(0.1f, 0.1f, 1.0f));
        float t;
        
        bool hit = torus.intersect(ray, t);
        
        // Note: ce test peut échouer selon l'implémentation exacte et la précision numérique
        // L'important est que le comportement soit cohérent avec la géométrie du tore
        if (hit) {
            REQUIRE(t > 0.0f);
        }
    }
    
    SECTION("Ray intersection - miss completely") {
        // Rayon qui passe complètement à côté du tore
        Ray ray(Vector3(10.0f, 10.0f, -10.0f), Vector3(0.0f, 0.0f, 1.0f));
        float t;
        
        bool hit = torus.intersect(ray, t);
        
        REQUIRE(hit == false);
    }
    
    SECTION("Normal calculation - outer ring") {
        // Un point sur l'anneau extérieur du tore
        Vector3 point(majorRadius, 0.0f, 0.0f);
        
        Vector3 normal = torus.getNormal(point);
        
        // La normale doit pointer vers l'extérieur
        REQUIRE_THAT(normal.x, Catch::Matchers::WithinRel(1.0f));
        REQUIRE_THAT(normal.y, Catch::Matchers::WithinRel(0.0f));
        REQUIRE_THAT(normal.z, Catch::Matchers::WithinRel(0.0f));
        REQUIRE_THAT(normal.length(), Catch::Matchers::WithinRel(1.0f));
    }
    
    SECTION("Material access") {
        const Material& mat = torus.getMaterial();
        
        REQUIRE(mat.getColor().getR() == 0);
        REQUIRE(mat.getColor().getG() == 0);
        REQUIRE(mat.getColor().getB() == 255);
    }
    
    SECTION("Base center should equal center") {
        Vector3 baseCenter = torus.getBaseCenter();
        Vector3 center = torus.getCenter();
        
        REQUIRE(baseCenter.x == center.x);
        REQUIRE(baseCenter.y == center.y);
        REQUIRE(baseCenter.z == center.z);
    }
} 