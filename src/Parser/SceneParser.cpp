/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** SceneParser
*/

#include "Parser/SceneParser.hpp"
#include <limits>
#include <string>
#include "Core/Camera.hpp"
#include "Factory/LightFactory.hpp"
#include "Factory/PrimitiveFactory.hpp"
#include "GlobalException.hpp"
#include "Parser/ObjParser.hpp"
#include "Primitives/Triangle.hpp"
#include "Utils/Vector3.hpp"

Raytracer::SceneParser::SceneParser(const std::string &filename, Scene &scene) : m_filename(filename), m_cfg(), m_scene(scene) {
}

bool Raytracer::SceneParser::parse() {
    try {
        m_cfg.readFile(m_filename.c_str());
        const libconfig::Setting &root = m_cfg.getRoot();
        if (!parseCamera(root))
            throw GlobalException("[SceneParser] Failed to parse camera.");
        if (!parseLights(root))
            throw GlobalException("[SceneParser] Failed to parse lights.");
        if (!parsePrimitives(root))
            throw GlobalException("[SceneParser] Failed to parse primitives.");
        return true;
    } catch (const libconfig::ParseException &e) {
        throw GlobalException("[SceneParser] Parse error: " + std::string(e.getError()) + " at line " + std::to_string(e.getLine()));
    } catch (const libconfig::SettingException &e) {
        throw GlobalException("[SceneParser] Setting error: " + std::string(e.what()));
    }
    return false;
}

bool Raytracer::SceneParser::parseCamera(const libconfig::Setting &root) {
    try {
        const libconfig::Setting &cam = root.lookup("camera");
        Vector3 position = parseVector3(cam.lookup("position"));
        Vector3 rotation = parseVector3(cam.lookup("rotation"));
        int width = 800;
        int height = 600;
        float fov = 70.0f;
        const libconfig::Setting &res = cam.lookup("resolution");
        if (!res.lookupValue("width", width) || !res.lookupValue("height", height))
            throw GlobalException("Invalid resolution values.");
        if (!cam.lookupValue("fieldOfView", fov))
            throw GlobalException("'fieldOfView' missing or invalid.");
        Camera camera;
        camera.setPosition(position);
        camera.setRotation(rotation);
        camera.setResolution(width, height);
        camera.setFieldOfView(fov);
        m_scene.setCamera(camera);
        return true;
    } catch (const libconfig::SettingException &e) {
        throw GlobalException("[SceneParser] Error parsing camera: " + std::string(e.what()));
        return false;
    }
}

bool Raytracer::SceneParser::parseLights(const libconfig::Setting &root) {
    try {
        if (!root.exists("lights"))
            return true;
        const libconfig::Setting &lights = root.lookup("lights");

    if (lights.exists("ambient")) {
      float ambient = 0.0f;
      if (lights.lookupValue("ambient", ambient)) {
        if (ambient < 0.0f || ambient > 1.0f)
          throw GlobalException("Ambient light value must be between 0 and 1.");
        m_scene.addLight(LightFactory::createAmbientLight(Vector3(0, 0, 0), ambient));
      } else {
        throw GlobalException("'ambient' light value missing or invalid.");
      }
    }

        if (lights.exists("point")) {
            const libconfig::Setting &points = lights.lookup("point");
            for (int i = 0; i < points.getLength(); ++i) {
                Vector3 pos = parseVector3(points[i]);
                m_scene.addLight(LightFactory::createPointLight(pos));
            }
        }
        if (lights.exists("directional")) {
            const libconfig::Setting &directionals = lights.lookup("directional");
            for (int i = 0; i < directionals.getLength(); ++i) {
                Vector3 pos = parseVector3(directionals[i].lookup("position"));
                Vector3 dir = parseVector3(directionals[i].lookup("direction"));
                m_scene.addLight(LightFactory::createDirectionalLight(pos, dir));
            }
        }
        return true;
    } catch (const libconfig::SettingException &e) {
        throw GlobalException("[SceneParser] Error parsing lights: " + std::string(e.what()));
        return false;
    }
}

