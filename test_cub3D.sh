#!/bin/bash

# Chemin vers le répertoire contenant les fichiers de test
MAPS_DIR="maps/bad"

# Chemin vers ton programme cub3D (à ajuster selon ta configuration)
CUB3D_EXEC="./cub3D"

# Créer ou vider le fichier de rapport des tests
REPORT_FILE="valgrind_test_report.txt"
echo "Rapport de test Valgrind pour cub3D" > $REPORT_FILE

# Options de Valgrind (ajuster si besoin)
VALGRIND_OPTIONS="--leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=1"

# Initialiser les compteurs pour les tests passés et échoués
passed_count=0
failed_count=0

# Couleurs
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# Boucle sur chaque fichier .cub dans le répertoire
for map_file in $MAPS_DIR/*.cub; do
    echo "Test du fichier: $map_file"
    echo "Test du fichier: $map_file" >> $REPORT_FILE

    # Exécuter Valgrind et vérifier si des erreurs ont été détectées
    valgrind $VALGRIND_OPTIONS $CUB3D_EXEC $map_file 2>&1 | tee -a $REPORT_FILE

    if [ $? -eq 0 ]; then
        echo -e "${GREEN}PASSED${NC}"
        echo "PASSED" >> $REPORT_FILE
        ((passed_count++))
    else
        echo -e "${RED}FAILED${NC}"
        echo "FAILED" >> $REPORT_FILE
        ((failed_count++))
    fi

    # Ajouter une séparation entre les tests
    echo "-------------------------" >> $REPORT_FILE
done

# Afficher le résumé des résultats
echo "Résumé des tests :" >> $REPORT_FILE
echo "Nombre de tests réussis : $passed_count" >> $REPORT_FILE
echo "Nombre de tests échoués : $failed_count" >> $REPORT_FILE

# Afficher aussi dans la console avec des couleurs
echo -e "\nTous les tests Valgrind sont terminés."
echo -e "${GREEN}Nombre de tests réussis : $passed_count${NC}"
echo -e "${RED}Nombre de tests échoués : $failed_count${NC}"

