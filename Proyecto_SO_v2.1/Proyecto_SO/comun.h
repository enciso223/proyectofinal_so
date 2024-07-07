#ifndef COMUN_H
#define COMUN_H

typedef struct {
    char comando[100];
    int tiempo_inicio;
    int tiempo_estimado;
    int tiempo_finalizacion;
    int turnaround_time;
    int response_time;
} Comando;

#endif

