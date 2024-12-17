#include <stdio.h>
#include <stdlib.h>
#include "../Practica_2/langman.h"
#include "../Practica_1/stringmanipulation.h"
#include "./automata.h"

int main(){
    char *nombre_archivo = "automata_2.txt";
    FILE *archivo = leer_texto(nombre_archivo, 0);
    Automata *automata = (Automata*)malloc(sizeof(Automata));
    char *estados = (char*)malloc(sizeof(char)*MAX_LONGITUD);
    char *alfabeto = (char*)malloc(sizeof(char)*MAX_LONGITUD);
    char *estado_inicial = (char*)malloc(sizeof(char)*MAX_LONGITUD);
    char *estados_finales = (char*)malloc(sizeof(char)*MAX_LONGITUD);
    char *transiciones = (char*)malloc(sizeof(char)*MAX_LONGITUD);
    char nombres[MAX_LONGITUD];
    char palabra_evaluar[MAX_LONGITUD] = " ";
    int j;
    
    // INICIALIZACIÓN
    fscanf(archivo, "%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\t]", estados, alfabeto, estado_inicial, estados_finales, transiciones);

    for (int i = 0; *(estado_inicial + i) != '\0'; i++){
        if(*(estado_inicial + i) == ','){
            *(estado_inicial + i) = '\0';
        }
    }
    for (int i = 0; *(transiciones+i) != '\0'; i++){
        if (*(transiciones+i) == '\n'){
            *(transiciones+i) = ',';
        }
    }
    inicializar_automata(automata);
    for (int i = 0, j = 0; *(estados + i) != '\0'; i++){
        if(*(estados + i) != ','){
            nombres[j] = *(estados+i);
            j++;
        }
        else{
            nombres[j] = '\0';
            agregar_estado(automata, nombres);
            j = 0;
        }
    }
    printf("El autómata tiene %d estados\n", automata->num_estados);
    imprimir_estados(automata);
    agregar_alfabeto(automata, alfabeto);
    printf("El alfabeto del autómata es:\n");
    imprimir_alfabeto(automata);
    agregar_estado_inicial(automata, estado_inicial);
    printf("El estado inicial del autómata es %s\n", automata->estado_inicial->nombre);
    for (int i = 0, j = 0; *(estados_finales + i) != '\0'; i++){
        if(*(estados_finales + i) != ','){
            nombres[j] = *(estados_finales+i);
            j++;
        }
        else{
            nombres[j] = '\0';
            encontrar_estado(automata, nombres)->es_final = 1;
            j = 0;
        }
    }
    printf("Los estados finales del autómata son:\n");
    for (int i = 0; i < automata->num_estados; i++){
        if (automata->estados[i].es_final == 1){
            printf("%s\n", automata->estados[i].nombre);
        }
    }
    
    for (int i = 0; *(transiciones+i) != '\0'; i++){
        char *nombre_estado_inicial = (char*)malloc(sizeof(char)*20);
        int j = 0;
        while (*(transiciones+i) != ','){
            *(nombre_estado_inicial + j) = *(transiciones + i);
            i++;
            j++;
        }
        i++;
        char simbolo = *(transiciones + i);
        i+=2;
        j = 0;
        char *nombre_estado_final = (char*)malloc(sizeof(char)*20);
        while (*(transiciones+i) != ','){
            *(nombre_estado_final + j) = *(transiciones + i);
            i++;
            j++;
        }
        agregar_transicion(automata, nombre_estado_inicial, simbolo, nombre_estado_final);
        free(nombre_estado_inicial);
        free(nombre_estado_final);
    }
    printf("El autómata tiene las transiciones cargadas\n");
    fclose(archivo);
    while (1) {
        printf("Ingresa la cadena a evaluar (o ',' para salir): \n");
        scanf("%[^\n]", palabra_evaluar);
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        if (cadenas_iguales(palabra_evaluar, ",")) {
            printf("Saliendo...\n");
            break;
        }
        printf("Se evaluará '%s'\n", palabra_evaluar);
        printf("%s\n", validacion(automata, automata->estado_inicial, palabra_evaluar));
    }

    free(automata);
    return 0;
}