bool Raytracer::SceneParser::parsePrimitives(const libconfig::Setting &root) {
  try {
    if (!root.exists("primitives"))
      return true;
    const auto &prims = root.lookup("primitives");
    if (prims.exists("spheres")) {
      const auto &spheres = prims.lookup("spheres");
      for (int i = 0; i < spheres.getLength(); ++i) {
        const auto &s = spheres[i];
        Vector3 center;
        {
          int xi, yi, zi;
          float xf, yf, zf;
          if (s.lookupValue("x", xi) && s.lookupValue("y", yi) && s.lookupValue("z", zi)) {
            center = Vector3{(float)xi, (float)yi, (float)zi};
          } else if (s.lookupValue("x", xf) && s.lookupValue("y", yf) && s.lookupValue("z", zf)) {
            center = Vector3{xf, yf, zf};
          } else {
            throw GlobalException("Sphere #" + std::to_string(i) + " : position (x,y,z) invalide ou manquante");
          }
        }
        float radius = 1.0f;
        if (s.exists("r")) {
          int ri;
          float rf;
          if (s.lookupValue("r", ri))
            radius = (float)ri;
          else if (s.lookupValue("r", rf))
            radius = rf;
          else
            throw GlobalException("Sphere #" + std::to_string(i) + " : 'r' existe mais n'est ni int ni float");
        } else {
          throw GlobalException("Sphere #" + std::to_string(i) + " : champ 'r' manquant");
        }
        int cr = 255, cg = 255, cb = 255;
        if (s.exists("color")) {
          const auto &col = s.lookup("color");
          col.lookupValue("r", cr);
          col.lookupValue("g", cg);
          col.lookupValue("b", cb);
        }
        m_scene.addPrimitive(PrimitiveFactory::createSphere(center, radius, parseMaterial(s, Color(cr, cg, cb))));
      }
    }
    if (prims.exists("planes")) {
      const auto &planes = prims.lookup("planes");
      for (int i = 0; i < planes.getLength(); ++i) {
        const auto &p = planes[i];
        std::string axis;
        if (!p.lookupValue("axis", axis))
          throw GlobalException("Plan #" + std::to_string(i) + " : champ 'axis' manquant");
        char a = axis.empty() ? 'Y' : axis[0];
        float pos = 0.0f;
        {
          int pi;
          if (p.lookupValue("position", pi))
            pos = (float)pi;
          else if (p.lookupValue("position", pos)) { /* lu */
          } else
            throw GlobalException("Plan #" + std::to_string(i) + " : champ 'position' manquant");
        }
        int pr = 255, pg = 255, pb = 255;
        if (p.exists("color")) {
          const auto &col = p.lookup("color");
          col.lookupValue("r", pr);
          col.lookupValue("g", pg);
          col.lookupValue("b", pb);
        }
        Vector3 normal;
        switch (a) {
          case 'X':
          case 'x':
            normal = {1, 0, 0};
            break;
          case 'Y':
          case 'y':
            normal = {0, 1, 0};
            break;
          case 'Z':
          case 'z':
            normal = {0, 0, 1};
            break;
          default:
            throw GlobalException("Plan #" + std::to_string(i) + " : axe invalide '" + axis + "'");
        }
        m_scene.addPrimitive(PrimitiveFactory::createPlane(normal, pos, parseMaterial(p, Color(pr, pg, pb))));
      }
    }
    if (prims.exists("tanglecubes")) {
      const auto &tanglecubes = prims.lookup("tanglecubes");
      for (int i = 0; i < tanglecubes.getLength(); ++i) {
        const auto &tc = tanglecubes[i];
        Vector3 center;
        float size = 1.0f;
        int tr = 255, tg = 255, tb = 255;
        if (tc.exists("center")) {
          center = parseVector3(tc.lookup("center"));
        } else {
          throw GlobalException("TangleCube #" + std::to_string(i) + " : champ 'center' manquant ou invalide");
        }
        if (tc.exists("size")) {
          int si;
          float sf;
          if (tc.lookupValue("size", sf))
            size = sf;
          else if (tc.lookupValue("size", si))
            size = static_cast<float>(si);
          else
            throw GlobalException("TangleCube #" + std::to_string(i) + " : champ 'size' invalide");
        } else {
          throw GlobalException("TangleCube #" + std::to_string(i) + " : champ 'size' manquant");
        }
        if (tc.exists("color")) {
          const auto &col = tc.lookup("color");
          col.lookupValue("r", tr);
          col.lookupValue("g", tg);
          col.lookupValue("b", tb);
        }
        m_scene.addPrimitive(PrimitiveFactory::createTangleCube(center, size, parseMaterial(tc, Color(tr, tg, tb))));
      }
    }
    if (prims.exists("cylinders")) {
      const auto &cylinders = prims.lookup("cylinders");
      for (int i = 0; i < cylinders.getLength(); ++i) {
        const auto &c = cylinders[i];
        Vector3 baseCenter;
        Vector3 rotation(0, 0, 0);
        float radius = 1.0f;
        float height = std::numeric_limits<float>::infinity();
        int cr = 255, cg = 255, cb = 255;

        if (c.exists("baseCenter")) {
          baseCenter = parseVector3(c.lookup("baseCenter"));
        } else {
          throw GlobalException("Cylinder #" + std::to_string(i) + " : champ 'baseCenter' manquant ou invalide");
        }
        if (c.exists("radius")) {
          int ri;
          float rf;
          if (c.lookupValue("radius", ri))
            radius = static_cast<float>(ri);
          else if (c.lookupValue("radius", rf))
            radius = rf;
          else
            throw GlobalException("Cylinder #" + std::to_string(i) + " : champ 'radius' manquant ou invalide");
        }
        if (c.exists("height")) {
          int hi;
          float hf;
          if (c.lookupValue("height", hi))
            height = static_cast<float>(hi);
          else if (c.lookupValue("height", hf))
            height = hf;
        }
        if (c.exists("rotation")) {
          rotation = parseVector3(c.lookup("rotation"));
        }
        if (c.exists("color")) {
          const auto &col = c.lookup("color");
          col.lookupValue("r", cr);
          col.lookupValue("g", cg);
          col.lookupValue("b", cb);
        }
        m_scene.addPrimitive(PrimitiveFactory::createCylinder(baseCenter, radius, height, rotation, parseMaterial(c, Color(cr, cg, cb))));
      }
    }
    if (prims.exists("cones")) {
      const auto &cones = prims.lookup("cones");
      for (int i = 0; i < cones.getLength(); ++i) {
        const auto &c = cones[i];
        Vector3 baseCenter;
        Vector3 rotation(0, 0, 0);
        float radius = 1.0f;
        float height = std::numeric_limits<float>::infinity();
        int cr = 255, cg = 255, cb = 255;
        if (c.exists("baseCenter")) {
          baseCenter = parseVector3(c.lookup("baseCenter"));
        } else {
          throw GlobalException("Cone #" + std::to_string(i) + " : champ 'baseCenter' manquant ou invalide");
        }
        if (c.exists("radius")) {
          int ri;
          float rf;
          if (c.lookupValue("radius", ri))
            radius = static_cast<float>(ri);
          else if (c.lookupValue("radius", rf))
            radius = rf;
          else
            throw GlobalException("Cone #" + std::to_string(i) + " : champ 'radius' manquant ou invalide");
        } else {
          throw GlobalException("Cone #" + std::to_string(i) + " : champ 'radius' manquant ou invalide");
        }
        if (c.exists("height")) {
          int hi;
          float hf;
          if (c.lookupValue("height", hi))
            height = static_cast<float>(hi);
          else if (c.lookupValue("height", hf))
            height = hf;
        }
        if (c.exists("rotation"))
          rotation = parseVector3(c.lookup("rotation"));
        if (c.exists("color")) {
          const auto &col = c.lookup("color");
          col.lookupValue("r", cr);
          col.lookupValue("g", cg);
          col.lookupValue("b", cb);
        }

        m_scene.addPrimitive(PrimitiveFactory::createCone(baseCenter, radius, height, rotation, parseMaterial(c, Color(cr, cg, cb))));
      }
    }
    if (prims.exists("triangles")) {
      const auto &triangles = prims.lookup("triangles");
      for (int i = 0; i < triangles.getLength(); ++i) {
        const auto &t = triangles[i];
        if (!t.exists("a") || !t.exists("b") || !t.exists("c"))
          throw GlobalException("Triangle #" + std::to_string(i) + " : points a, b, c manquants");

        Vector3 a = parseVector3(t.lookup("a"));
        Vector3 b = parseVector3(t.lookup("b"));
        Vector3 c = parseVector3(t.lookup("c"));

        int r = 255, g = 255, b_col = 255;
        if (t.exists("color")) {
          const auto &col = t.lookup("color");
          col.lookupValue("r", r);
          col.lookupValue("g", g);
          col.lookupValue("b", b_col);
        }
        m_scene.addPrimitive(PrimitiveFactory::createTriangle(a, b, c, parseMaterial(t, Color(r, g, b_col))));
      }
    }
    if (prims.exists("torus")) {
      const auto &toruses = prims.lookup("torus");
      for (int i = 0; i < toruses.getLength(); ++i) {
        const auto &t = toruses[i];
        Vector3 center;
        Vector3 rotation(0, 0, 0);
        float majorRadius = 1.0f;
        float minorRadius = 0.5f;
        int cr = 255, cg = 255, cb = 255;
        if (t.exists("center")) {
          center = parseVector3(t.lookup("center"));
        } else {
          throw GlobalException("Torus #" + std::to_string(i) + " : champ 'center' manquant ou invalide");
        }
        if (t.exists("majorRadius")) {
          int ri;
          float rf;
          if (t.lookupValue("majorRadius", ri))
            majorRadius = static_cast<float>(ri);
          else if (t.lookupValue("majorRadius", rf))
            majorRadius = rf;
          else
            throw GlobalException("Torus #" + std::to_string(i) + " : champ 'majorRadius' manquant ou invalide");
        }
        if (t.exists("minorRadius")) {
          int ri;
          float rf;
          if (t.lookupValue("minorRadius", ri))
            minorRadius = static_cast<float>(ri);
          else if (t.lookupValue("minorRadius", rf))
            minorRadius = rf;
          else
            throw GlobalException("Torus #" + std::to_string(i) + " : champ 'minorRadius' manquant ou invalide");
        }
        if (t.exists("rotation"))
          rotation = parseVector3(t.lookup("rotation"));
        if (t.exists("color")) {
          const auto &col = t.lookup("color");
          col.lookupValue("r", cr);
          col.lookupValue("g", cg);
          col.lookupValue("b", cb);
        }
        m_scene.addPrimitive(PrimitiveFactory::createTorus(center, majorRadius, minorRadius, rotation, parseMaterial(t, Color(cr, cg, cb))));
      }
    }
    if (prims.exists("obj")) {
      const auto &objs = prims.lookup("obj");
      for (int i = 0; i < objs.getLength(); ++i) {
        const auto &obj = objs[i];
        std::string path;
        int cr = 255, cg = 255, cb = 255;
        Vector3 offset(0.0f, 0.0f, 0.0f);
        Vector3 rotation(0.0f, 0.0f, 0.0f);
        float scale = 1.0f;
        if (!obj.lookupValue("file", path))
          throw GlobalException("OBJ #" + std::to_string(i) + " : champ 'file' manquant");
        if (obj.exists("color")) {
          const auto &col = obj.lookup("color");
          col.lookupValue("r", cr);
          col.lookupValue("g", cg);
          col.lookupValue("b", cb);
        }
        if (obj.exists("scale")) {
          int si;
          float sf;
          if (obj.lookupValue("scale", si))
            scale = static_cast<float>(si);
          else if (obj.lookupValue("scale", sf))
            scale = sf;
        }
        if (obj.exists("offset"))
          offset = parseVector3(obj.lookup("offset"));
        if (obj.exists("rotation"))
          rotation = parseVector3(obj.lookup("rotation"));
        auto triangles = ObjParser::loadFromFile(path, scale, offset, rotation);
        for (const auto &tri : triangles) {
          m_scene.addPrimitive(PrimitiveFactory::createTriangle(tri.a, tri.b, tri.c, parseMaterial(obj, Color(cr, cg, cb))));
        }
      }
    }
    return true;
  } catch (const libconfig::SettingException &e) {
    throw GlobalException("[SceneParser] Error parsing primitives: " + std::string(e.what()));
  }
}

