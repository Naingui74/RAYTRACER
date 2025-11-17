// src/Renderer/Renderer.cpp

#include "Renderer/Renderer.hpp"
#include <algorithm>
#include <cmath>
#include "Lights/AmbientLight.hpp"
#include "Lights/CompositeLight.hpp"
#include "Primitives/CompositePrimitive.hpp"

constexpr float EPSILON = 0.001f;

/**
 * @brief Constructs a new Renderer
 * 
 * @param scene Reference to the scene to render
 * @param width Width of the output image in pixels
 * @param height Height of the output image in pixels
 */
Raytracer::Renderer::Renderer(const Scene& scene, int width, int height) : m_scene(scene), m_width(width), m_height(height) {
  m_image.resize(m_height, std::vector<Color>(m_width, Color(0, 0, 0)));
}

/**
 * @brief Computes the ray direction for a given pixel
 * 
 * This method converts pixel coordinates to a ray direction vector in world space,
 * taking into account the camera's field of view, aspect ratio, and orientation.
 * 
 * @param x X-coordinate of the pixel (0 to width-1)
 * @param y Y-coordinate of the pixel (0 to height-1)
 * @return Vector3 Normalized ray direction in world space
 */
Raytracer::Vector3 Raytracer::Renderer::computeRayDirection(int x, int y) const {
  float aspect = float(m_width) / m_height;
  float fovScale = std::tan(m_scene.getCamera().getFieldOfView() * 0.5f * M_PI / 180.0f);
  float px = (2.0f * (x + 0.5f) / m_width - 1.0f) * aspect * fovScale;
  float py = (1.0f - 2.0f * (y + 0.5f) / m_height) * fovScale;
  Vector3 dir(px, py, 1.0f);
  dir = dir.normalized();

  auto rot = m_scene.getCamera().getRotation();
  float pitch = rot.x * M_PI / 180.0f;
  float yaw = rot.y * M_PI / 180.0f;
  float roll = rot.z * M_PI / 180.0f;

  dir = rotateX(dir, pitch);
  dir = rotateY(dir, yaw);
  dir = rotateZ(dir, roll);
  return dir.normalized();
}

/**
 * @brief Traces a ray through the scene
 * 
 * Determines what color is seen when looking in a particular direction (ray)
 * by finding the first object the ray hits and calculating its shaded color.
 * This method can call itself recursively to handle reflections.
 * 
 * @param ray The ray to trace
 * @param depth Current recursion depth (to limit maximum reflections)
 * @return Color The computed color for this ray
 */
Raytracer::Color Raytracer::Renderer::traceRay(const Ray& ray, int depth) const {
  if (depth > 3)
    return {0, 0, 0};
  
  float closestT = std::numeric_limits<float>::infinity();
  std::shared_ptr<IPrimitive> hitPrim = nullptr;
  
  auto rootComposite = m_scene.getRootCompositePrimitive();
  if (rootComposite && rootComposite->intersect(ray, closestT)) {
    Vector3 point = ray.at(closestT);
    Vector3 normal = rootComposite->getNormal(point);
    const Material& material = rootComposite->getMaterial();
    Color base = material.getColor();
    Color refl = getReflectionColor(point, normal, ray, depth);
    return shadeHit(point, normal, base, refl, material);
  }
  
  for (const auto& prim : m_scene.getPrimitives()) {
    float t;
    if (prim->intersect(ray, t) && t > EPSILON && t < closestT) {
      closestT = t;
      hitPrim = prim;
    }
  }
  
  if (hitPrim) {
    Vector3 point = ray.at(closestT);
    Vector3 normal = hitPrim->getNormal(point);
    const Material& material = hitPrim->getMaterial();
    Color base = material.getColor();
    Color refl = getReflectionColor(point, normal, ray, depth);
    return shadeHit(point, normal, base, refl, material);
  }
  
  // Couleur du ciel (pas d'intersection)
  float t = 0.5f * (ray.getDirection().y + 1.0f);
  return Color(int(255 * (1 - t)), int(255 * t), 255);
}

/**
 * @brief Computes reflection color at a hit point
 * 
 * Creates a reflection ray and traces it to determine what color is reflected
 * at the given point.
 * 
 * @param hitPoint The point of intersection
 * @param normal Surface normal at the hit point
 * @param ray The incoming ray that hit the surface
 * @param depth Current recursion depth
 * @return Color The reflected color
 */
Raytracer::Color Raytracer::Renderer::getReflectionColor(const Vector3& hitPoint, const Vector3& normal, const Ray& ray, int depth) const {
  Vector3 reflectDir = ray.getDirection() - normal * (2.0f * ray.getDirection().dot(normal));
  Ray reflectRay(hitPoint + normal * EPSILON, reflectDir.normalized());
  return traceRay(reflectRay, depth + 1);
}

/**
 * @brief Shades a hit point using the Blinn-Phong lighting model
 * 
 * Computes the color at a point based on the material properties, light sources,
 * shadows, and reflections.
 * 
 * @param hitPoint The point of intersection
 * @param normal Surface normal at the hit point
 * @param baseColor The base color of the material
 * @param reflectionColor The color from reflections
 * @param material The material properties of the hit surface
 * @return Color The final shaded color
 */
