#include <catch2/catch_all.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "Material/Material.hpp"

using namespace Raytracer;

TEST_CASE("Material operations", "[material]") {
    SECTION("Default constructor") {
        Material material;
        
        REQUIRE(material.getType() == Material::LAMBERTIAN);
        REQUIRE_THAT(material.getRoughness(), Catch::Matchers::WithinRel(0.5));
        REQUIRE_THAT(material.getMetalness(), Catch::Matchers::WithinRel(0.0));
        REQUIRE_THAT(material.getReflectivity(), Catch::Matchers::WithinRel(0.0));
        REQUIRE_THAT(material.getTransparency(), Catch::Matchers::WithinRel(0.0));
        REQUIRE_THAT(material.getRefractiveIndex(), Catch::Matchers::WithinRel(1.0));
        REQUIRE_THAT(material.getEmissiveIntensity(), Catch::Matchers::WithinRel(0.0));
        
        REQUIRE(material.getColor().getR() == 255);
        REQUIRE(material.getColor().getG() == 255);
        REQUIRE(material.getColor().getB() == 255);
    }
    
    SECTION("Constructor with type") {
        Material material(Material::METAL);
        
        REQUIRE(material.getType() == Material::METAL);
    }
    
    SECTION("Constructor with type and color") {
        Color color(100, 150, 200);
        Material material(Material::DIELECTRIC, color);
        
        REQUIRE(material.getType() == Material::DIELECTRIC);
        REQUIRE(material.getColor().getR() == 100);
        REQUIRE(material.getColor().getG() == 150);
        REQUIRE(material.getColor().getB() == 200);
    }
    
    SECTION("Setters and getters") {
        Material material;
        
        material.setType(Material::EMISSIVE);
        REQUIRE(material.getType() == Material::EMISSIVE);
        
        material.setRoughness(0.8);
        REQUIRE_THAT(material.getRoughness(), Catch::Matchers::WithinRel(0.8));
        
        material.setMetalness(0.6);
        REQUIRE_THAT(material.getMetalness(), Catch::Matchers::WithinRel(0.6));
        
        material.setReflectivity(0.9);
        REQUIRE_THAT(material.getReflectivity(), Catch::Matchers::WithinRel(0.9));
        
        material.setTransparency(0.5);
        REQUIRE_THAT(material.getTransparency(), Catch::Matchers::WithinRel(0.5));
        
        material.setRefractiveIndex(1.5);
        REQUIRE_THAT(material.getRefractiveIndex(), Catch::Matchers::WithinRel(1.5));
        
        material.setEmissiveIntensity(2.0);
        REQUIRE_THAT(material.getEmissiveIntensity(), Catch::Matchers::WithinRel(2.0));
        
        Color color(50, 100, 150);
        material.setColor(color);
        REQUIRE(material.getColor().getR() == 50);
        REQUIRE(material.getColor().getG() == 100);
        REQUIRE(material.getColor().getB() == 150);
    }
} 