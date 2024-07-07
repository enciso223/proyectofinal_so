#include "planificador.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fcfs(Comando* comandos, int num_comandos) {
    // Ordenar por tiempo de inicio
    for (int i = 0; i < num_comandos - 1; ++i) {
        for (int j = 0; j < num_comandos - i - 1; ++j) {
            if (comandos[j].tiempo_inicio > comandos[j + 1].tiempo_inicio) {
                Comando temp = comandos[j];
                comandos[j] = comandos[j + 1];
                comandos[j + 1] = temp;
            }
        }
    }

    int tiempo_actual = 0;
    for (int i = 0; i < num_comandos; ++i) {
        if (tiempo_actual < comandos[i].tiempo_inicio) {
            tiempo_actual = comandos[i].tiempo_inicio;
        }
        comandos[i].tiempo_finalizacion = tiempo_actual + comandos[i].tiempo_estimado;
        comandos[i].turnaround_time = comandos[i].tiempo_finalizacion - comandos[i].tiempo_inicio;
        comandos[i].response_time = tiempo_actual - comandos[i].tiempo_inicio;
        tiempo_actual = comandos[i].tiempo_finalizacion;
    }
}

void rr(Comando* comandos, int num_comandos, int quantum) {
    int tiempo_actual = 0;
    int completado = 0;
    int tiempos_restantes[num_comandos];

    for (int i = 0; i < num_comandos; ++i) {
        tiempos_restantes[i] = comandos[i].tiempo_estimado;
    }

    while (completado < num_comandos) {
        for (int i = 0; i < num_comandos; ++i) {
            if (comandos[i].tiempo_inicio <= tiempo_actual && tiempos_restantes[i] > 0) {
                if (comandos[i].tiempo_estimado == tiempos_restantes[i]) {
                    comandos[i].response_time = tiempo_actual - comandos[i].tiempo_inicio;
                }

                if (tiempos_restantes[i] > quantum) {
                    tiempo_actual += quantum;
                    tiempos_restantes[i] -= quantum;
                } else {
                    tiempo_actual += tiempos_restantes[i];
                    tiempos_restantes[i] = 0;
                    comandos[i].tiempo_finalizacion = tiempo_actual;
                    comandos[i].turnaround_time = comandos[i].tiempo_finalizacion - comandos[i].tiempo_inicio;
                    completado++;
                }
            }
        }
    }
}

void sjf(Comando* comandos, int num_comandos) {
    // Ordenar por tiempo estimado
    for (int i = 0; i < num_comandos - 1; ++i) {
        for (int j = 0; j < num_comandos - i - 1; ++j) {
            if (comandos[j].tiempo_estimado > comandos[j + 1].tiempo_estimado) {
                Comando temp = comandos[j];
                comandos[j] = comandos[j + 1];
                comandos[j + 1] = temp;
            }
        }
    }

    int tiempo_actual = 0;
    for (int i = 0; i < num_comandos; ++i) {
        if (tiempo_actual < comandos[i].tiempo_inicio) {
            tiempo_actual = comandos[i].tiempo_inicio;
        }
        comandos[i].tiempo_finalizacion = tiempo_actual + comandos[i].tiempo_estimado;
        comandos[i].turnaround_time = comandos[i].tiempo_finalizacion - comandos[i].tiempo_inicio;
        comandos[i].response_time = tiempo_actual - comandos[i].tiempo_inicio;
        tiempo_actual = comandos[i].tiempo_finalizacion;
    }
}

void srt(Comando* comandos, int num_comandos) {
    int tiempo_actual = 0;
    int completado = 0;
    int tiempos_restantes[num_comandos];

    for (int i = 0; i < num_comandos; ++i) {
        tiempos_restantes[i] = comandos[i].tiempo_estimado;
    }

    while (completado < num_comandos) {
        int idx = -1;
        int menor_tiempo_restante = 1000000; // Un número grande para inicializar

        for (int i = 0; i < num_comandos; ++i) {
            if (comandos[i].tiempo_inicio <= tiempo_actual && tiempos_restantes[i] > 0 && tiempos_restantes[i] < menor_tiempo_restante) {
                menor_tiempo_restante = tiempos_restantes[i];
                idx = i;
            }
        }

        if (idx != -1) {
            if (comandos[idx].tiempo_estimado == tiempos_restantes[idx]) {
                comandos[idx].response_time = tiempo_actual - comandos[idx].tiempo_inicio;
            }

            tiempo_actual++;
            tiempos_restantes[idx]--;

            if (tiempos_restantes[idx] == 0) {
                comandos[idx].tiempo_finalizacion = tiempo_actual;
                comandos[idx].turnaround_time = comandos[idx].tiempo_finalizacion - comandos[idx].tiempo_inicio;
                completado++;
            }
        } else {
            tiempo_actual++;
        }
    }
}

void hrrn(Comando* comandos, int num_comandos) {
    int tiempo_actual = 0;
    int completado = 0;
    int espera[num_comandos];

    for (int i = 0; i < num_comandos; ++i) {
        espera[i] = 0;
    }

    while (completado < num_comandos) {
        int idx = -1;
        double mayor_ratio = -1.0;

        for (int i = 0; i < num_comandos; ++i) {
            if (comandos[i].tiempo_inicio <= tiempo_actual && comandos[i].tiempo_finalizacion == 0) {
                double ratio = (espera[i] + comandos[i].tiempo_estimado) / (double)comandos[i].tiempo_estimado;
                if (ratio > mayor_ratio) {
                    mayor_ratio = ratio;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            if (comandos[idx].tiempo_finalizacion == 0) {
                comandos[idx].response_time = tiempo_actual - comandos[idx].tiempo_inicio;
            }

            tiempo_actual += comandos[idx].tiempo_estimado;
            comandos[idx].tiempo_finalizacion = tiempo_actual;
            comandos[idx].turnaround_time = comandos[idx].tiempo_finalizacion - comandos[idx].tiempo_inicio;
            completado++;
        } else {
            tiempo_actual++;
        }

        for (int i = 0; i < num_comandos; ++i) {
            if (comandos[i].tiempo_inicio <= tiempo_actual && comandos[i].tiempo_finalizacion == 0) {
                espera[i]++;
            }
        }
    }
}

