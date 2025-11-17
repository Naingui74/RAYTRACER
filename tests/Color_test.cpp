#include <catch2/catch_all.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "Utils/Color.hpp"

using namespace Raytracer;

TEST_CASE("Color operations", "[color]") {
    SECTION("Default constructor") {
        Color color;
        
        REQUIRE(color.getR() == 0);
        REQUIRE(color.getG() == 0);
        REQUIRE(color.getB() == 0);
    }
    
    SECTION("RGB constructor") {
        Color color(100, 150, 200);
        
        REQUIRE(color.getR() == 100);
        REQUIRE(color.getG() == 150);
        REQUIRE(color.getB() == 200);
    }
    
    SECTION("Copy constructor") {
        Color original(100, 150, 200);
        Color copy(original);
        
        REQUIRE(copy.getR() == 100);
        REQUIRE(copy.getG() == 150);
        REQUIRE(copy.getB() == 200);
    }
    
    SECTION("Setters") {
        Color color;
        
        color.setR(50);
        color.setG(100);
        color.setB(150);
        
        REQUIRE(color.getR() == 50);
        REQUIRE(color.getG() == 100);
        REQUIRE(color.getB() == 150);
    }
    
    SECTION("Addition") {
        Color a(100, 150, 200);
        Color b(50, 75, 100);
        
        Color result = a + b;
        
        REQUIRE(result.getR() == 150);
        REQUIRE(result.getG() == 225);
        REQUIRE(result.getB() == 255); // Clamp à 255
    }
    
    SECTION("Subtraction") {
        Color a(100, 150, 200);
        Color b(50, 75, 100);
        
        Color result = a - b;
        
        REQUIRE(result.getR() == 50);
        REQUIRE(result.getG() == 75);
        REQUIRE(result.getB() == 100);
    }
    
    SECTION("Multiplication by scalar") {
        Color a(100, 150, 200);
        float scalar = 0.5f;
        
        Color result = a * scalar;
        
        REQUIRE(result.getR() == 50);
        REQUIRE(result.getG() == 75);
        REQUIRE(result.getB() == 100);
    }
    
    SECTION("Multiplication by Color") {
        Color a(100, 150, 200);
        Color b(100, 100, 100);
        
        // Multiplier par 100/255 = ~0.392
        Color result = a * b;
        
        REQUIRE(result.getR() == 39);
        REQUIRE(result.getG() == 59);
        REQUIRE(result.getB() == 78);
    }
    
    SECTION("Clamping values above 255") {
        Color a(200, 200, 200);
        Color b(100, 100, 100);
        
        Color result = a + b;
        
        REQUIRE(result.getR() == 255);
        REQUIRE(result.getG() == 255);
        REQUIRE(result.getB() == 255);
    }
    
    SECTION("Clamping values below 0") {
        Color a(50, 50, 50);
        Color b(100, 100, 100);
        
        Color result = a - b;
        
        REQUIRE(result.getR() == 0);
        REQUIRE(result.getG() == 0);
        REQUIRE(result.getB() == 0);
    }
    
    SECTION("Assignment operator") {
        Color a(100, 150, 200);
        Color b;
        
        b = a;
        
        REQUIRE(b.getR() == 100);
        REQUIRE(b.getG() == 150);
        REQUIRE(b.getB() == 200);
    }
} 