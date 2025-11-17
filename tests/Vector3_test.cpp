#include <catch2/catch_all.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "Utils/Vector3.hpp"
#include <cmath>

using namespace Raytracer;

TEST_CASE("Vector3 basic operations", "[vector3]") {
    SECTION("Constructor and getters") {
        Vector3 v1;
        REQUIRE(v1.x == 0.0f);
        REQUIRE(v1.y == 0.0f);
        REQUIRE(v1.z == 0.0f);
        
        Vector3 v2(1.0f, 2.0f, 3.0f);
        REQUIRE(v2.x == 1.0f);
        REQUIRE(v2.y == 2.0f);
        REQUIRE(v2.z == 3.0f);
    }
    
    SECTION("Addition") {
        Vector3 v1(1.0f, 2.0f, 3.0f);
        Vector3 v2(4.0f, 5.0f, 6.0f);
        
        Vector3 sum = v1 + v2;
        REQUIRE(sum.x == 5.0f);
        REQUIRE(sum.y == 7.0f);
        REQUIRE(sum.z == 9.0f);
    }
    
    SECTION("Subtraction") {
        Vector3 v1(4.0f, 5.0f, 6.0f);
        Vector3 v2(1.0f, 2.0f, 3.0f);
        
        Vector3 diff = v1 - v2;
        REQUIRE(diff.x == 3.0f);
        REQUIRE(diff.y == 3.0f);
        REQUIRE(diff.z == 3.0f);
    }
    
    SECTION("Scalar multiplication") {
        Vector3 v(1.0f, 2.0f, 3.0f);
        
        Vector3 scaled = v * 2.0f;
        REQUIRE(scaled.x == 2.0f);
        REQUIRE(scaled.y == 4.0f);
        REQUIRE(scaled.z == 6.0f);
        
        Vector3 scaled2 = 2.0f * v;
        REQUIRE(scaled2.x == 2.0f);
        REQUIRE(scaled2.y == 4.0f);
        REQUIRE(scaled2.z == 6.0f);
    }
    
    SECTION("Negation") {
        Vector3 v(1.0f, 2.0f, 3.0f);
        
        Vector3 neg = -v;
        REQUIRE(neg.x == -1.0f);
        REQUIRE(neg.y == -2.0f);
        REQUIRE(neg.z == -3.0f);
    }
    
    SECTION("Dot product") {
        Vector3 v1(1.0f, 2.0f, 3.0f);
        Vector3 v2(4.0f, 5.0f, 6.0f);
        
        float dot = v1.dot(v2);
        REQUIRE(dot == 32.0f); // 1*4 + 2*5 + 3*6 = 4 + 10 + 18 = 32
    }
    
    SECTION("Cross product") {
        Vector3 v1(1.0f, 0.0f, 0.0f);
        Vector3 v2(0.0f, 1.0f, 0.0f);
        
        Vector3 cross = v1.cross(v2);
        REQUIRE(cross.x == 0.0f);
        REQUIRE(cross.y == 0.0f);
        REQUIRE(cross.z == 1.0f);
    }
    
    SECTION("Length") {
        Vector3 v(3.0f, 4.0f, 0.0f);
        
        REQUIRE(v.length() == 5.0f);
    }
    
    SECTION("Normalization") {
        Vector3 v(3.0f, 4.0f, 0.0f);
        
        Vector3 norm = v.normalized();
        REQUIRE_THAT(norm.x, Catch::Matchers::WithinRel(0.6f));
        REQUIRE_THAT(norm.y, Catch::Matchers::WithinRel(0.8f));
        REQUIRE_THAT(norm.z, Catch::Matchers::WithinRel(0.0f));
        REQUIRE_THAT(norm.length(), Catch::Matchers::WithinRel(1.0f));
    }
} 