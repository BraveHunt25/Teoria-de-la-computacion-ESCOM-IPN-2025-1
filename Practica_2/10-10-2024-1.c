#include "../Practica_1/strmanipulation.h"
#include <stdio.h>
#include <stdlib.h>
/*
* Hernández Jiménez Erick Yael
* 2023630748
* La práctica deberá contener las funciones:
* - Unión o alternativa
* - Concatenación
* - Potencia de un lenguaje
* Para ello hace falta:
* - Longitud del lenguaje: Lista
* - Imprimir el lenguaje: Lista
* - Extender el lenguaje: En progreso
* - Reiniciar el lenguaje
* - Unión o alternativa
* - Concatenación
* - Potencia de un lenguaje
* - Obtener potencias negativas
* - Estandarizar lambda
*/

void imprimir_lenguaje(char **lenguaje);
char **alargar_lenguaje(char **lenguaje_original);
int longitud_lenguaje(char **lenguaje);


int main(){
    int op;
    char **lenguaje_1 = (char**)malloc(5*sizeof(char*));
    char **lenguaje_2 = (char**)malloc(sizeof(char*));
    *(lenguaje_1+0) = "NULL"; 
    *(lenguaje_1+1) = "Beta"; 
    *(lenguaje_1+2) = "Charly"; 
    *(lenguaje_1+3) = "Delta"; 
    *(lenguaje_1+4) = NULL; 
    printf("La longitud del lenguaje 1 es: %d\n", longitud_lenguaje(lenguaje_1));
    imprimir_lenguaje(lenguaje_1);
    printf("La longitud del lenguaje 2 es: %d\n", longitud_lenguaje(lenguaje_2));
    imprimir_lenguaje(lenguaje_2);
    return 0;
}

void imprimir_lenguaje(char **lenguaje){
    if (lenguaje == NULL){
        printf("\n");
    }
    else{
        for (int i = 0; *(lenguaje+i) != NULL; i++){
            printf("%s\t", *(lenguaje+i));
        }
        printf("\n");
    }
}

char **alargar_lenguaje(char **lenguaje_original){
    char *cadena;
    char **temporal = lenguaje_original;
    printf("Ingresa las palabras que deseas agregar al lenguaje. Usa los espacios ' ' para separarlos y termina de agregar con un salto de linea y un espacio\n");
    while (cadena != "\n")
    {
        int longitud_temporal = longitud_lenguaje(temporal);
        scanf("[^ ]", cadena);
        temporal = realloc(temporal, (longitud_temporal+1) * sizeof(char*));
        *(temporal+longitud_temporal) = (char*)malloc((length(cadena)+1) * sizeof(char));
    }
    temporal = realloc(temporal, (longitud_lenguaje(temporal)+1) * sizeof(char*));
    
}

int longitud_lenguaje(char **lenguaje){
    int longitud;
    for(longitud = 0; *(lenguaje+longitud) != NULL; longitud++){;}
    return longitud;
}