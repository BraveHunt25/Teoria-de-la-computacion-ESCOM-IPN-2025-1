#include <stdio.h>
#include <stdlib.h>
#include "../Practica_2/langman.h"
#include "../Practica_1/stringmanipulation.h"
#include "../Practica_3/automata.h"
#include "../Refuerzo/List_Str_.h"
#include "../Refuerzo/Set_Str_.h"

#define MAX_CONJUNTOS 100

Set_Str_ *cerradura_epsilon(Estado *inicial, char *epsilon);
Set_Str_ *ir_a(Automata *automata, Set_Str_ *conjunto, char *simbolo, char *epsilon);

Set_Str_ *Set_in_List_(Set_Str_ **list, Set_Str_ *set);
char *List_Set_Str__str_(Set_Str_ **lista);
void List_Set_Str__add_(Set_Str_ ***lista, Set_Str_ *elemento);
void thompson_states_gen(Automata *afn, Automata *afd, Set_Str_ ***equivalencias, Set_Str_ *conjunto, char *epsilon);

int main(){
    char *nombre_archivo = "(BorBA)A.txt";
    FILE *archivo = leer_texto(nombre_archivo, 0);
    Automata *automata = (Automata*)malloc(sizeof(Automata));
    char *estados = (char*)malloc(sizeof(char)*MAX_LONGITUD);
    char *alfabeto = (char*)malloc(sizeof(char)*MAX_LONGITUD);
    char *estado_inicial = (char*)malloc(sizeof(char)*MAX_LONGITUD);
    char *estados_finales = (char*)malloc(sizeof(char)*MAX_LONGITUD);
    char *transiciones = (char*)malloc(sizeof(char)*MAX_LONGITUD);
    char nombres[MAX_LONGITUD];
    //char palabra_evaluar[MAX_LONGITUD] = " ";
    
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
        //free(nombre_estado_inicial);
        //free(nombre_estado_final);
    }
    printf("El autómata tiene las transiciones cargadas\n");
    fclose(archivo);
    /*
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
    */

    /* Generación del automata de Thompson*/
    // Inicialización sin estados finales
    Automata *Thompson = (Automata*)malloc(sizeof(Automata));
    Thompson->alfabeto = __str__copy(automata->alfabeto);
    Thompson->num_estados = 0;
    Set_Str_ **equivalencias = (Set_Str_**)calloc(1, sizeof(Set_Str_*));
    List_Set_Str__add_(&equivalencias, cerradura_epsilon(automata->estado_inicial, "E"));
    printf("%s", List_Set_Str__str_(equivalencias));
    printf("------\n");
    agregar_estado(Thompson, &(*(*equivalencias + 0)->alias));
    printf("------\n");
    agregar_estado_inicial(Thompson, (*equivalencias + 0)->alias);
    thompson_states_gen(automata, Thompson, &equivalencias, (*equivalencias + 0), "E");
    imprimir_estados(Thompson);
    //free(automata);
    return 0;
}

/* Recibe un apuntador `Estado` y otro `char`. A partir del estado inicial, busca todos los estados a los que se puede llegar con el `epsilon` ingresado. Regresa un apuntador `Set_Str_` con los nombres de los estados que se alcanzan. */
Set_Str_ *cerradura_epsilon(Estado *inicial, char* epsilon){
    printf("trace:cerradura_epsilon:ini\n");
    char *prefijo = (char*)malloc(sizeof(char)*3);
    prefijo[0] = 'C';
    prefijo[1] = 'E';
    prefijo[2] = '\0';
    char *concatenado = __str__concat(prefijo, inicial->nombre);
    Set_Str_ *resultado = Set_Str__init_(inicial->nombre, concatenado);
    for (int i = 0; i < inicial->num_transiciones; i++){
        if(__str__eq(&(inicial->transiciones[i].simbolo), epsilon)){
            Set_Str__add_(resultado, inicial->transiciones[i].estado_destino->nombre);
            Set_Str_ *temp = cerradura_epsilon(inicial->transiciones[i].estado_destino, epsilon);
            resultado = Set_Str__union_(resultado, temp, __str__concat(prefijo, inicial->nombre));
            //free(temp);
        }
    }
    //free(prefijo);
    printf("trace:cerradura_epsilon:out\n");
    return resultado;
}

