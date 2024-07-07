#ifndef BASE_DATOS_H
#define BASE_DATOS_H

#include "comun.h"
#include <sqlite3.h>

int inicializar_base_datos();
int insertar_ejecucion(Comando* comandos, int num_comandos, const char* algoritmo);
void mostrar_ejecuciones();

#endif

