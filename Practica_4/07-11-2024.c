#include <stdio.h>
#include <stdlib.h>
#include "../Practica_3/automata.h"

Estado *combinar_transiciones(Estado *original, char simbolo);
Transicion **mismo_simbolo(Estado *estado, char simbolo);
char *copiar_cadena(char *original);
Transicion *copiar_transicion(Transicion *trasicion_original, Automata *automata_destino, Estado *estado_destino);

int main(){
    char *nombre_archivo = "automata.txt";
    FILE *archivo = fopen(nombre_archivo, "r");
    Automata *automata_fnd = (Automata*)malloc(sizeof(Automata));
    Automata *automata_fd = (Automata*)malloc(sizeof(Automata));
    Transicion **lista_transiciones = NULL;
    char *estados = (char*)malloc(sizeof(char)*MAX_LONGITUD);
    char *alfabeto = (char*)malloc(sizeof(char)*MAX_LONGITUD);
    char *estado_inicial = (char*)malloc(sizeof(char)*MAX_LONGITUD);
    char *estados_finales = (char*)malloc(sizeof(char)*MAX_LONGITUD);
    char *transiciones = (char*)malloc(sizeof(char)*MAX_LONGITUD);
    char nombres[MAX_LONGITUD];
    char palabra_evaluar[MAX_LONGITUD] = " ";
    int j;
    
    // LECTURA DEL AUTÓMATA ORIGINAL
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
    inicializar_automata(automata_fnd);
    // Agrega los estados
    for (int i = 0, j = 0; *(estados + i) != '\0'; i++){
        if(*(estados + i) != ','){
            nombres[j] = *(estados+i);
            j++;
        }
        else{
            nombres[j] = '\0';
            agregar_estado(automata_fnd, nombres);
            j = 0;
        }
    }
    printf("El autómata tiene %d estados\n", automata_fnd->num_estados);
    imprimir_estados(automata_fnd);
    // Agrega el alfabeto
    agregar_alfabeto(automata_fnd, alfabeto);
    printf("El alfabeto del autómata es:\n");
    imprimir_alfabeto(automata_fnd);
    // Indica cuál es el estado original
    agregar_estado_inicial(automata_fnd, estado_inicial);
    printf("El estado inicial del autómata es %s\n", automata_fnd->estado_inicial->nombre);
    // Configura los estados finales
    for (int i = 0, j = 0; *(estados_finales + i) != '\0'; i++){
        if(*(estados_finales + i) != ','){
            nombres[j] = *(estados_finales+i);
            j++;
        }
        else{
            nombres[j] = '\0';
            encontrar_estado(automata_fnd, nombres)->es_final = 1;
            j = 0;
        }
    }
    printf("Los estados finales del autómata son:\n");
    for (int i = 0; i < automata_fnd->num_estados; i++){
        if (automata_fnd->estados[i].es_final == 1){
            printf("%s\n", automata_fnd->estados[i].nombre);
        }
    }
    // Agrega las transiciones
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
        agregar_transicion(automata_fnd, nombre_estado_inicial, simbolo, nombre_estado_final);
        free(nombre_estado_inicial);
        free(nombre_estado_final);
    }
    
    // CREACIÓN DEL SEGUNDO AUTOMATA
    inicializar_automata(automata_fd);
    // Agregamos los estados ya existentes (sin transiciones)
    for (int i = 0; i < automata_fnd->num_estados; i++){
        agregar_estado(automata_fd, (automata_fnd->estados + i)->nombre);
    }
    // Agregamos el alfabeto del autómata original
    for (int i = 0; *(automata_fnd->alfabeto + i) != NULL; i++){
        *(automata_fd->alfabeto + i) = *(automata_fnd->alfabeto + i);
    }
    // Agregamos los estados resultantes de combinar las transiciones originales
    for (int i = 0; i < automata_fnd->num_estados; i++){
        // Por cada símbolo en el abecedario del autómata
        for (int j = 0; *(automata_fd->alfabeto + j) != NULL; j++){
            Transicion **encontradas = mismo_simbolo((automata_fnd->estados + i), *(automata_fd->alfabeto + j));
            // Contamos cuantas transiciones encontró
            int num_transiciones_encontradas = 0;
            for (int k = 0; *(encontradas + k) != NULL; k++){
                num_transiciones_encontradas++;
            }
            //Si no encontramos transiciones con el símbolo...
            if (num_transiciones_encontradas < 1){
                printf("No se encontraron transiciones con %c en %s\n", *(automata_fd->alfabeto + j), (automata_fnd->estados + i)->nombre);
                continue;   // Continuamos con la siguiente letra
            }
            // Si encontramos una transición, copiamos la transición
            else if (num_transiciones_encontradas == 1){
                printf("Se encontró una transición con %c en %s\n", *(automata_fd->alfabeto + j), (automata_fnd->estados + i)->nombre);
                agregar_transicion(automata_fd,                         // Agregamos la transición al autómata finito
                                 (automata_fnd->estados + i)->nombre,   // En el estado de la iteración
                                 *(automata_fd->alfabeto + j),         // Con el símbolo de la iteración
                                 encontrar_estado(                      // Con destino al apuntador del estado encontrado...
                                    automata_fd,                        // En el autómata determinista
                                    (*encontradas)->estado_destino->nombre)->nombre);   // Con el nombre del estado destino al que la transición original apunta
            }
            // Si son más de una, se procede a combinar estados
            else{
                printf("Se encontraron %d transiciones para el estado %s con el caractér %c\n", num_transiciones_encontradas, (automata_fnd->estados + i)->nombre, *(automata_fd->alfabeto + j));
                char *nombre_nuevo = (char*)malloc(sizeof(char));
                *nombre_nuevo = '\0';
                int es_final = 0;
                for (int i = 0; *(encontradas + i) != NULL; i++){
                    nombre_nuevo = concat(nombre_nuevo, (*encontradas + i)->estado_destino->nombre);
                    nombre_nuevo = concat(nombre_nuevo, "-");
                    if ((*encontradas + i)->estado_destino->es_final == 1){
                        es_final = 1;
                    }
                }
                *(nombre_nuevo + length(nombre_nuevo) - 1) = '\0';
                printf("Agregando el estado %s\n", nombre_nuevo);
                agregar_estado(automata_fd, nombre_nuevo);
                // Sustituto forzado de encontrar estado
                Estado *estado_encontrado = NULL;
                for (int i = 0; i < automata_fd->num_estados; i++){
                    char *nombre_estado_actual = automata_fd->estados[i].nombre;
                    // Sustituto forzado de cadenas_iguales
                    int iguales = 1;
                    if (nombre_nuevo == NULL || nombre_estado_actual == NULL || length(nombre_nuevo) != length(nombre_estado_actual)){
                        iguales = 0;
                    }
                    else{
                        for (int posicion = 0; *(nombre_nuevo+posicion) != '\0' && *(nombre_estado_actual+posicion) != '\0'; posicion++)
                        {
                            if (*(nombre_nuevo+posicion) != *(nombre_estado_actual+posicion)){
                                iguales = 0;
                                break;
                            }
                        }
                    }
                    if (iguales == 1) {
                        estado_encontrado = &(automata_fd->estados[i]);
                        break;
                    }
                }
                estado_encontrado->es_final = es_final;
            }        
        }
    }
    free(automata_fnd);
    free(automata_fd);
    return 0;
}