/* Recibe un apuntador `Automata`, uno `Set_Str_` y dos `char`. Ejecuta el algoritmo `ir_a`, desde los estados del `conjunto` que se encuentran en el `automata` con el `simbolo`, ejecutando luego la cerradura épsilon con el símblo `epsilon`. Regresa un apuntador `Set_Str_` con el nombre de los estados que genera este algoritmo. */
Set_Str_ *ir_a(Automata *automata, Set_Str_ *conjunto, char *simbolo, char *epsilon){
    printf("trace:ir_a:ini\n");
    Set_Str_ *resultado = NULL;
    for (int i = 0; i < automata->num_estados; i++){
        if(List_Str__in_(conjunto->contenido, automata->estados[i].nombre)){
            for (int j = 0; j < automata->estados[i].num_transiciones; j++){
                if (automata->estados[i].transiciones[j].simbolo == *simbolo){
                    if(!resultado){
                        resultado = cerradura_epsilon(automata->estados[i].transiciones[j].estado_destino, epsilon);
                    }
                    else{
                        Set_Str_ *temp = cerradura_epsilon(automata->estados[i].transiciones[j].estado_destino, epsilon);    
                        resultado = Set_Str__union_(resultado, temp, resultado->alias);
                        //free(temp);
                    }
                }
            }    
        }
    }
    printf("trace:ir_a:out\n");
    return resultado;
}


void thompson_states_gen(Automata *afn, Automata *afd, Set_Str_ ***equivalencias, Set_Str_ *conjunto, char *epsilon){
    printf("trace:thompson_states_gen:ini\n");
    for (int i = 0; i < __str__len(afd->alfabeto); i++){
        char letra = afd->alfabeto[i];
        char simbolo[2];
        simbolo[0] = letra;
        simbolo[1] = '\0';
        Set_Str_ *ir_a_temporal = ir_a(afn, conjunto, simbolo, epsilon);
        if (!Set_in_List_(*equivalencias, ir_a_temporal)){
            List_Set_Str__add_(equivalencias, ir_a_temporal);
            agregar_estado(afd, ir_a_temporal->alias);
            agregar_transicion(afd, conjunto->alias, *(afd->alfabeto + i), ir_a_temporal->alias);
            thompson_states_gen(afn, afd, equivalencias, ir_a_temporal, epsilon);
        }
    }
    printf("trace:thompson_states_gen:out\n");
    return;    
}

void List_Set_Str__add_(Set_Str_ ***lista, Set_Str_ *elemento){
    int i = 0;
    while (*(*lista + i) != NULL){
        i++;
    }
    Set_Str_ **temp = (Set_Str_**)realloc(*lista, sizeof(Set_Str_*)*(i+2));
    while(!temp){
        temp = (Set_Str_**)calloc((i+2), sizeof(Set_Str_*));
        for (int j = 0; j < i; j++){
            *(temp + j) = *(*lista + j);
        }
        //free(*lista);
    }
    *lista = temp;
    *(*lista + i) = elemento;
    *(*lista + i + 1) = NULL;
    return;
}

char *List_Set_Str__str_(Set_Str_ **lista){
    printf("trace:List_Set_Str__str_:ini\n");
    char *resultado = "";
    int i = 0;
    while (*(lista + i) != NULL){
        resultado = __str__concat(resultado, __str__concat(Set_Str__str_(*(lista + i)), "\n"));
        i++;
    }
    printf("trace:List_Set_Str__str_:out\n");
    return resultado;
}

/* Recibe un doble apuntador `Set_Str_` y uno simple `Set_Str_`. Si el `set` ya se encuentra en `list`, regresa el apuntador del elemento en lista, de lo contrario, regresa NULL. */
Set_Str_ *Set_in_List_(Set_Str_ **list, Set_Str_ *set){
    Set_Str_ *resultado = NULL;
    int i = 0;
    while (*(list + i)){
        if (Set_Str__eq__(set, *(list + i))){
            resultado = *(list + i);
            break;
        }
        i++;
    }
    return resultado;
}