#ifndef LANGMAN
#define LANGMAN

#include <stdio.h>
#include <stdlib.h>
#include "../Practica_1/strmanipulation.h"

void imprimir_lenguaje(char **lenguaje);
int cadenas_iguales(char *palabra_1, char* palabra_2);
int longitud_lenguaje(char **lenguaje);
int elevar_num(int base, int exponente);
char **concatenar_lenguajes(char **lenguaje_1, char **lenguaje_2);
char **expandir_lenguaje(char **lenguaje_original, char *nueva_palabra, int long_max_palabra);
char **invertir_lenguaje(char **lenguaje);
char **elevar_potencia_lenguaje(char** lenguaje, int potencia);
char **union_lenguajes(char **lenguaje_1, char **lenguaje_2);

#endif