#ifndef PLANIFICADOR_H
#define PLANIFICADOR_H

#include "comun.h"

void fcfs(Comando* comandos, int num_comandos);
void rr(Comando* comandos, int num_comandos, int quantum);
void sjf(Comando* comandos, int num_comandos);
void srt(Comando* comandos, int num_comandos);
void hrrn(Comando* comandos, int num_comandos);

#endif // PLANIFICADOR_H



