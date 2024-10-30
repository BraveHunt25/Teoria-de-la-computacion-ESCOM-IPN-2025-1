#include <stdio.h>
#include <stdlib.h>
#include "../Practica_2/langman.h"
#include "../Practica_1/stringmanipulation.h"

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
void agregar_transicion(Automata *automata, char *estado_inicial, char simbolo, char *estado_final);
Transicion *inicializar_transicion(Estado* estado_destino, char simbolo);
Estado *encontrar_estado(Automata *automata, char *nombre);
void agregar_estado_final(Automata *automata, char *nombre_estado);
int caracter_en_alfabeto(Automata *automata, char c);
char *validacion(Automata *automata, Estado *estado_actual, char *palabra);
Transicion *encontrar_transicion(Estado *estado, char simbolo);

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
    Estado *estados;
    int num_estados;
    Estado *estado_inicial;
    char *alfabeto;
};

int main(){
    char *nombre_archivo = "automata.txt";
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

char *validacion(Automata *automata, Estado *estado_actual, char *palabra){
    char *resultado = NULL;
    if (*palabra == '\0'){
        if (estado_actual->es_final == 1){
            resultado = concat(estado_actual->nombre, ".");
        }
        else{
            resultado = (char*)malloc(sizeof(char));
            *(resultado + 0) = '\0';
        }
    }
    else{
        char *s_estado = concat(estado_actual->nombre, ",");
        char *s_simbolo = (char*)malloc(sizeof(char)*3);
        *(s_simbolo + 0) = *palabra;
        *(s_simbolo + 1) = ',';
        *(s_simbolo + 2) = '\0';
        char *s_paso = concat(s_estado, s_simbolo);
        char *sig_simbolo = (char*)malloc(sizeof(char)*2);
        *(sig_simbolo + 0) = *palabra;
        *(sig_simbolo + 1) = '\0';
        Transicion *siguiente_estado = encontrar_transicion(estado_actual, *sig_simbolo);
        if (siguiente_estado == NULL){
            resultado = (char*)malloc(sizeof(char));
            *resultado = '\0';
        }
        else{
            resultado = concat(s_paso, validacion(automata, siguiente_estado->estado_destino, palabra + 1));
            if (*(resultado + length(resultado) - 1) == ',');{
                free(resultado);
                resultado = (char*)malloc(sizeof(char)*2);
                *(resultado + 0) = '.';
                *(resultado + 1) = '\0';
            }
            
        }
    }
    return resultado;
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