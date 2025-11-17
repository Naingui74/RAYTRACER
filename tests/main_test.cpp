#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <iostream>

// Ce fichier contiendra uniquement l'entrée principale pour Catch2
// Les tests réels seront dans d'autres fichiers

TEST_CASE("Environnement de test fonctionnel", "[sanity]") {
    REQUIRE(1 == 1);
    REQUIRE(2 + 2 == 4);
    std::cout << "L'environnement de test est opérationnel!" << std::endl;
} 