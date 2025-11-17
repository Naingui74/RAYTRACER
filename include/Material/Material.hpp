#pragma once

#include "Utils/Color.hpp"

namespace Raytracer {
  /**
   * @class Material
   * @brief Represents the material properties of a surface
   * 
   * This class encapsulates all properties that define how a surface interacts with light,
   * including its color, reflectivity, transparency, and other physical properties.
   * It supports different material types like lambertian, metal, and dielectric.
   */
  class Material {
    public:
      /**
       * @brief Enumeration of supported material types
       */
      enum Type {
        FLAT_COLOR,   ///< Simple flat color with no lighting effects
        LAMBERTIAN,   ///< Diffuse material with matte appearance
        METAL,        ///< Reflective metal material
        DIELECTRIC,   ///< Transparent material like glass
        EMISSIVE      ///< Self-illuminating material that acts as a light source
      };

      /**
       * @brief Default constructor
       * 
       * Creates a material with default properties (lambertian white)
       */
      Material() = default;
      
      /**
       * @brief Constructor with specified material type
       * 
       * @param type The type of material to create
       */
      explicit Material(Type type) : _type(type) {
      }
      
      /**
       * @brief Constructor with material type and color
       * 
       * @param type The type of material to create
       * @param color The color of the material
       */
      Material(Type type, const Color& color) : _type(type), _color(color) {
      }
      
      /**
       * @brief Virtual destructor
       */
      virtual ~Material() = default;

      /**
       * @brief Sets the material type
       * 
       * @param type The new material type
       */
      void setType(Type type) {
        _type = type;
      }
      
      /**
       * @brief Sets the material roughness
       * 
       * Controls how smooth or rough a surface appears. Higher values create
       * more diffuse reflections, while lower values create sharper reflections.
       * 
       * @param roughness Value between 0.0 (perfectly smooth) and 1.0 (very rough)
       */
      void setRoughness(double roughness) {
        _roughness = roughness;
      }
      
      /**
       * @brief Sets the metalness factor
       * 
       * Controls how metallic the material appears. Higher values make the material
       * more like metal, affecting how it reflects light.
       * 
       * @param metalness Value between 0.0 (non-metal) and 1.0 (pure metal)
       */
      void setMetalness(double metalness) {
        _metalness = metalness;
      }
      
      /**
       * @brief Sets the reflectivity factor
       * 
       * Controls how much light the material reflects.
       * 
       * @param reflectivity Value between 0.0 (no reflection) and 1.0 (mirror-like)
       */
      void setReflectivity(double reflectivity) {
        _reflectivity = reflectivity;
      }
      
      /**
       * @brief Sets the transparency factor
       * 
       * Controls how transparent the material is.
       * 
       * @param transparency Value between 0.0 (opaque) and 1.0 (fully transparent)
       */
      void setTransparency(double transparency) {
        _transparency = transparency;
      }
      
      /**
       * @brief Sets the refractive index
       * 
       * Controls how light bends when passing through the material.
       * 
       * @param refractiveIndex Typical values: air (1.0), water (1.33), glass (1.5)
       */
      void setRefractiveIndex(double refractiveIndex) {
        _refractiveIndex = refractiveIndex;
      }
      
      /**
       * @brief Sets the emissive intensity
       * 
       * Controls how much light the material emits, for emissive materials.
       * 
       * @param intensity Value >= 0.0, where higher values mean brighter emission
       */
      void setEmissiveIntensity(double intensity) {
        _emissiveIntensity = intensity;
      }
      
      /**
       * @brief Sets the material color
       * 
       * @param color The new color of the material
       */
      void setColor(const Color& color) {
        _color = color;
      }

      /**
       * @brief Gets the material type
       * 
       * @return The material type
       */
      Type getType() const {
        return _type;
      }
      
      /**
       * @brief Gets the material roughness
       * 
       * @return Value between 0.0 (smooth) and 1.0 (rough)
       */
      double getRoughness() const {
        return _roughness;
      }
      
      /**
       * @brief Gets the material metalness
       * 
       * @return Value between 0.0 (non-metal) and 1.0 (metal)
       */
      double getMetalness() const {
        return _metalness;
      }
      
      /**
       * @brief Gets the material reflectivity
       * 
       * @return Value between 0.0 (no reflection) and 1.0 (mirror)
       */
      double getReflectivity() const {
        return _reflectivity;
      }
      
      /**
       * @brief Gets the material transparency
       * 
       * @return Value between 0.0 (opaque) and 1.0 (transparent)
       */
      double getTransparency() const {
        return _transparency;
      }
      
      /**
       * @brief Gets the material refractive index
       * 
       * @return The refractive index value
       */
      double getRefractiveIndex() const {
        return _refractiveIndex;
      }
      
      /**
       * @brief Gets the material emissive intensity
       * 
       * @return The emissive intensity value
       */
      double getEmissiveIntensity() const {
        return _emissiveIntensity;
      }
      
      /**
       * @brief Gets the material color
       * 
       * @return Reference to the material color
       */
      const Color& getColor() const {
        return _color;
      }

    private:
      Type _type = LAMBERTIAN;           ///< Material type
      double _roughness = 0.5;            ///< Surface roughness
      double _metalness = 0.0;            ///< Metallic factor
      double _reflectivity = 0.0;         ///< Reflection factor
      double _transparency = 0.0;         ///< Transparency factor
      double _refractiveIndex = 1.0;      ///< Refractive index for transparent materials
      double _emissiveIntensity = 0.0;    ///< Light emission intensity
      Color _color = Color(255, 255, 255); ///< Default white color
  };
}  // namespace Raytracer
