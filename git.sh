#!/bin/bash

# Vérification des paramètres
if [ $# -ne 1 ]; then
    echo "Utilisation : $0 <message de commit>"
    exit 1
fi

# Récupération du message de commit passé en paramètre
commit_message=$1

make fclean
# Ajout des fichiers à l'index Git
git add .

# Création du message de commit avec la date actuelle et l'heure
date_time=$(date +"%Y-%m-%d %H:%M:%S")
commit_message_with_date="$commit_message le $date_time"

# Effectuer le commit avec le message
git commit -m "$commit_message_with_date"

# Affichage du résultat du commit
if [ $? -eq 0 ]; then
    echo "Commit effectué avec succès : $commit_message_with_date"
else
    echo "Erreur lors de l'exécution du commit."
fi