Raytracer::Color Raytracer::Renderer::shadeHit(const Vector3& hitPoint, const Vector3& normal, const Color& baseColor, const Color& reflectionColor, const Material& material) const {
  float ambientStrength = 0;

  // Recherche de la lumière ambiante
  for (auto light : m_scene.getLights()) {
    auto ambientLight = dynamic_cast<Raytracer::AmbientLight*>(light.get());
    if (ambientLight) {
      ambientStrength = ambientLight->getIntensity();
      break;
    }
  }

  float r = baseColor.getR() * ambientStrength;
  float g = baseColor.getG() * ambientStrength;
  float b = baseColor.getB() * ambientStrength;
  Vector3 viewDir = (m_scene.getCamera().getPosition() - hitPoint).normalized();


  for (const auto& light : m_scene.getLights()) {
    // Ignorer les lumières ambiantes (déjà traitées)
    if (dynamic_cast<Raytracer::AmbientLight*>(light.get())) {
      continue;
    }
    
    // Ignorer les composites (nous traitons les lumières directement)
    if (dynamic_cast<Raytracer::CompositeLight*>(light.get())) {
      continue;
    }
    
    Vector3 lightDir = light->getDirectionFrom(hitPoint).normalized();
    Ray shadowRay(hitPoint + normal * EPSILON, lightDir);
    bool inShadow = false;
    
    // Test d'intersection optimisé avec le composite racine
    auto rootPrimitives = m_scene.getRootCompositePrimitive();
    float shadowT;
    if (rootPrimitives && rootPrimitives->intersect(shadowRay, shadowT) && shadowT > EPSILON) {
      inShadow = true;
    }
    
    if (inShadow)
      continue;
      
    float intensity = light->getIntensity();
    float diffuseFactor = 0.7f;
    float specularFactor = 0.1f;
    
    // Diffuse
    float diff = std::max(0.f, normal.dot(lightDir)) * diffuseFactor * intensity;

    // Specular (Blinn-Phong)
    Vector3 halfway = (lightDir + viewDir).normalized();
    float shininess = 64.0f;
    if (material.getType() == Material::METAL) {
      shininess = 128.0f - material.getRoughness() * 120.0f;
      specularFactor = 0.2f;
    }
    float spec = std::pow(std::max(0.f, normal.dot(halfway)), shininess) * intensity;
    
    r += baseColor.getR() * diff + 255.f * spec * specularFactor;
    g += baseColor.getG() * diff + 255.f * spec * specularFactor;
    b += baseColor.getB() * diff + 255.f * spec * specularFactor;
  }
  
  // Réflexions
  float reflectivity = material.getReflectivity();
  if (material.getType() == Material::METAL) {
    reflectivity = 0.8f - material.getRoughness() * 0.6f;
  }
  
  r = r * (1.0f - reflectivity) + reflectionColor.getR() * reflectivity;
  g = g * (1.0f - reflectivity) + reflectionColor.getG() * reflectivity;
  b = b * (1.0f - reflectivity) + reflectionColor.getB() * reflectivity;
  
  // Ajout de l'émission lumineuse pour les matériaux émissifs
  if (material.getType() == Material::EMISSIVE && material.getEmissiveIntensity() > 0) {
    float emission = material.getEmissiveIntensity();
    r += baseColor.getR() * emission;
    g += baseColor.getG() * emission;
    b += baseColor.getB() * emission;
  }

  return Color(int(std::clamp(r, 0.f, 255.f)), int(std::clamp(g, 0.f, 255.f)), int(std::clamp(b, 0.f, 255.f)));
}

/**
 * @brief Executes the main rendering process
 * 
 * Iterates over each pixel of the output image, computes the ray direction,
 * traces the ray through the scene, and stores the resulting color.
 */
void Raytracer::Renderer::render() {
  for (int y = 0; y < m_height; ++y) {
    for (int x = 0; x < m_width; ++x) {
      Vector3 dir = computeRayDirection(x, y);
      Ray ray(m_scene.getCamera().getPosition(), dir);
      m_image[y][x] = traceRay(ray, 1);
    }
  }
}

/**
 * @brief Gets the rendered image
 * 
 * @return const std::vector<std::vector<Color>>& 2D array of computed pixel colors
 */
const std::vector<std::vector<Raytracer::Color>>& Raytracer::Renderer::getImage() const {
  return m_image;
}

/**
 * @brief Sets a pixel color in the image buffer
 * 
 * @param x X-coordinate of the pixel
 * @param y Y-coordinate of the pixel
 * @param color Color to set
 */
void Raytracer::Renderer::setPixel(int x, int y, const Color& color) {
  if ((unsigned)x < m_width && (unsigned)y < m_height)
    m_image[y][x] = color;
}

/**
 * @brief Rotates a vector around the X axis
 * 
 * @param v Vector to rotate
 * @param a Angle in radians
 * @return Vector3 Rotated vector
 */
Raytracer::Vector3 Raytracer::Renderer::rotateX(const Vector3& v, float a) const {
  return {v.x, v.y * std::cos(a) - v.z * std::sin(a), v.y * std::sin(a) + v.z * std::cos(a)};
}

/**
 * @brief Rotates a vector around the Y axis
 * 
 * @param v Vector to rotate
 * @param a Angle in radians
 * @return Vector3 Rotated vector
 */
Raytracer::Vector3 Raytracer::Renderer::rotateY(const Vector3& v, float a) const {
  return {v.x * std::cos(a) + v.z * std::sin(a), v.y, -v.x * std::sin(a) + v.z * std::cos(a)};
}

/**
 * @brief Rotates a vector around the Z axis
 * 
 * @param v Vector to rotate
 * @param a Angle in radians
 * @return Vector3 Rotated vector
 */
Raytracer::Vector3 Raytracer::Renderer::rotateZ(const Vector3& v, float a) const {
  return {v.x * std::cos(a) - v.y * std::sin(a), v.x * std::sin(a) + v.y * std::cos(a), v.z};
}
