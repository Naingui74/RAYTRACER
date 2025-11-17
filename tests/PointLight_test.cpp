#include <catch2/catch_all.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "Lights/PointLight.hpp"
#include "Utils/Vector3.hpp"
#include "Utils/Color.hpp"

using namespace Raytracer;

TEST_CASE("PointLight operations", "[point_light]") {
    Vector3 position(5.0f, 10.0f, 15.0f);
    float intensity = 1.0f;
    
    PointLight light(position, intensity);
    
    SECTION("Getters") {
        REQUIRE(light.getPosition().x == 5.0f);
        REQUIRE(light.getPosition().y == 10.0f);
        REQUIRE(light.getPosition().z == 15.0f);
        
        REQUIRE(light.getIntensity() == 1.0f);
    }
    
    SECTION("GetDirectionFrom a point") {
        Vector3 point(5.0f, 5.0f, 15.0f);
        
        Vector3 lightDir = light.getDirectionFrom(point);
        
        // La direction devrait pointer du point vers la position de la lumière
        // Dans ce cas, la direction est (0, 1, 0) normalisée
        REQUIRE_THAT(lightDir.x, Catch::Matchers::WithinRel(0.0f));
        REQUIRE_THAT(lightDir.y, Catch::Matchers::WithinRel(1.0f));
        REQUIRE_THAT(lightDir.z, Catch::Matchers::WithinRel(0.0f));
        REQUIRE_THAT(lightDir.length(), Catch::Matchers::WithinRel(1.0f));
    }
    
    SECTION("GetDirectionFrom another point") {
        Vector3 point(0.0f, 10.0f, 15.0f);
        
        Vector3 lightDir = light.getDirectionFrom(point);
        
        // La direction devrait pointer du point vers la position de la lumière
        // Dans ce cas, la direction est (1, 0, 0) normalisée
        REQUIRE_THAT(lightDir.x, Catch::Matchers::WithinRel(1.0f));
        REQUIRE_THAT(lightDir.y, Catch::Matchers::WithinRel(0.0f));
        REQUIRE_THAT(lightDir.z, Catch::Matchers::WithinRel(0.0f));
    }
    
    SECTION("With different intensity") {
        PointLight dimLight(position, 0.5f);
        
        REQUIRE(dimLight.getIntensity() == 0.5f);
    }
} 