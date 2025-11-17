#include <catch2/catch_all.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "Maths/Ray.hpp"

using namespace Raytracer;

TEST_CASE("Ray operations", "[ray]") {
    SECTION("Constructor and getters") {
        Vector3 origin(1.0f, 2.0f, 3.0f);
        Vector3 direction(0.0f, 1.0f, 0.0f);
        
        Ray ray(origin, direction);
        
        REQUIRE(ray.getOrigin().x == 1.0f);
        REQUIRE(ray.getOrigin().y == 2.0f);
        REQUIRE(ray.getOrigin().z == 3.0f);
        
        REQUIRE(ray.getDirection().x == 0.0f);
        REQUIRE(ray.getDirection().y == 1.0f);
        REQUIRE(ray.getDirection().z == 0.0f);
    }
    
    SECTION("Direction normalization") {
        Vector3 origin(0.0f, 0.0f, 0.0f);
        Vector3 direction(3.0f, 4.0f, 0.0f);
        
        Ray ray(origin, direction);
        
        // Vérifier que la direction est normalisée
        REQUIRE(ray.getDirection().x > 0.59f);
        REQUIRE(ray.getDirection().x < 0.61f);
        REQUIRE(ray.getDirection().y > 0.79f);
        REQUIRE(ray.getDirection().y < 0.81f);
        REQUIRE(ray.getDirection().z >= -0.01f);
        REQUIRE(ray.getDirection().z <= 0.01f);
        REQUIRE(ray.getDirection().length() > 0.99f);
        REQUIRE(ray.getDirection().length() < 1.01f);
    }
    
    SECTION("Point at parameter") {
        Vector3 origin(1.0f, 2.0f, 3.0f);
        Vector3 direction(1.0f, 0.0f, 0.0f);
        
        Ray ray(origin, direction);
        
        Vector3 point = ray.at(2.0f);
        REQUIRE(point.x == 3.0f); // origin.x + t * direction.x = 1 + 2 * 1 = 3
        REQUIRE(point.y == 2.0f); // origin.y + t * direction.y = 2 + 2 * 0 = 2
        REQUIRE(point.z == 3.0f); // origin.z + t * direction.z = 3 + 2 * 0 = 3
    }
} 