Raytracer::Vector3 Raytracer::SceneParser::parseVector3(const libconfig::Setting &setting) {
    float x = 0.0f, y = 0.0f, z = 0.0f;

    try {
        if (setting.exists("x")) {
            if (setting["x"].getType() == libconfig::Setting::TypeFloat)
                x = static_cast<float>(setting.lookup("x"));
            else if (setting["x"].getType() == libconfig::Setting::TypeInt)
                x = static_cast<float>(static_cast<int>(setting.lookup("x")));
        }
        if (setting.exists("y")) {
            if (setting["y"].getType() == libconfig::Setting::TypeFloat)
                y = static_cast<float>(setting.lookup("y"));
            else if (setting["y"].getType() == libconfig::Setting::TypeInt)
                y = static_cast<float>(static_cast<int>(setting.lookup("y")));
        }
        if (setting.exists("z")) {
            if (setting["z"].getType() == libconfig::Setting::TypeFloat)
                z = static_cast<float>(setting.lookup("z"));
            else if (setting["z"].getType() == libconfig::Setting::TypeInt)
                z = static_cast<float>(static_cast<int>(setting.lookup("z")));
        }
    } catch (const libconfig::SettingException &e) {
        throw GlobalException("[SceneParser] Error parsing vector3: " + std::string(e.what()));
    }
    return Vector3(x, y, z);
}

