#!/bin/bash

# Configuration
PROGRAM="./cub3d_adri"
GOOD_DIR="maps/good"
BAD_DIR="maps/bad"

# Compteurs pour le bilan final
PASSED=0
FAILED=0
LEAK_ERRORS=0

# Couleurs pour le terminal
GREEN="\033[32m"
RED="\033[31m"
YELLOW="\033[33m"
ORANGE="\033[33m"
BLUE="\033[34m"
RESET="\033[0m"

# Vérification de l'existence du programme
if [ ! -f "$PROGRAM" ]; then
    echo -e "${RED}Erreur : L'exécutable $PROGRAM n'existe pas. Lance 'make' avant.${RESET}"
    exit 1
fi

# Vérification de leaks (disponible sur Mac)
if ! command -v leaks &> /dev/null; then
    echo -e "${RED}Erreur : 'leaks' n'est pas disponible.${RESET}"
    echo "Cet outil est uniquement disponible sur macOS avec Xcode."
    exit 1
fi

echo -e "${YELLOW}=== DEBUT DES TESTS AVEC LEAKS ===${RESET}\n"

# Fonction pour tester avec leaks
test_leaks() {
    local map=$1
    local map_name=$(basename "$map")
    
    echo -n "Leaks sur $map_name : "
    
    # Exécuter le programme et capturer les fuites
    LEAKS_OUTPUT=$(leaks -atExit -- "$PROGRAM" "$map" 2>&1)
    STATUS=$?
    
    # Vérifier si leaks a trouvé des fuites
    if echo "$LEAKS_OUTPUT" | grep -q "0 leaks"; then
        echo -e "${GREEN}✓ No leaks${RESET}"
        ((PASSED++))
        return 0
    else
        # Extraire les informations de fuite
        LEAK_COUNT=$(echo "$LEAKS_OUTPUT" | grep "Process.*leaked" | grep -oE "[0-9]+ " | head -1 | tr -d ' ')
        if [ -z "$LEAK_COUNT" ]; then
            LEAK_COUNT=$(echo "$LEAKS_OUTPUT" | grep "leaks" | head -1)
        fi
        
        echo -e "${RED}✗ Leaks detected${RESET}"
        echo "$LEAKS_OUTPUT" | grep -E "Process.*leaked|TOTAL" | head -1 | sed 's/^/  /'
        ((FAILED++))
        ((LEAK_ERRORS++))
        return 1
    fi
}

# Fonction pour tester avec leaks - cartes invalides
test_leaks_bad() {
    local map=$1
    local map_name=$(basename "$map")
    
    echo -n "Leaks sur $map_name : "
    
    # Exécuter le programme et capturer les fuites
    LEAKS_OUTPUT=$(leaks -atExit -- "$PROGRAM" "$map" 2>&1)
    STATUS=$?
    
    # Vérifier si leaks a trouvé des fuites
    if echo "$LEAKS_OUTPUT" | grep -q "0 leaks"; then
        echo -e "${GREEN}✓ No leaks${RESET}"
        ((PASSED++))
        return 0
    else
        echo -e "${ORANGE}⚠ Leaks detected (carte invalide)${RESET}"
        echo "$LEAKS_OUTPUT" | grep -E "Process.*leaked|TOTAL" | head -1 | sed 's/^/  /'
        ((LEAK_ERRORS++))
        return 1
    fi
}

# ------------------------------------------------------------------------------
# 1. Test LEAKS des BONNES cartes
# ------------------------------------------------------------------------------
echo -e "${YELLOW}[+] Test Leaks des cartes valides${RESET}"
if [ -d "$GOOD_DIR" ] && [ "$(ls -A $GOOD_DIR)" ]; then
    for map in "$GOOD_DIR"/*; do
        "$PROGRAM" "$map" > /dev/null 2>&1
        if [ $? -eq 0 ]; then
            test_leaks "$map"
        else
            echo -n "Test de $(basename "$map") : "
            echo -e "${RED}KO (Le programme a échoué)${RESET}"
            ((FAILED++))
        fi
    done
else
    echo "Aucune carte trouvée dans $GOOD_DIR"
fi

echo ""

# ------------------------------------------------------------------------------
# 2. Test LEAKS des MAUVAISES cartes
# ------------------------------------------------------------------------------
echo -e "${YELLOW}[+] Test Leaks des cartes invalides${RESET}"
if [ -d "$BAD_DIR" ] && [ "$(ls -A $BAD_DIR)" ]; then
    for map in "$BAD_DIR"/*; do
        STDERR_OUTPUT=$("$PROGRAM" "$map" 2>&1 > /dev/null)
        if [ $? -ne 0 ] && echo "$STDERR_OUTPUT" | grep -iq "^Error"; then
            test_leaks_bad "$map"
        else
            echo -n "Test de $(basename "$map") : "
            echo -e "${RED}KO (Comportement incorrect)${RESET}"
            ((FAILED++))
        fi
    done
else
    echo "Aucune carte trouvée dans $BAD_DIR"
fi

# ------------------------------------------------------------------------------
# Bilan
# ------------------------------------------------------------------------------
echo -e "\n${YELLOW}=== BILAN FINAL ===${RESET}"
echo -e "${GREEN}Tests sans fuites : $PASSED${RESET}"
if [ $FAILED -gt 0 ]; then
    echo -e "${RED}Tests échoués : $FAILED${RESET}"
fi
if [ $LEAK_ERRORS -gt 0 ]; then
    echo -e "${RED}Erreurs de fuites mémoire : $LEAK_ERRORS${RESET}"
fi

if [ $FAILED -eq 0 ] && [ $LEAK_ERRORS -eq 0 ]; then
    echo -e "${GREEN}Tout est parfait ! Aucune fuite mémoire 🎉${RESET}"
    exit 0
else
    exit 1
fi