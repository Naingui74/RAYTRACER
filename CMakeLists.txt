cmake_minimum_required(VERSION 3.16)
project(raytracer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 💡 Lien compile_commands.json pour l'autocomplétion (VSCode, clangd, etc.)
execute_process(
  COMMAND ln -sf ${PROJECT_SOURCE_DIR}/build/compile_commands.json ${PROJECT_SOURCE_DIR}
)

# ✅ Option pour activer ou désactiver SFML
option(USE_SFML "Enable SFML graphical output" OFF)

# ✅ libconfig++ obligatoire
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBCONFIGPP REQUIRED libconfig++)

include_directories(${LIBCONFIGPP_INCLUDE_DIRS})
link_directories(${LIBCONFIGPP_LIBRARY_DIRS})

# ✅ Ajoute tous les fichiers .cpp
include_directories(include)
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

add_executable(raytracer ${SOURCES})

# ✅ Si SFML est activé, on l'ajoute aux dépendances
if(USE_SFML)
    find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
    target_compile_definitions(raytracer PRIVATE USE_SFML)
    target_link_libraries(raytracer
        ${LIBCONFIGPP_LIBRARIES}
        sfml-graphics
        sfml-window
        sfml-system
    )
else()
    target_link_libraries(raytracer
        ${LIBCONFIGPP_LIBRARIES}
    )
endif()

set_property(TARGET raytracer PROPERTY CXX_STANDARD 20)
# >>>>>>> Stashed changes
