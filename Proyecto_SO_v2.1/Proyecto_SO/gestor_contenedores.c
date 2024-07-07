#include "gestor_contenedores.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void crear_imagen_contenedor(const char* comando, char* id_imagen) {
    char dockerfile[512];
    sprintf(dockerfile, "FROM alpine:latest\nCMD %s\n", comando);

    FILE* file = fopen("Dockerfile", "w");
    if (file == NULL) {
        perror("Error al crear Dockerfile");
        return;
    }
    fprintf(file, "%s", dockerfile);
    fclose(file);

    int ret = system("docker build -t temp_image .");
    if (ret != 0) {
        fprintf(stderr, "Error al construir la imagen de Docker\n");
        return;
    }

    ret = system("docker images -q temp_image > temp_image_id.txt");
    if (ret != 0) {
        fprintf(stderr, "Error al obtener el ID de la imagen de Docker\n");
        return;
    }

    FILE* id_file = fopen("temp_image_id.txt", "r");
    if (id_file == NULL) {
        perror("Error al abrir el archivo de ID de imagen");
        return;
    }
    fscanf(id_file, "%s", id_imagen);
    fclose(id_file);

    system("rm Dockerfile temp_image_id.txt");
}

void ejecutar_contenedor(const char* id_imagen) {
    char comando[256];
    sprintf(comando, "docker run --rm %s", id_imagen);
    int ret = system(comando);
    if (ret != 0) {
        fprintf(stderr, "Error al ejecutar el contenedor de Docker\n");
    }
}

