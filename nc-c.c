#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) 
{
    if (argc != 3) {
        printf("Utilisation : %s <adresse IP> <port>\n", argv[0]);
        return 1;
    }

    // Création du socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Erreur lors de la création du socket");
        return 1;
    }

    // Configuration de l'adresse du serveur
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    server_addr.sin_port = htons(atoi(argv[2]));

    // Connexion au serveur
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Erreur lors de la connexion au serveur");
        return 1;
    }

    // Boucle de lecture et d'envoi des données
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read, bytes_written;
    while (1) {
        // Lecture des données depuis l'entrée standard
        bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE);
        if (bytes_read <= 0) {
            break;
        }

        // Ajout du caractère de retour à la ligne ('\r') avant chaque saut de ligne ('\n')
        for (int i = 0; i < bytes_read; i++) {
            if (buffer[i] == '\n') {
                memmove(&buffer[i + 1], &buffer[i], bytes_read - i);
                buffer[i] = '\r';
                bytes_read++;
                i++;
            }
        }

        // Envoi des données au serveur
        bytes_written = send(sockfd, buffer, bytes_read, 0);
        if (bytes_written < 0) {
            perror("Erreur lors de l'envoi des données");
            break;
        }
    }

    // Fermeture de la connexion
    close(sockfd);

    return 0;
}

