#!/bin/bash

# Variables de couleur pour les sorties
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Vérifier si lcov est installé
which lcov > /dev/null
if [ $? -ne 0 ]; then
  echo -e "${RED}lcov n'est pas installé. Veuillez l'installer avec 'sudo pacman -S lcov' sur Arch Linux.${NC}"
  exit 1
fi

echo -e "${BLUE}=== Préparation de l'environnement de test ===${NC}"

# Nettoyer les fichiers de couverture précédents
echo -e "${YELLOW}Nettoyage des fichiers de couverture précédents...${NC}"
find . -name "*.gcda" -delete
find . -name "*.gcno" -delete

# Reconstruire avec la couverture activée
echo -e "${YELLOW}Reconstruction du projet avec la couverture de code activée...${NC}"
rm -rf build
mkdir -p build
cd build
cmake .. -DBUILD_TESTS=ON -DCODE_COVERAGE=ON
make -j$(nproc)
cd ..

# Exécuter les tests
echo -e "\n${BLUE}=== Exécution des tests unitaires ===${NC}"
./run_tests

# Créer un répertoire pour les rapports de couverture
echo -e "\n${BLUE}=== Génération du rapport de couverture ===${NC}"
mkdir -p coverage

# Collecter les données de couverture
echo -e "${YELLOW}Collecte des données de couverture...${NC}"
lcov --capture --directory build --output-file coverage/coverage.info

# Exclure les fichiers externes
echo -e "${YELLOW}Filtrage des fichiers externes...${NC}"
lcov --remove coverage/coverage.info '/usr/*' --output-file coverage/filtered_coverage.info

# Générer le rapport HTML
echo -e "${YELLOW}Génération du rapport HTML...${NC}"
genhtml coverage/filtered_coverage.info --output-directory coverage/html

echo -e "\n${GREEN}=== Terminé ! ===${NC}"
echo -e "${GREEN}Rapport de couverture généré dans le répertoire 'coverage/html'${NC}"
echo -e "${GREEN}Ouvrez coverage/html/index.html dans votre navigateur pour voir le rapport${NC}" 