#include <stdio.h>
#include <stdlib.h>
#include "../Practica_2/langman.h"

#define MAX_ESTADOS 100
#define MAX_TRANSICIONES 100
#define MAX_ALFABETO 26
#define MAX_LONGITUD 100

typedef struct {
    int estado_destino;
    char simbolo;
} Transicion;

typedef struct {
    int id;
    int es_final;
    Transicion transiciones[MAX_TRANSICIONES];
    int num_transiciones;
} Estado;

typedef struct {
    Estado estados[MAX_ESTADOS];
    int num_estados;
    int estado_inicial;
    char alfabeto[MAX_ALFABETO];
} Automata;

FILE *leer_texto(char* nombre_archivo, int verboise){
    FILE *archivo = fopen(nombre_archivo, "r");
    if(archivo == NULL){
        perror("Error al encontrar o abrir el archivo");
        return NULL;
    }
    if (verboise == 1){
        printf("Texto leído con éxito\n");
    }
    return archivo;
}

int main(int argc, char const *argv[])
{
    char *nombre_archivo = "automata.txt";
    FILE *archivo = leer_texto(nombre_archivo, 1);
    Automata *automata = (Automata*)malloc(sizeof(Automata)*1);
    char *estados = (char*)malloc(sizeof(char)*MAX_LONGITUD);
    char *alfabeto = (char*)malloc(sizeof(char)*MAX_LONGITUD);
    char *estado_inicial = (char*)malloc(sizeof(char)*MAX_LONGITUD);
    char *estados_finales = (char*)malloc(sizeof(char)*MAX_LONGITUD);
    char *transiciones = (char*)malloc(sizeof(char)*MAX_LONGITUD);
    
    fscanf(archivo, "%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\t]", estados, alfabeto, estado_inicial, estados_finales, transiciones);

    printf("Los estados son: %s\n", estados);
    printf("El alfabeto es: %s\n", alfabeto);
    printf("El estado inicial es: %s\n", estado_inicial);
    printf("Los estados finales son: %s\n", estados_finales);
    printf("Las transiciones son: %s\n", transiciones);

    fclose(archivo);
    free(automata);
    return 0;
}
