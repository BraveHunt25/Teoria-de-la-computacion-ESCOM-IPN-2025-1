#ifndef _AUTOMATA_
#define _AUTOMATA_

#include <stdio.h>
#include <stdlib.h>
#include "../Practica_1/stringmanipulation.h"
#include "../Practica_2/langman.h"
#include "../cadenas/cadenas.h"

#define MAX_ESTADOS 100
#define MAX_TRANSICIONES 100
#define MAX_ALFABETO 26
#define MAX_LONGITUD 100

/* Estructura que define a los estados del autómata
 * 
 * char *nombre: Cadena con nombre del estado
 * 
 * int es_final: Propiedad descriptiva que indica si el estado es final (1) o no (!= 1)
 * 
 * Transicion transiciones[MAX_TRANSICIONES]: Lista de estructuras de Transicion relacionados al estado
 * 
 * int num_transiciones: Propiedad descriptiva que indica el número de trancisiones que contiene asignados el estado.
 *                          - 0: No contiene transiciones asignadas
 *                          - <0: No inicializado
 *                          - >0: Contiene transiciones asignadas
*/
typedef struct Estado Estado;
/* Estructura con las transiciones con una letra y con el estado destino desde el estado al que se asigne
 * 
 * Estado *estado_destino: Puntero hacia el estado destino al que se accederá con el símbolo
 * 
 * char simbolo: Caracter de acceso al estado destino
*/
typedef struct Transicion Transicion;
/* Estructura que contiene al autómata por completo
 * 
 * Estado estados[MAX_ESTADOS]: Arreglo de estados de tamaño MAX_ESTADOS
 * 
 * Estado *estado_inicial: Puntero de tipo Estado hacia el estado inicial
 * 
 * char alfabeto[MAX_ALFABETO]: Arreglo de caracteres de todos los símbolos pertenecientes al alfabeto de este autómata
 * 
 * int num_estados: Propiedad descriptiva de los estados que contiene el autómata
 *                  - 0: No contiene estados asignados
 *                  - <0: No inicializado
 *                  - >0: Contiene estados asignados
*/
typedef struct Automata Automata;

// DEFINICION DE ESTRUCTURAS
struct Transicion{
    /* Estructura con las transiciones con una letra y con el estado destino desde el estado al que se asigne
     * 
     * Estado *estado_destino: Puntero hacia el estado destino al que se accederá con el símbolo
     * 
     * char simbolo: Caracter de acceso al estado destino
    */
    Estado *estado_destino;
    char simbolo;
};

struct Estado{
    /* Estructura que define a los estados del autómata
     * 
     * char *nombre: Cadena con nombre del estado
     * 
     * int es_final: Propiedad descriptiva que indica si el estado es final (1) o no (!= 1)
     * 
     * Transicion transiciones[MAX_TRANSICIONES]: Lista de estructuras de Transicion relacionados al estado
     * 
     * int num_transiciones: Propiedad descriptiva que indica el número de trancisiones que contiene asignados el estado.
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
    Estado *estados;
    int num_estados;
    Estado *estado_inicial;
    char *alfabeto;
};


// PROTOTIPOS DE FUNCIONES
FILE *leer_texto(char* nombre_archivo, int verboise);
void inicializar_automata(Automata *automata);
void agregar_estado(Automata *automata, char *nombre);
void imprimir_estados(Automata *automata);
void agregar_alfabeto(Automata *automata, char *alfabeto);
void imprimir_alfabeto(Automata *automata);
void agregar_estado_inicial(Automata *automata, char *nombre_estado);
void agregar_transicion(Automata *automata, char *estado_inicial, char simbolo, char *estado_final);
Transicion *inicializar_transicion(Estado* estado_destino, char simbolo);
Estado *encontrar_estado(Automata *automata, char *nombre);
void agregar_estado_final(Automata *automata, char *nombre_estado);
int caracter_en_alfabeto(Automata *automata, char c);
char *validacion(Automata *automata, Estado *estado_actual, char *palabra);
Transicion *encontrar_transicion(Estado *estado, char simbolo);

#endif // _AUTOMATA_
