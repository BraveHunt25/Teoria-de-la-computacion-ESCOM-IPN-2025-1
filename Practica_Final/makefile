PROGRAMA = a
FUENTES = final.c ../Refuerzo/Set_Str_.c ../Refuerzo/List_Str_.c ../Practica_3/automata.c ../Practica_2/langman.c ../Practica_1/stringmanipulation.c ../cadenas/cadenas.c
CABECERAS = $(FUENTES:.c=.h)
CC = gcc
DB = gdb
CFLAGS = -Wall -Wextra -std=c99 -I../Refuerzo -I../Practica_1 -I../Practica_2 -I../Practica_3 -I../cadenas -g -O0

all: $(PROGRAMA)

$(PROGRAMA): $(FUENTES)
	$(CC) $(CFLAGS) $(FUENTES) -o $(PROGRAMA).out

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJETOS)

info:
	@echo "FUENTES: $(FUENTES)"
	@echo "CABECERAS: $(CABECERAS)"

debug: $(OBJETOS)
	$(CC) $(OBJETOS) -o $(PROGRAMA).out