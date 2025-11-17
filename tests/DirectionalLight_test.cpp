#include <catch2/catch_all.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "Lights/DirectionalLight.hpp"
#include "Utils/Vector3.hpp"

using namespace Raytracer;

TEST_CASE("DirectionalLight operations", "[directional_light]") {
    Vector3 position(0.0f, 0.0f, 0.0f);
    Vector3 direction(-1.0f, -1.0f, 0.0f);
    float intensity = 1.0f;
    
    DirectionalLight light(position, direction, intensity);
    
    SECTION("Get direction from point") {
        Vector3 point(10.0f, 20.0f, 30.0f);
        
        Vector3 lightDir = light.getDirectionFrom(point);
        
        // La direction doit être normalisée
        REQUIRE_THAT(lightDir.length(), Catch::Matchers::WithinRel(1.0f));
        
        // Pour une lumière directionnelle, la direction de la lumière est constante
        // indépendamment du point d'évaluation
        // Les composantes devraient être -1/sqrt(2), -1/sqrt(2), 0 normalisées
        float expectedValue = -1.0f / std::sqrt(2.0f);
        REQUIRE_THAT(lightDir.x, Catch::Matchers::WithinRel(expectedValue));
        REQUIRE_THAT(lightDir.y, Catch::Matchers::WithinRel(expectedValue));
        REQUIRE_THAT(lightDir.z, Catch::Matchers::WithinRel(0.0f));
    }
    
    SECTION("Get intensity") {
        REQUIRE(light.getIntensity() == 1.0f);
    }
    
    SECTION("With different intensity") {
        DirectionalLight dimLight(position, direction, 0.5f);
        
        REQUIRE(dimLight.getIntensity() == 0.5f);
    }
} 