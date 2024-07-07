CC = gcc
CFLAGS = -Wall -g
LIBS = -lsqlite3

all: contenedorizador

contenedorizador: main.o gestor_contenedores.o planificador.o base_datos.o
	$(CC) $(CFLAGS) -o contenedorizador main.o gestor_contenedores.o planificador.o base_datos.o $(LIBS)

main.o: main.c gestor_contenedores.h planificador.h base_datos.h
	$(CC) $(CFLAGS) -c main.c

gestor_contenedores.o: gestor_contenedores.c gestor_contenedores.h
	$(CC) $(CFLAGS) -c gestor_contenedores.c

planificador.o: planificador.c planificador.h
	$(CC) $(CFLAGS) -c planificador.c

base_datos.o: base_datos.c base_datos.h
	$(CC) $(CFLAGS) -c base_datos.c

clean:
	rm -f *.o contenedorizador
