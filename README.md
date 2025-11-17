# 🎨 Raytracer

[![C++](https://img.shields.io/badge/C++-20-blue.svg)](https://en.cppreference.com/w/cpp/20)
[![CMake](https://img.shields.io/badge/CMake-3.16+-green.svg)](https://cmake.org/)
[![License](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

Un raytracer moderne écrit en **C++20** qui simule le comportement de la lumière pour générer des images 3D réalistes. Ce projet implémente un moteur de rendu par lancer de rayons complet avec support de multiples primitives géométriques, différents types d'éclairage et matériaux.

## 📋 Table des matières

- [Fonctionnalités](#-fonctionnalités)
- [Prérequis](#-prérequis)
- [Installation](#-installation)
- [Utilisation](#-utilisation)
- [Structure du projet](#-structure-du-projet)
- [Primitives supportées](#-primitives-supportées)
- [Types d'éclairage](#-types-déclairage)
- [Format de scène](#-format-de-scène)
- [Exemples](#-exemples)
- [Documentation](#-documentation)
- [Développement](#-développement)
- [Contribution](#-contribution)
- [License](#-license)

## ✨ Fonctionnalités

- 🎯 **Rendu par lancer de rayons** : Simulation physique de la lumière
- 🔷 **Primitives multiples** : Sphères, plans, cylindres, cônes, tori, triangles, TangleCube
- 💡 **Système d'éclairage avancé** : Lumière ambiante, ponctuelle, directionnelle
- 🎨 **Matériaux** : Support des propriétés de matériaux (couleur, réflexion, etc.)
- 📐 **Parsing de fichiers OBJ** : Import de modèles 3D
- 📷 **Caméra configurable** : Résolution, position, rotation, champ de vision
- 🖼️ **Export PPM** : Génération d'images haute qualité
- ⚡ **Optimisations** : Compilation optimisée avec flags de performance

## 🔧 Prérequis

- **C++20** compatible compiler (GCC 10+, Clang 12+, MSVC 2019+)
- **CMake** 3.16 ou supérieur
- **libconfig++** pour le parsing des fichiers de configuration
- **SFML** (optionnel) pour l'affichage graphique

### Installation des dépendances

#### macOS
```bash
brew install cmake libconfig sfml
```

#### Ubuntu/Debian
```bash
sudo apt-get update
sudo apt-get install build-essential cmake libconfig++-dev libsfml-dev
```

#### Fedora
```bash
sudo dnf install gcc-c++ cmake libconfig++-devel SFML-devel
```

## 🚀 Installation

1. **Cloner le repository**
```bash
git clone https://github.com/votre-username/raytracer.git
cd raytracer
```

2. **Compiler le projet**
```bash
./start.sh
```

Ou manuellement :
```bash
mkdir -p build && cd build
cmake ..
make -j$(nproc)  # ou make -j$(sysctl -n hw.ncpu) sur macOS
```

3. **Activer SFML (optionnel)**
```bash
cd build
cmake -DUSE_SFML=ON ..
make -j$(nproc)
```

## 💻 Utilisation

### Lancer le raytracer

```bash
./raytracer <SCENE_FILE>
```

Le fichier de scène doit être au format libconfig++. Des exemples sont disponibles dans le dossier `scenes/`.

### Exemple basique

```bash
./raytracer scenes/demo_scene.cfg
```

L'image générée sera sauvegardée dans `output.ppm` à la racine du projet.

### Visualiser l'image PPM

```bash
# macOS
open output.ppm

# Linux (avec ImageMagick)
display output.ppm

# Ou convertir en PNG
convert output.ppm output.png
```

## 📁 Structure du projet

```
raytracer/
├── include/              # Headers
│   ├── Core/           # Caméra, Scène
│   ├── Primitives/     # Formes géométriques
│   ├── Lights/         # Système d'éclairage
│   ├── Material/       # Matériaux
│   ├── Parser/         # Parsers de fichiers
│   ├── Renderer/       # Moteur de rendu
│   ├── Maths/          # Ray, Vector3
│   └── Utils/          # Utilitaires
├── src/                # Implémentations
├── scenes/             # Fichiers de scène d'exemple
├── obj/                # Modèles 3D OBJ
├── tests/              # Tests unitaires
├── docs/               # Documentation Doxygen
├── CMakeLists.txt      # Configuration CMake
└── README.md          # Ce fichier
```

## 🔷 Primitives supportées

- **Sphere** : Sphères avec position, rayon et couleur
- **Plane** : Plans infinis
- **Cylinder** : Cylindres
- **Cone** : Cônes
- **Torus** : Tori (donuts)
- **Triangle** : Triangles individuels
- **TangleCube** : Cube de Tangle (forme complexe)
- **CompositePrimitive** : Groupes de primitives (pour fichiers OBJ)

## 💡 Types d'éclairage

- **AmbientLight** : Éclairage ambiant uniforme
- **PointLight** : Sources lumineuses ponctuelles
- **DirectionalLight** : Lumière directionnelle (soleil)
- **CompositeLight** : Combinaison de plusieurs lumières

## 📝 Format de scène

Les fichiers de scène utilisent le format **libconfig++**. Voici un exemple complet :

```cpp
camera = { 
    resolution = { width = 800; height = 600; };
    position = { x = 0; y = 0; z = -400; };
    rotation = { x = 0; y = 0; z = 0; };
    fieldOfView = 70.0;
}

lights = {
    ambient = 0.2;
    point = (
        { x = 150; y = 200; z = -100; },
        { x = -200; y = 150; z = -100; }
    );
    directional = (
        { x = 0.5; y = -1; z = 0.3; }
    );
}

primitives = {
    spheres = (
        {
            x = 0;
            y = 0;
            z = 0;
            r = 50;
            color = { r = 255; g = 0; b = 0; };
        }
    );
    planes = (
        {
            point = { x = 0; y = -100; z = 0; };
            normal = { x = 0; y = 1; z = 0; };
            color = { r = 200; g = 200; b = 200; };
        }
    );
    cylinders = (
        {
            center = { x = 100; y = 0; z = 0; };
            axis = { x = 0; y = 1; z = 0; };
            radius = 30;
            height = 100;
            color = { r = 0; g = 255; b = 0; };
        }
    );
    cones = (
        {
            apex = { x = -100; y = 50; z = 0; };
            axis = { x = 0; y = -1; z = 0; };
            angle = 30;
            height = 100;
            color = { r = 0; g = 0; b = 255; };
        }
    );
    triangles = (
        {
            v1 = { x = 0; y = 100; z = 50; };
            v2 = { x = -50; y = 0; z = 50; };
            v3 = { x = 50; y = 0; z = 50; };
            color = { r = 255; g = 255; b = 0; };
        }
    );
    obj_files = (
        "obj/model.obj"
    );
}
```

## 🎬 Exemples

Le dossier `scenes/` contient plusieurs exemples :

- `demo_scene.cfg` : Scène de démonstration avec sphères colorées
- `simple_reflection.cfg` : Exemple avec réflexions
- `with_plane.cfg` : Scène avec un plan
- `with_cylinder.cfg` : Scène avec cylindre
- `with_cone.cfg` : Scène avec cône
- `with_torus.cfg` : Scène avec tore
- `with_triangle.cfg` : Scène avec triangle
- `with_tanglecube.cfg` : Scène avec TangleCube
- `obj.cfg` : Exemple avec import de fichier OBJ

## 📚 Documentation

La documentation complète générée par Doxygen est disponible dans le dossier `docs/`. Pour la générer vous-même :

```bash
doxygen Doxyfile
```

Puis ouvrez `docs/html/index.html` dans votre navigateur.

## 🛠️ Développement

### Exécuter les tests

```bash
cd build
cmake ..
make
./run_tests.sh
```

### Formatage du code

Il est recommandé d'utiliser `clang-format` pour maintenir un style cohérent :

```bash
find src include -name "*.cpp" -o -name "*.hpp" | xargs clang-format -i
```

### Architecture

Le raytracer suit une architecture modulaire :

- **Core** : Gestion de la scène et de la caméra
- **Renderer** : Algorithme de lancer de rayons
- **Primitives** : Implémentation des intersections ray-primitive
- **Lights** : Calcul de l'éclairage selon différents modèles
- **Parser** : Chargement des scènes depuis fichiers

## 🤝 Contribution

Les contributions sont les bienvenues ! Pour contribuer :

1. Fork le projet
2. Créez une branche pour votre fonctionnalité (`git checkout -b feature/AmazingFeature`)
3. Committez vos changements (`git commit -m 'Add some AmazingFeature'`)
4. Push vers la branche (`git push origin feature/AmazingFeature`)
5. Ouvrez une Pull Request

## 📄 License

Ce projet est sous licence MIT. Voir le fichier `LICENSE` pour plus de détails.

## 🙏 Remerciements

- École Epitech pour le cadre pédagogique
- La communauté open-source pour les outils et bibliothèques utilisés

---

⭐ Si ce projet vous plaît, n'hésitez pas à lui donner une étoile !
