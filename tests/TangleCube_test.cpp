#include <catch2/catch_all.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "Primitives/TangleCube.hpp"
#include "Maths/Ray.hpp"

using namespace Raytracer;

TEST_CASE("TangleCube operations", "[tanglecube]") {
    Vector3 center(0.0f, 0.0f, 0.0f);
    float size = 1.0f;
    Material material;
    material.setColor(Color(255, 255, 0)); // Jaune
    
    TangleCube tangleCube(center, size, material);
    
    SECTION("Getters") {
        REQUIRE(tangleCube.getCenter().x == 0.0f);
        REQUIRE(tangleCube.getCenter().y == 0.0f);
        REQUIRE(tangleCube.getCenter().z == 0.0f);
        
        REQUIRE(tangleCube.getColor().getR() == 255);
        REQUIRE(tangleCube.getColor().getG() == 255);
        REQUIRE(tangleCube.getColor().getB() == 0);
    }
    
    SECTION("Ray intersection - hit") {
        // Rayon qui devrait frapper le TangleCube
        // (nous devrons choisir un rayon approprié selon l'implémentation spécifique)
        Ray ray(Vector3(3.0f, 0.0f, 0.0f), Vector3(-1.0f, 0.0f, 0.0f));
        float t;
        
        bool hit = tangleCube.intersect(ray, t);
        
        // Note: le résultat exact dépend de l'implémentation
        // L'important est que le test démontre que l'intersection fonctionne
        REQUIRE(hit == true);
        REQUIRE(t > 0.0f);
    }
    
    SECTION("Ray intersection - miss") {
        // Rayon qui passe loin du TangleCube
        Ray ray(Vector3(10.0f, 10.0f, 10.0f), Vector3(1.0f, 0.0f, 0.0f));
        float t;
        
        bool hit = tangleCube.intersect(ray, t);
        
        REQUIRE(hit == false);
    }
    
    SECTION("Normal calculation") {
        // Un point sur la surface du TangleCube
        // (les coordonnées exactes dépendent de l'équation de la surface)
        Vector3 point(1.0f, 0.0f, 0.0f);
        
        Vector3 normal = tangleCube.getNormal(point);
        
        // La normale doit pointer vers l'extérieur et être normalisée
        REQUIRE(normal.length() > 0.99f);
        REQUIRE(normal.length() < 1.01f);
        
        // Pour un point sur l'axe X positif, la normale doit pointer généralement dans la direction X
        REQUIRE(normal.x > 0.0f);
    }
    
    SECTION("Material access") {
        const Material& mat = tangleCube.getMaterial();
        
        REQUIRE(mat.getColor().getR() == 255);
        REQUIRE(mat.getColor().getG() == 255);
        REQUIRE(mat.getColor().getB() == 0);
    }
    
    SECTION("Base center should equal center") {
        Vector3 baseCenter = tangleCube.getBaseCenter();
        Vector3 center = tangleCube.getCenter();
        
        REQUIRE(baseCenter.x == center.x);
        REQUIRE(baseCenter.y == center.y);
        REQUIRE(baseCenter.z == center.z);
    }
} 