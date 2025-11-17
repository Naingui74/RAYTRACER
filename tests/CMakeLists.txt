# CMake configuration for tests
cmake_minimum_required(VERSION 3.16)
project(raytracer_tests)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Options pour la couverture de code
option(CODE_COVERAGE "Enable coverage reporting" ON)
if(CODE_COVERAGE)
  add_compile_options(--coverage -O0)
  add_link_options(--coverage)
endif()

# Rechercher Catch2 en tant que package installé
find_package(Catch2 3 REQUIRED)

# Ajout des répertoires d'en-têtes
include_directories(${CMAKE_SOURCE_DIR}/include)

# Trouver tous les fichiers source pour les tests
file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS *.cpp)

# Ajout des dépendances externes
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBCONFIGPP REQUIRED libconfig++)
include_directories(${LIBCONFIGPP_INCLUDE_DIRS})
link_directories(${LIBCONFIGPP_LIBRARY_DIRS})

# Créer l'exécutable de test
add_executable(run_tests ${TEST_SOURCES})

# Lier avec Catch2 et les autres bibliothèques nécessaires
target_link_libraries(run_tests 
  PRIVATE
  Catch2::Catch2WithMain
  ${LIBCONFIGPP_LIBRARIES}
)

# Ajouter les fichiers source du projet principal (à l'exception de main.cpp)
file(GLOB_RECURSE PROJECT_SOURCES 
  ${CMAKE_SOURCE_DIR}/src/*.cpp
)
# Vérifier si PROJECT_SOURCES est vide
if(NOT PROJECT_SOURCES)
  message(FATAL_ERROR "Aucun fichier source trouvé dans ${CMAKE_SOURCE_DIR}/src/. Vérifiez le chemin.")
endif()

# Filtrer le fichier main.cpp
list(FILTER PROJECT_SOURCES EXCLUDE REGEX ".*main\\.cpp$")

# Créer une bibliothèque à partir des sources du projet
add_library(raytracer_lib STATIC ${PROJECT_SOURCES})

# Lier la bibliothèque du projet à l'exécutable de test
target_link_libraries(run_tests PRIVATE raytracer_lib)

# Inclure le registre de tests Catch2
include(CTest)
include(Catch) 