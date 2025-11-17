#include <catch2/catch_all.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "Primitives/Sphere.hpp"
#include "Maths/Ray.hpp"
#include "Material/Material.hpp"

using namespace Raytracer;

TEST_CASE("Sphere operations", "[sphere]") {
    Vector3 center(0.0f, 0.0f, 0.0f);
    float radius = 1.0f;
    Material material;
    material.setColor(Color(255, 0, 0)); // Rouge
    
    Sphere sphere(center, radius, material);
    
    SECTION("Getters") {
        REQUIRE(sphere.getCenter().x == 0.0f);
        REQUIRE(sphere.getCenter().y == 0.0f);
        REQUIRE(sphere.getCenter().z == 0.0f);
        
        REQUIRE(sphere.getColor().getR() == 255);
        REQUIRE(sphere.getColor().getG() == 0);
        REQUIRE(sphere.getColor().getB() == 0);
    }
    
    SECTION("Ray intersection - hit") {
        Ray ray(Vector3(0.0f, 0.0f, -5.0f), Vector3(0.0f, 0.0f, 1.0f));
        float t;
        
        bool hit = sphere.intersect(ray, t);
        
        REQUIRE(hit == true);
        REQUIRE_THAT(t, Catch::Matchers::WithinRel(4.0f)); // Distance de l'origine du rayon à la sphère
    }
    
    SECTION("Ray intersection - miss") {
        Ray ray(Vector3(0.0f, 2.0f, -5.0f), Vector3(0.0f, 0.0f, 1.0f));
        float t;
        
        bool hit = sphere.intersect(ray, t);
        
        REQUIRE(hit == false);
    }
    
    SECTION("Normal calculation") {
        Vector3 point(0.0f, 1.0f, 0.0f);
        
        Vector3 normal = sphere.getNormal(point);
        
        REQUIRE(normal.x == 0.0f);
        REQUIRE(normal.y == 1.0f);
        REQUIRE(normal.z == 0.0f);
    }
    
    SECTION("Material access") {
        const Material& mat = sphere.getMaterial();
        
        REQUIRE(mat.getColor().getR() == 255);
        REQUIRE(mat.getColor().getG() == 0);
        REQUIRE(mat.getColor().getB() == 0);
    }
} 