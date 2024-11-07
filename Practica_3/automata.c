#include <stdio.h>
#include <stdlib.h>
#include "./automata.h"

#define MAX_ESTADOS 100
#define MAX_TRANSICIONES 100
#define MAX_ALFABETO 26
#define MAX_LONGITUD 100

// FUNCIONES
FILE *leer_texto(char* nombre_archivo, int verboise){
    /* Encapsula el proceso de abrir un archivo txt en modo lectura localizada en la misma carpeta que el código fuente;
     * asignar su contenido al puntero de tipo FILE.
     * 
     * char* nombre_archivo: cadena con el nombre del archivo por leer.
     * int verboise: entero con comportamiento booleano que imprime el estado exitoso de la lectura (1)
     *               o la omite (!=1)
    */
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

void inicializar_automata(Automata *automata){
    automata->num_estados = 0;
    automata->alfabeto = (char*)malloc(sizeof(char)*MAX_ALFABETO);
    automata->estados = (Estado*)malloc(sizeof(Estado)*MAX_ESTADOS);
    return;
}

void agregar_estado(Automata *automata, char *nombre){
    /* Inicializa un Estado sin transiciones y lo agrega al autómata descrito 
     *
     * Automata *automata: Dirección del autómata al que se agregará el estado
     * char *nombre: Nombre del estado que se agregará
    */
    // Inicializa el estado 
    Estado *nuevo_estado = (Estado*)malloc(sizeof(Estado));
    nuevo_estado->es_final = 0;
    nuevo_estado->nombre = (char*)malloc(sizeof(char)*(length(nombre)+1));
    nuevo_estado->num_transiciones = 0;
    
    for (int i = 0; *(nombre + i) != '\0'; i++){
        *(nuevo_estado->nombre + i) = *(nombre + i);
    }
    *(nuevo_estado->nombre + length(nombre)) = '\0';
    nuevo_estado->num_transiciones = 0;

    *(automata->estados + automata->num_estados) = *nuevo_estado;
    automata->num_estados++;
    return;
}

void imprimir_estados(Automata *automata){
    if (automata != NULL){
        for (int i = 0; i < automata->num_estados; i++){
            printf("%s\n", automata->estados[i].nombre);
        }
    }
    return;
}

void agregar_alfabeto(Automata *automata, char *alfabeto){
    for (int i = 0, j = 0; *(alfabeto + i) != '\0'; i++){
        if(*(alfabeto + i) != ','){
            automata->alfabeto[j] = *(alfabeto+i);
            j++;
        }
    }
}

void imprimir_alfabeto(Automata *automata){
    int i;
    for (i = 0; length(automata->alfabeto)-1 > i ; i++){
        printf("%c,", *(automata->alfabeto + i));
    }
    printf("%c\n", *(automata->alfabeto + i));
}

void agregar_estado_inicial(Automata *automata, char *nombre_estado){
    Estado *estado_encontrado = NULL;
    if (automata != NULL && nombre_estado != NULL){
        for (int i = 0; i < automata->num_estados; i++){
            char *nombre_estado_actual = automata->estados[i].nombre;
            if (cadenas_iguales(nombre_estado, nombre_estado_actual) == 1) {
                estado_encontrado = &(automata->estados[i]);
                break;
            }
        }
        if (estado_encontrado->nombre == NULL){
            perror("No se encontró el estado");
        }
        else{
            automata->estado_inicial = estado_encontrado;
        }  
    }
    else if (automata == NULL){
        perror("No se ingresó un autómata válido");
    }
    else if (nombre_estado == NULL){
        perror("No se proporcionó el nombre del estado inicial");
    }
    return;
}

Transicion *inicializar_transicion(Estado* estado_destino, char simbolo){
    Transicion *nueva_transicion = (Transicion*)malloc(sizeof(Transicion));
    nueva_transicion->estado_destino = estado_destino;
    nueva_transicion->simbolo = simbolo;
    return nueva_transicion;
}

void agregar_transicion(Automata *automata, char *estado_inicial, char simbolo, char *estado_final){
    Estado *estado_inicial_encontrado = NULL;
    Estado *estado_final_encontrado = NULL;
    Transicion *nueva_transicion = NULL;
    if (automata != NULL && estado_inicial != NULL && caracter_en_alfabeto(automata, simbolo) == 1 && estado_final != NULL){
        estado_inicial_encontrado = encontrar_estado(automata, estado_inicial);
        estado_final_encontrado = encontrar_estado(automata, estado_final);
        if (estado_inicial_encontrado->nombre == NULL || estado_final_encontrado->nombre == NULL){
            perror("No se encontró el estado");
        }
        else{
            nueva_transicion = inicializar_transicion(estado_final_encontrado, simbolo);
            *(estado_inicial_encontrado->transiciones + estado_inicial_encontrado->num_transiciones) = *(nueva_transicion);
            estado_inicial_encontrado->num_transiciones++;
        }  
    }
    else if (automata == NULL){
        perror("No se ingresó un autómata válido");
    }
    else if (estado_inicial == NULL){
        perror("No se proporcionó el nombre del estado inicial");
    }
    else if (caracter_en_alfabeto(automata, simbolo) == 0){
        perror("No se proporcionó el símbolo");
    }
    else if (estado_final == NULL){
        perror("No se proporcionó el estado final");
    }
    return;
}

Estado *encontrar_estado(Automata *automata, char *nombre){
    Estado *estado_encontrado = NULL;
    for (int i = 0; i < automata->num_estados; i++){
        char *nombre_estado_actual = automata->estados[i].nombre;
        if (cadenas_iguales(nombre, nombre_estado_actual) == 1) {
            estado_encontrado = &(automata->estados[i]);
            break;
        }
    }
    return estado_encontrado;
}

void agregar_estado_final(Automata *automata, char *nombre_estado){
    Estado *estado_encontrado = encontrar_estado(automata, nombre_estado);
    estado_encontrado->es_final = 1;
    return;
}

int caracter_en_alfabeto(Automata *automata, char c){
    int en_alfabeto = 0;
    for (int i = 0; *(automata->alfabeto + i) != '\0'; i++){
        if (*(automata->alfabeto + i) == c){
            en_alfabeto = 1;
            break;
        }
    }
    return en_alfabeto;
}

char *validacion(Automata *automata, Estado *estado_actual, char *palabra) {
    if (*palabra == '\0') {
        if (estado_actual->es_final == 1) {
            return concat(estado_actual->nombre, ".");
        } else {
            char *resultado = (char*)malloc(sizeof(char));
            *resultado = '\0';
            return resultado;
        }
    } else {
        for (int i = 0; i < estado_actual->num_transiciones; i++) {
            Transicion *transicion = &estado_actual->transiciones[i];
            
            if (transicion->simbolo == *palabra) {
                char *resultado_parcial = validacion(automata, transicion->estado_destino, palabra + 1);
                
                if (*resultado_parcial != '\0') {
                    char *s_paso = concat(estado_actual->nombre, ",");
                    char *resultado = concat(s_paso, resultado_parcial);
                    free(s_paso);
                    free(resultado_parcial);
                    return resultado;
                }
                free(resultado_parcial);
            }
        }
        char *resultado = (char*)malloc(sizeof(char));
        *resultado = '\0';
        return resultado;
    }
}

Transicion *encontrar_transicion(Estado *estado, char simbolo){
    Transicion *resultado = NULL;
    if (estado != NULL && simbolo != '\0'){
        for (int i = 0; i < estado->num_transiciones; i++){
            if(estado->transiciones[i].simbolo == simbolo){
                resultado = estado->transiciones + i;
                break;
            }
        }
    }
    return resultado;
}