# proyectofinal_so 

### Informe del Programa de Planificación y Ejecución de Tareas en Contenedores Docker

---

#### Descripción del Programa

Este programa está diseñado para gestionar la ejecución de tareas utilizando contenedores Docker y algoritmos de planificación. Su objetivo es optimizar la ejecución de comandos, asegurando eficiencia y consistencia en un entorno controlado. Desarrollado en lenguaje C, utiliza SQLite para la gestión de datos y Docker para la ejecución de comandos en contenedores.

#### Teoría de Planificación

La planificación de tareas es crucial para la optimización del uso de recursos en sistemas operativos. Los algoritmos de planificación permiten decidir el orden en que se deben ejecutar las tareas, basándose en diferentes criterios como tiempo de llegada, duración estimada y prioridad. Los algoritmos implementados en este programa incluyen:

1. **First-Come, First-Served (FCFS):** Las tareas se ejecutan en el orden en que llegan.
2. **Shortest Job First (SJF):** Las tareas con menor tiempo estimado de ejecución se ejecutan primero.
3. **Shortest Remaining Time (SRT):** Similar a SJF, pero preemptivo, ejecutando siempre la tarea con el menor tiempo restante.
4. **Highest Response Ratio Next (HRRN):** Selecciona la tarea con el mayor ratio de respuesta, considerando tiempo de espera y duración.
5. **Round Robin (RR):** Asigna un tiempo fijo (quantum) a cada tarea, rotando entre ellas hasta completarlas.

#### Estructura del Programa

1. **main.c:** Función principal que inicia la base de datos, recoge los comandos del usuario, aplica el algoritmo de planificación seleccionado, calcula promedios de tiempos y guarda los resultados en la base de datos.
2. **base_datos.c:** Gestiona la creación y manejo de la base de datos SQLite, incluyendo la inserción de registros de ejecuciones.
3. **planificador.c:** Implementa los algoritmos de planificación de tareas.
4. **gestor_contenedores.c:** Gestiona la creación y ejecución de contenedores Docker.
5. **comun.h:** Define la estructura de datos para los comandos.
6. **planificador.h:** Declara las funciones de planificación.
7. **base_datos.h:** Declara las funciones para la gestión de la base de datos.
8. **gestor_contenedores.h:** Declara las funciones para la gestión de contenedores Docker.

#### Compilación y Ejecución

**Pasos para Compilar y Ejecutar el Programa:**

1. **Compilación:**
   - Compilar cada archivo fuente:
     
     gcc -Wall -g -c main.c -o main.o
     gcc -Wall -g -c gestor_contenedores.c -o gestor_contenedores.o
     gcc -Wall -g -c planificador.c -o planificador.o
     gcc -Wall -g -c base_datos.c -o base_datos.o
     
   - Vincular los archivos objeto y generar el ejecutable:
     
     gcc -Wall -g -o contenedorizador main.o gestor_contenedores.o planificador.o base_datos.o -lsqlite3
     

2. **Ejecución:**
   - Ejecutar el programa:
     
     ./contenedorizador
     
   - Introducir los comandos, tiempos de inicio y estimados según las indicaciones:
     
     Ingrese el comando (o 'salir' para terminar): ps ef
     Ingrese el tiempo de inicio: 0
     Ingrese el tiempo estimado: 1
     Ingrese el comando (o 'salir' para terminar): sleep 5
     Ingrese el tiempo de inicio: 5
     Ingrese el tiempo estimado: 5
     Ingrese el comando (o 'salir' para terminar): ls -l
     Ingrese el tiempo de inicio: 5
     Ingrese el tiempo estimado: 1
     Ingrese el comando (o 'salir' para terminar): salir
     

3. **Seleccionar el Algoritmo de Planificación:**
   - Introducir el algoritmo deseado (FCFS, RoundRobin, SPN, SRT, HRRN):
     
     Ingrese el algoritmo de planificación (FCFS, RoundRobin, SPN, SRT, HRRN): FCFS
     

4. **Revisión de Resultados:**
   - Los resultados de las ejecuciones se almacenan en la base de datos SQLite y se muestran en la salida del programa:
     
     ID: 1, Comando: ps ef, Algoritmo: FCFS, Timestamp: 2024-07-01 12:00:00
     ID: 2, Comando: sleep 5, Algoritmo: FCFS, Timestamp: 2024-07-01 12:00:05
     ID: 3, Comando: ls -l, Algoritmo: FCFS, Timestamp: 2024-07-01 12:00:10
     

5. **Consultar la Base de Datos:**
   - Utilizar SQLite para ver las ejecuciones guardadas:
     
     sqlite3 planificador.db
     SELECT * FROM ejecuciones;
     .exit
     

#### Conclusión

Este programa proporciona una solución completa y eficiente para la planificación y ejecución de tareas en entornos controlados, utilizando la potencia de los algoritmos de planificación y la tecnología de contenedores Docker. La combinación de estas herramientas permite una gestión óptima de recursos y una ejecución consistente de tareas, facilitando la automatización y el manejo de múltiples comandos de forma ordenada y eficiente.
