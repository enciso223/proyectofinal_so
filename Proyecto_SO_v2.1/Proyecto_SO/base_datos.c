#include "base_datos.h"
#include <stdio.h>
#include <stdlib.h>

int inicializar_base_datos() {
    sqlite3 *db;
    char *err_msg = 0;
    
    int rc = sqlite3_open("planificador.db", &db);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }
    
    char *sql = "CREATE TABLE IF NOT EXISTS ejecuciones ("
                "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                "comando TEXT, "
                "algoritmo TEXT, "
                "tiempo_inicio INTEGER, "
                "tiempo_estimado INTEGER, "
                "tiempo_finalizacion INTEGER, "
                "turnaround_time INTEGER, "
                "response_time INTEGER);";
    
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    }
    
    sqlite3_close(db);
    
    return 0;
}

int insertar_ejecucion(Comando* comandos, int num_comandos, const char* algoritmo) {
    sqlite3 *db;
    char *err_msg = 0;
    
    int rc = sqlite3_open("planificador.db", &db);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }
    
    char sql[1024];
    
    for (int i = 0; i < num_comandos; ++i) {
        snprintf(sql, sizeof(sql), 
                 "INSERT INTO ejecuciones (comando, algoritmo, tiempo_inicio, tiempo_estimado, tiempo_finalizacion, turnaround_time, response_time) "
                 "VALUES ('%s', '%s', %d, %d, %d, %d, %d);",
                 comandos[i].comando, algoritmo, comandos[i].tiempo_inicio, comandos[i].tiempo_estimado, comandos[i].tiempo_finalizacion,
                 comandos[i].turnaround_time, comandos[i].response_time);
        
        rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
        
        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", err_msg);
            sqlite3_free(err_msg);
            sqlite3_close(db);
            return 1;
        }
    }
    
    sqlite3_close(db);
    
    return 0;
}

void mostrar_ejecuciones() {
    sqlite3 *db;
    sqlite3_stmt *res;
    
    int rc = sqlite3_open("planificador.db", &db);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }
    
    char *sql = "SELECT id, comando, algoritmo, tiempo_inicio, tiempo_estimado, tiempo_finalizacion, turnaround_time, response_time FROM ejecuciones";
    
    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }
    
    printf("Listado de ejecuciones:\n");
    
    while (sqlite3_step(res) == SQLITE_ROW) {
        printf("ID: %d, Comando: %s, Algoritmo: %s, Tiempo Inicio: %d, Tiempo Estimado: %d, Tiempo Finalización: %d, Turnaround Time: %d, Response Time: %d\n", 
               sqlite3_column_int(res, 0), 
               sqlite3_column_text(res, 1),
               sqlite3_column_text(res, 2),
               sqlite3_column_int(res, 3),
               sqlite3_column_int(res, 4),
               sqlite3_column_int(res, 5),
               sqlite3_column_int(res, 6),
               sqlite3_column_int(res, 7));
    }
    
    sqlite3_finalize(res);
    sqlite3_close(db);
}

