// Jean Paul Davalos Valencia 1832375
// David  Alejandro  Enciso Gutierrez 2240581


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include "base_datos.h"
#include "planificador.h"
#include "gestor_contenedores.h"

void calcular_promedios(Comando* comandos, int num_comandos, int* turnaround_avg, int* response_avg) {
    int turnaround_total = 0;
    int response_total = 0;

    for (int i = 0; i < num_comandos; ++i) {
        turnaround_total += comandos[i].turnaround_time;
        response_total += comandos[i].response_time;
    }

    *turnaround_avg = turnaround_total / num_comandos;
    *response_avg = response_total / num_comandos;
}

int main() {
    if (inicializar_base_datos() != 0) {
        return 1;
    }

    char comando[100];
    Comando comandos[100];
    int num_comandos = 0;
    int tiempo_inicio, tiempo_estimado;

    printf("Ingrese el comando (o 'salir' para terminar): ");
    fgets(comando, sizeof(comando), stdin);
    comando[strcspn(comando, "\n")] = 0;

    while (strcmp(comando, "salir") != 0) {
        printf("Ingrese el tiempo de inicio: ");
        scanf("%d", &tiempo_inicio);
        printf("Ingrese el tiempo estimado: ");
        scanf("%d", &tiempo_estimado);
        getchar();

        Comando nuevo_comando;
        strcpy(nuevo_comando.comando, comando);
        nuevo_comando.tiempo_inicio = tiempo_inicio;
        nuevo_comando.tiempo_estimado = tiempo_estimado;

        comandos[num_comandos] = nuevo_comando;
        num_comandos++;

        printf("Ingrese el comando (o 'salir' para terminar): ");
        fgets(comando, sizeof(comando), stdin);
        comando[strcspn(comando, "\n")] = 0;
    }

    char algoritmo[100];
    printf("Ingrese el algoritmo de planificación: ");
    fgets(algoritmo, sizeof(algoritmo), stdin);
    algoritmo[strcspn(algoritmo, "\n")] = 0;

    if (strcmp(algoritmo, "FCFS") == 0) {
        fcfs(comandos, num_comandos);
    } else if (strcmp(algoritmo, "SJF") == 0) {
        sjf(comandos, num_comandos);
    } else if (strcmp(algoritmo, "SRT") == 0) {
        srt(comandos, num_comandos);
    } else if (strcmp(algoritmo, "HRRN") == 0) {
        hrrn(comandos, num_comandos);
    } else if (strcmp(algoritmo, "RR") == 0) {
        int quantum;
        printf("Ingrese el quantum: ");
        scanf("%d", &quantum);
        getchar();
        rr(comandos, num_comandos, quantum);
    } else {
        printf("Algoritmo no reconocido.\n");
        return 1;
    }

    int turnaround_avg, response_avg;
    calcular_promedios(comandos, num_comandos, &turnaround_avg, &response_avg);

    printf("Tiempos de cada proceso:\n");
    for (int i = 0; i < num_comandos; ++i) {
        printf("Comando: %s\n", comandos[i].comando);
        printf("Turnaround time: %d\n", comandos[i].turnaround_time);
        printf("Response time: %d\n", comandos[i].response_time);
    }

    printf("Turnaround time promedio: %d\n", turnaround_avg);
    printf("Response time promedio: %d\n", response_avg);

    insertar_ejecucion(comandos, num_comandos, algoritmo);

    printf("Ejecuciones guardadas en la base de datos.\n");

    mostrar_ejecuciones();

    return 0;
}