Transicion **mismo_simbolo(Estado *estado, char simbolo){
    Transicion **transiciones_encontradas = (Transicion**)malloc(sizeof(Transicion*)*(estado->num_transiciones + 1));
    *transiciones_encontradas = NULL;
    int j = 0;
    for (int i = 0; i < estado->num_transiciones; i++){
        if ((estado->transiciones + i)->simbolo == simbolo){
            *(transiciones_encontradas + j) = (Transicion*)malloc(sizeof(Transicion));
            *(transiciones_encontradas + j) = (estado->transiciones + i);
            j++;
        }
    }
    *(transiciones_encontradas + j + 1) = NULL;
    return transiciones_encontradas;
}

Estado *combinar_transiciones(Estado *original, char simbolo){
    Transicion **transiciones_encontradas = mismo_simbolo(original, simbolo);
    int num_transiciones_encontradas = 0;
    for (int i = 0; *(transiciones_encontradas + i) != NULL; i++){
        num_transiciones_encontradas++;
    }
    printf("Se encontraron %d transiciones\n", num_transiciones_encontradas);
    Estado *resultado = NULL;
    if(num_transiciones_encontradas > 1){
        char *nombre_nuevo = (char*)malloc(sizeof(char));
        *nombre_nuevo = '\0';
        int es_final = 0;
        for (int i = 0; *(transiciones_encontradas + i) != NULL; i++){
            nombre_nuevo = concat(nombre_nuevo, (*transiciones_encontradas + i)->estado_destino->nombre);
            nombre_nuevo = concat(nombre_nuevo, "-");
            if ((*transiciones_encontradas + i)->estado_destino->es_final == 1){
                es_final = 1;
            }
        }
        *(nombre_nuevo + length(nombre_nuevo) - 1) = '\0';
        resultado = (Estado*)malloc(sizeof(Estado));
        resultado->nombre = nombre_nuevo;
        resultado->es_final = es_final;
        resultado->num_transiciones = 0;
    }
    if (num_transiciones_encontradas == 1){
        resultado = (*transiciones_encontradas)->estado_destino;
    }
    return resultado;
}

char *copiar_cadena(char *original){
    int longitud = length(original);
    char *nueva = (char*)malloc(sizeof(char)*(longitud + 1));
    for (int i = 0; i < longitud; i++){
        *(nueva + i) = *(original + i);
    }
    *(nueva + longitud) = '\0';
    return nueva;
}

Transicion *copiar_transicion(Transicion *trasicion_original, Automata *automata_destino, Estado *estado_destino){
    Transicion *nueva = inicializar_transicion(estado_destino, trasicion_original->simbolo);
    return nueva;
}