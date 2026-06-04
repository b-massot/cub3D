#!/bin/bash

# Configuration
PROGRAM="./cub3d_adri"
GOOD_DIR="maps/good"
BAD_DIR="maps/bad"

# Compteurs pour le bilan final
PASSED=0
FAILED=0

# Couleurs pour le terminal
GREEN="\033[32m"
RED="\033[31m"
YELLOW="\033[33m"
RESET="\033[0m"

# Vérification de l'existence du programme
if [ ! -f "$PROGRAM" ]; then
    echo -e "${RED}Erreur : L'exécutable $PROGRAM n'existe pas. Lance 'make' avant.${RESET}"
    exit 1
fi

echo -e "${YELLOW}=== DEBUT DES TESTS ===${RESET}\n"

# ------------------------------------------------------------------------------
# 1. Test des BONNES cartes (Doivent réussir, exit code = 0)
# ------------------------------------------------------------------------------
echo -e "${YELLOW}[+] Test des cartes valides (Attendu : SUCCÈS)${RESET}"
if [ -d "$GOOD_DIR" ] && [ "$(ls -A $GOOD_DIR)" ]; then
    for map in "$GOOD_DIR"/*; do
        echo -n "Test de $(basename "$map") : "
        
        # Exécution du programme en masquant la sortie standard
        "$PROGRAM" "$map" > /dev/null 2>&1
        STATUS=$?

        if [ $STATUS -eq 0 ]; then
            echo -e "${GREEN}OK (Succès attendu obtenu)${RESET}"
            ((PASSED++))
        else
            echo -e "${RED}KO (Le programme a échoué avec le code $STATUS)${RESET}"
            ((FAILED++))
        fi
    done
else
    echo "Aucune carte trouvée dans $GOOD_DIR"
fi

echo ""

# ------------------------------------------------------------------------------
# 2. Test des MAUVAISES cartes (Doivent échouer et afficher Error)
# ------------------------------------------------------------------------------
echo -e "${YELLOW}[+] Test des cartes invalides (Attendu : ERREUR)${RESET}"
if [ -d "$BAD_DIR" ] && [ "$(ls -A $BAD_DIR)" ]; then
    for map in "$BAD_DIR"/*; do
        echo -n "Test de $(basename "$map") : "
        
        # On récupère la première ligne de stderr pour vérifier le message d'erreur
        # et on récupère le code de retour
        STDERR_OUTPUT=$("$PROGRAM" "$map" 2>&1 > /dev/null)
        STATUS=$?

        # Vérification : le code doit être != 0 ET la sortie doit commencer par "Error"
        if [ $STATUS -ne 0 ] && echo "$STDERR_OUTPUT" | grep -iq "^Error"; then
            echo -e "${GREEN}OK (Erreur détectée proprement)${RESET}"
            ((PASSED++))
        else
            echo -e "${RED}KO (Comportement incorrect)${RESET}"
            if [ $STATUS -eq 0 ]; then
                echo -e "   -> ${RED}Le programme a renvoyé 0 (succès) alors que la carte est invalide !${RESET}"
            fi
            if ! echo "$STDERR_OUTPUT" | grep -iq "^Error"; then
                echo -e "   -> ${RED}Le message d'erreur ne commence pas par 'Error' ou est vide.${RESET}"
                echo -e "      Sortie reçue : '${STDERR_OUTPUT:0:50}'"
            fi
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
echo -e "${GREEN}Tests réussis : $PASSED${RESET}"
if [ $FAILED -gt 0 ]; then
    echo -e "${RED}Tests échoués : $FAILED${RESET}"
    exit 1
else
    echo -e "${GREEN}Tout est parfait ! 🎉${RESET}"
    exit 0
fi