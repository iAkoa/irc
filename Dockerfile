# Utilisez l'image de base Ubuntu
FROM ubuntu:latest

# Mise à jour des paquets existants et installation de Make et g++ et zsh et git
RUN apt-get update && apt-get install -y make g++ zsh git

# Installez Oh My Zsh
RUN sh -c "$(curl -fsSL https://raw.github.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"


SHELL ["/bin/zsh"]

# Définition du répertoire de travail
WORKDIR /project

# Exposez le port 8888 pour les connexions entrantes
EXPOSE 8888

# Commande d'exécution pour lancer le projet
CMD ["tail", "-f", "/dev/null"]

