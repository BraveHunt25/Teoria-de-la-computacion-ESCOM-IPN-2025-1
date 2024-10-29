#include <stdio.h>
#include <stdlib.h>
#include "../Practica_2/langman.h"
#include "../Practica_1/strmanipulation.h"

#define MAX_ESTADOS 100
#define MAX_TRANSICIONES 100
#define MAX_ALFABETO 26
#define MAX_LONGITUD 100

// PROTOTIPOS DE ESTRCUTURAS
typedef struct Estado Estado;
typedef struct Transicion Transicion;
typedef struct Automata Automata;

// PROTOTIPOS DE FUNCIONES
FILE *leer_texto(char* nombre_archivo, int verboise);
void inicializar_automata(Automata *automata);
void agregar_estado(Automata *automata, char *nombre);
void imprimir_estados(Automata *automata);
void agregar_alfabeto(Automata *automata, char *alfabeto);
void imprimir_alfabeto(Automata *automata);
void agregar_estado_inicial(Automata *automata, char *nombre_estado);

// DEFINICION DE ESTRUCTURAS
struct Transicion{
    /* Estructura con las transiciones con una letra y con el estado destino desde el estado al que se asigne
     * 
     * Estado *estado_destino: Puntero hacia el estado destino al que se accederá con el símbolo
     * char simbolo: Caracter de acceso al estado destino
    */
    Estado *estado_destino;
    char simbolo;
};

struct Estado{
    /* Estructura que define a los estados del autómata
     * 
     * char *nombre: Cadena con nombre del estado
     * int es_final: Propiedad descriptiva que indica si el estado es final (1) o no (!= 1)
     * Transicion transiciones[MAX_TRANSICIONES]: Lista de estructuras de Transicion relacionados al estado
     * int num_transiciones: Propiedad descriptiva que indica el número de trancisiones que contiene asignados
     *                       el estado.
     *                          - 0: No contiene transiciones asignadas
     *                          - <0: No inicializado
     *                          - >0: Contiene transiciones asignadas
    */
    char *nombre;
    int es_final;
    Transicion transiciones[MAX_TRANSICIONES];
    int num_transiciones;
};

struct Automata{
    /* Estructura que contiene al autómata por completo
     * 
     * Estado estados[MAX_ESTADOS]: Arreglo de estados de tamaño MAX_ESTADOS
     * int num_estados: Propiedad descriptiva de los estados que contiene el autómata
     *                  - 0: No contiene estados asignados
     *                  - <0: No inicializado
     *                  - >0: Contiene estados asignados
     * Estado *estado_inicial: Puntero de tipo Estado hacia el estado inicial
     * char alfabeto[MAX_ALFABETO]: Arreglo de caracteres de todos los símbolos pertenecientes al
     *                              alfabeto de este autómata
    */
    Estado estados[MAX_ESTADOS];
    int num_estados;
    Estado *estado_inicial;
    char alfabeto[MAX_ALFABETO];
};

int main(int argc, char const *argv[])
{
    char *nombre_archivo = "automata.txt";
    FILE *archivo = leer_texto(nombre_archivo, 0);
    Automata *automata = (Automata*)malloc(sizeof(Automata));
    char *estados = (char*)malloc(sizeof(char)*MAX_LONGITUD);
    char *alfabeto = (char*)malloc(sizeof(char)*MAX_LONGITUD);
    char *estado_inicial = (char*)malloc(sizeof(char)*MAX_LONGITUD);
    char *estados_finales = (char*)malloc(sizeof(char)*MAX_LONGITUD);
    char *transiciones = (char*)malloc(sizeof(char)*MAX_LONGITUD);
    char nombres[MAX_LONGITUD];
    
    fscanf(archivo, "%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\t]", estados, alfabeto, estado_inicial, estados_finales, transiciones);

    printf("Los estados son: %s\n", estados);
    printf("El alfabeto es: %s\n", alfabeto);
    printf("El estado inicial es: %s\n", estado_inicial);
    printf("Los estados finales son: %s\n", estados_finales);
    printf("Las transiciones son: %s\n", transiciones);

    inicializar_automata(automata);
    printf("El autómata tiene %d estados\n", automata->num_estados);
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
    printf("El autómata tiene los estados:\n");
    imprimir_estados(automata);
    printf("El autómata tiene %d estados\n", automata->num_estados);
    agregar_alfabeto(automata, alfabeto);
    printf("El alfabeto del autómata es:\n");
    imprimir_alfabeto(automata);
    agregar_estado_inicial(automata, estado_inicial);

    fclose(archivo);
    free(automata);
    return 0;
}

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
    
    for (int i = 0; *(nombre + i) != '\0'; i++){
        *(nuevo_estado->nombre + i) = *(nombre + i);
    }
    *(nuevo_estado->nombre + length(nombre)) = '\0';
    nuevo_estado->num_transiciones = 0;

    // Agrega el estado
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
    if (automata != NULL && nombre_estado != NULL){
        for (int i = 0; ; i++)
        {
            ;
        }
        ;
    }
    else if (automata == NULL){
        perror("No se ingresó un autómata válido");
    }
    else if (nombre_estado == NULL){
        perror("No se proporcionó el nombre del estado inicial");
    }
    return;
}