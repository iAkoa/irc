#!/bin/bash

# Nom de l'image Docker
IMAGE_NAME="ft_irc_image"
CONTAINER_NAME="ft_irc_container"

# Vérifiez si l'image existe déjà
if [[ "$(docker images -q ${IMAGE_NAME} 2> /dev/null)" == "" ]]; then
    # Construction de l'image Docker
    echo "Construction de l'image Docker..."
    docker build -t ${IMAGE_NAME} .
fi

# Vérifiez si un conteneur avec le même nom existe déjà
if [[ "$(docker ps -a -q -f name=${CONTAINER_NAME} 2> /dev/null)" != "" ]]; then
    echo "Un conteneur avec le nom ${CONTAINER_NAME} existe déjà."
    echo "Veuillez supprimer le conteneur existant ou utiliser un nom différent."
    exit 1
fi

# Récupération du chemin absolu du dossier actuel
CURRENT_DIR=$(pwd)

# Lancement du conteneur à partir de l'image avec le partage de volume (en excluant le répertoire .git)
echo "Lancement du conteneur à partir de l'image ${IMAGE_NAME} avec partage de volume..."
docker run -it -p 8888:8888 -v ${CURRENT_DIR}:/project --name ${CONTAINER_NAME} -e SHELL=/bin/zsh ${IMAGE_NAME} /bin/zsh