Raytracer::Material Raytracer::SceneParser::parseMaterial(const libconfig::Setting &setting, const Color &defaultColor) {
  Material material;
  material.setColor(defaultColor);

  if (!setting.exists("material")) {
    return material;
  }

  try {
    const auto &mat = setting.lookup("material");

    std::string type;
    if (mat.lookupValue("type", type)) {
      if (type == "flat" || type == "flat_color") {
        material.setType(Material::FLAT_COLOR);
      } else if (type == "lambertian") {
        material.setType(Material::LAMBERTIAN);
      } else if (type == "metal") {
        material.setType(Material::METAL);
      } else if (type == "dielectric" || type == "glass") {
        material.setType(Material::DIELECTRIC);
      } else if (type == "emissive" || type == "light") {
        material.setType(Material::EMISSIVE);
      }
    }

    float value;
    if (mat.lookupValue("roughness", value))
      material.setRoughness(value);
    if (mat.lookupValue("metalness", value))
      material.setMetalness(value);
    if (mat.lookupValue("reflectivity", value))
      material.setReflectivity(value);
    if (mat.lookupValue("transparency", value))
      material.setTransparency(value);
    if (mat.lookupValue("refractiveIndex", value))
      material.setRefractiveIndex(value);
    if (mat.lookupValue("emissiveIntensity", value))
      material.setEmissiveIntensity(value);

    if (mat.exists("color")) {
      const auto &col = mat.lookup("color");
      int r = defaultColor.getR(), g = defaultColor.getG(), b = defaultColor.getB();
      col.lookupValue("r", r);
      col.lookupValue("g", g);
      col.lookupValue("b", b);
      material.setColor(Color(r, g, b));
    }

  } catch (const libconfig::SettingException &e) {
    throw GlobalException("[SceneParser] Error parsing material: " + std::string(e.what()));
  }

  return material;
}
