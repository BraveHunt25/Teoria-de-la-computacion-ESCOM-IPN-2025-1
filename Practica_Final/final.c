#include <stdio.h>
#include <stdlib.h>
#include "../Practica_2/langman.h"
#include "../Practica_1/stringmanipulation.h"
#include "../Practica_3/automata.h"
#include "../Refuerzo/List_Str_.h"
#include "../Refuerzo/Set_Str_.h"

/*
NOTA: PARA REUTILIZAR EL ARCHIVO DEL AUTÓMATA ES NECESARIO REEMPLAZAR EL ÚLTIMO SALTO DE LÍNEA POR UNA COMA ','
*/

Set_Str_ *cerradura_epsilon(Estado *inicial, char *epsilon);
Set_Str_ *ir_a(Automata *automata, Set_Str_ *conjunto, char *simbolo, char *epsilon);

Set_Str_ *Set_in_List_(Set_Str_ **list, Set_Str_ *set);
char *List_Set_Str__str_(Set_Str_ **lista);
void List_Set_Str__add_(Set_Str_ ***lista, Set_Str_ *elemento);
void thompson_states_gen(Automata *afn, Automata *afd, Set_Str_ ***equivalencias, Set_Str_ *conjunto, char *epsilon);
void asignar_finales(Automata* afd, Automata *afn, Set_Str_ **equivalencias);

int main(){
    char *nombre_archivo = "b.txt";//"XYorZ.txt"; //"MN(OorP).txt";//"(BorBA)A.txt";
    FILE *archivo = leer_texto(nombre_archivo, 0);
    FILE *conversion = NULL;
    Automata *automata = (Automata*)malloc(sizeof(Automata));
    char *estados = (char*)malloc(sizeof(char)*MAX_LONGITUD);
    char *alfabeto = (char*)malloc(sizeof(char)*MAX_LONGITUD);
    char *estado_inicial = (char*)malloc(sizeof(char)*MAX_LONGITUD);
    char *estados_finales = (char*)malloc(sizeof(char)*MAX_LONGITUD);
    char *transiciones = (char*)malloc(sizeof(char)*MAX_LONGITUD);
    char nombres[MAX_LONGITUD];
    char palabra_evaluar[MAX_LONGITUD] = " ";
    
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
        char *nombre_estado_inicial = (char*)calloc(20, sizeof(char));
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
        char *nombre_estado_final = (char*)calloc(20, sizeof(char));
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
    free(estados);
    free(estado_inicial);
    free(estados_finales);
    free(transiciones);
    fclose(archivo);

    /* Generación del automata de Thompson*/
    // Inicialización sin estados finales
    Automata *Thompson = (Automata*)malloc(sizeof(Automata));
    inicializar_automata(Thompson);
    Thompson->alfabeto = __str__copy(automata->alfabeto);
    Thompson->num_estados = 0;
    Set_Str_ **equivalencias = (Set_Str_**)calloc(20, sizeof(Set_Str_*));
    List_Set_Str__add_(&equivalencias, cerradura_epsilon(automata->estado_inicial, "E"));
    /*
    char *impresion = List_Set_Str__str_(equivalencias);
    printf("%s", impresion);
    free(impresion);
    */

    Estado *nuevo_estado_inicial = (Estado*)malloc(sizeof(Estado));
    nuevo_estado_inicial->nombre = __str__copy((*equivalencias + 0)->alias); 
    nuevo_estado_inicial->es_final = 0;
    nuevo_estado_inicial->num_transiciones = 0;

    Thompson->estados[0] = *nuevo_estado_inicial;
    Thompson->num_estados = 1;
    Thompson->estado_inicial = Thompson->estados;
    imprimir_estados(Thompson);
    agregar_estado_inicial(Thompson, (*equivalencias + 0)->alias);
    
    thompson_states_gen(automata, Thompson, &equivalencias, (*equivalencias + 0), "E");
    printf("El autómata se ha convertido con éxito\nSus estados son...\n");
    imprimir_estados(Thompson);
    asignar_finales(Thompson, automata, equivalencias);
    char *impresion = List_Set_Str__str_(equivalencias);
    /*
    printf("Las equivalencias son:\n%s", impresion);
    printf("Los finales son:\n");
    for (int i = 0; i < Thompson->num_estados; i++){
        if ((Thompson->estados + i)->es_final == 1){
            printf("%s\n", (Thompson->estados + i)->nombre);
        }
    }
    */
    printf("Las transiciones son:\n");
    for (int i = 0; i < Thompson->num_estados; i++){
        printf("%s\n", (Thompson->estados + i)->nombre);
        for (int j = 0; j < (Thompson->estados + i)->num_transiciones; j++){
            printf("%s(%c)->%s\n", (Thompson->estados + i)->nombre, ((Thompson->estados + i)->transiciones + j)->simbolo, ((Thompson->estados + i)->transiciones + j)->estado_destino->nombre);
        }   
    }
    
    /* MENÚ */
    int opcion = 0;
    while (opcion < 3) {
        printf("El autómata tiene de alfabeto\n");
        imprimir_alfabeto(Thompson);
        printf("Indica la opción que deseas ejecutar:\n1. Validar una cadena en el autómata\n2. Exportar el autómata convertido a determinista\n3. Salir\n");
        scanf("%d", &opcion);
        while (getchar() != '\n');
        switch (opcion){
            case 1:
                palabra_evaluar[0] = '\0';
                printf("Ingresa la cadena a evaluar: \n");
                scanf("%[^\n]", palabra_evaluar);
                while (getchar() != '\n');
                printf("Se evaluará '%s'\n", palabra_evaluar);
                printf("%s\n", validacion(Thompson, Thompson->estado_inicial, palabra_evaluar));
                palabra_evaluar[0] = '\0';
                break;
            case 2:
                /* Exportación de autómata */
                conversion = fopen("Thompson.txt", "w");
                /* Imprimiendo estados */
                for (int i = 0; i < Thompson->num_estados; i++){
                    fprintf(conversion, "%s,", (Thompson->estados + i)->nombre);
                }
                fprintf(conversion, "\n");
                /* Imprimiendo alfabeto */
                for (int i = 0; i < __str__len(Thompson->alfabeto); i++){
                    fprintf(conversion, "%c,", *(Thompson->alfabeto + i));
                }
                /* Imprimiendo estado inicial */
                fprintf(conversion, "\n");
                fprintf(conversion, "%s,", Thompson->estado_inicial->nombre);
                fprintf(conversion, "\n");
                /* Imprimiendo estados finales */
                for (int i = 0; i < Thompson->num_estados; i++){
                    if ((Thompson->estados + i)->es_final == 1){
                        fprintf(conversion, "%s,", (Thompson->estados + i)->nombre);
                    }
                }
                fprintf(conversion, "\n");
                /* Imprimiendo transiciones */
                for (int i = 0; i < Thompson->num_estados; i++){
                    for (int j = 0; j < (Thompson->estados + i)->num_transiciones; j++){
                        fprintf(conversion, "%s,%c,%s\n", (Thompson->estados + i)->nombre, ((Thompson->estados + i)->transiciones + j)->simbolo, ((Thompson->estados + i)->transiciones + j)->estado_destino->nombre);
                    }
                }
                fclose(conversion);
                printf("Las equivalencias son:\n%s", impresion);
                printf("Los finales son:\n");
                for (int i = 0; i < Thompson->num_estados; i++){
                    if ((Thompson->estados + i)->es_final == 1){
                        printf("%s\n", (Thompson->estados + i)->nombre);
                    }
                }
                break;
            case 3:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opción inválida\n");
                break;
        }
    }
/*
NOTA: PARA REUTILIZAR EL ARCHIVO DEL AUTÓMATA ES NECESARIO REEMPLAZAR EL ÚLTIMO SALTO DE LÍNEA POR UNA COMA ','
*/

    free(impresion);

    return 0;
}

/* Recibe un apuntador `Estado` y otro `char`. A partir del estado inicial, busca todos los estados a los que se puede llegar con el `epsilon` ingresado. Regresa un apuntador `Set_Str_` con los nombres de los estados que se alcanzan. */
Set_Str_ *cerradura_epsilon(Estado *inicial, char* epsilon){
    //printf("trace:cerradura_epsilon:ini\n");
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
            char *nuevo_nombre = __str__concat(prefijo, inicial->nombre);
            resultado = Set_Str__union_(resultado, temp, nuevo_nombre);
        }
    }
    free(prefijo);
    //printf("trace:cerradura_epsilon:out\n");
    return resultado;
}

/* Recibe un apuntador `Automata`, uno `Set_Str_` y dos `char`. Ejecuta el algoritmo `ir_a`, desde los estados del `conjunto` que se encuentran en el `automata` con el `simbolo`, ejecutando luego la cerradura épsilon con el símblo `epsilon`. Regresa un apuntador `Set_Str_` con el nombre de los estados que genera este algoritmo. */
Set_Str_ *ir_a(Automata *automata, Set_Str_ *conjunto, char *simbolo, char *epsilon){
    //printf("trace:ir_a:ini\n");
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
                        resultado = Set_Str__union_(resultado, temp, __str__concat(resultado->alias, temp->alias + 2));
                    }
                }
            }    
        }
    }
    //printf("trace:ir_a:out\n");
    return resultado;
}

void thompson_states_gen(Automata *afn, Automata *afd, Set_Str_ ***equivalencias, Set_Str_ *conjunto, char *epsilon){
    //printf("trace:thompson_states_gen:ini\n");
    for (int i = 0; i < __str__len(afd->alfabeto); i++){
        char letra = afd->alfabeto[i];
        if (letra != *epsilon){
            char simbolo[2];
            simbolo[0] = letra;
            simbolo[1] = '\0';
            Set_Str_ *ir_a_temporal = ir_a(afn, conjunto, simbolo, epsilon);
            if (!Set_in_List_(*equivalencias, ir_a_temporal) && ir_a_temporal != NULL){
                List_Set_Str__add_(equivalencias, ir_a_temporal);
                afd->estados[afd->num_estados].nombre = ir_a_temporal->alias;
                afd->estados[afd->num_estados].es_final = 0;
                afd->estados[afd->num_estados].num_transiciones = 0;
                afd->num_estados++;
                agregar_transicion(afd, Set_in_List_(*equivalencias, conjunto)->alias, *(afd->alfabeto + i), Set_in_List_(*equivalencias, ir_a_temporal)->alias);
                thompson_states_gen(afn, afd, equivalencias, ir_a_temporal, epsilon);
            }
            else if (ir_a_temporal != NULL){
                agregar_transicion(afd, Set_in_List_(*equivalencias, conjunto)->alias, *(afd->alfabeto + i), Set_in_List_(*equivalencias, ir_a_temporal)->alias);
            }
        }
    }
    //printf("trace:thompson_states_gen:out\n");
    return;    
}

void List_Set_Str__add_(Set_Str_ ***lista, Set_Str_ *elemento){
    int i = 0;
    while (*(*lista + i) != NULL){
        i++;
    }
    *(*lista + i) = elemento;
    *(*lista + i + 1) = NULL;
    return;
}

char *List_Set_Str__str_(Set_Str_ **lista){
    //printf("trace:List_Set_Str__str_:ini\n");
    char *resultado = "";
    int i = 0;
    while (*(lista + i)){
        char *contenido = Set_Str__str_(*(lista + i));
        char *salto_linea = __str__concat(contenido, "\n");
        char *nuevo_resultado = __str__concat(resultado, salto_linea);
        resultado = nuevo_resultado;
        free(contenido);
        free(salto_linea);
        i++;
    }
    //printf("trace:List_Set_Str__str_:out\n");
    return resultado;
}

/* Recibe un doble apuntador `Set_Str_` y uno simple `Set_Str_`. Si el `set` ya se encuentra en `list`, regresa el apuntador del elemento en lista, de lo contrario, regresa NULL. */
Set_Str_ *Set_in_List_(Set_Str_ **list, Set_Str_ *set){
    Set_Str_ *resultado = NULL;
    int i = 0;
    if (list != NULL && set != NULL){
        while (*(list + i)){
            if (Set_Str__eq__(set, *(list + i))){
                resultado = *(list + i);
                break;
            }
        i++;
    }
    }
    return resultado;
}

void asignar_finales(Automata* afd, Automata *afn, Set_Str_ **equivalencias){
    Set_Str_ *finales = NULL;
    /* Buscamos los estados finales en el afn */
    for (int i = 0; i < afn->num_estados; i++){
        if ((afn->estados + i)->es_final == 1){
            if (finales == NULL){
                finales = Set_Str__init_((afn->estados + i)->nombre, "finales");
            }
            else{
                Set_Str__add_(finales, (afn->estados + i)->nombre);
            }
        }
    }
    /* Iteramos sobre los estados para asignar los finales */
    /* Por cada estado del afd */
    for (int i = 0; i < afd->num_estados; i++){
        /* Iniciamos la búsqueda en el contenido de los finales */
        List_Str_ *actual = finales->contenido;
        /* Por cada final en el conjunto de finales */
        for (int j = 0; j < finales->tamano; j++){
            /* Si el contenido del elemento actual se encuentra en la equivalencia del estado */
            if (Set_Str__in_(*(equivalencias + i), actual->contenido) == 1){
                /* Actualizamos el estado final */
                (afd->estados + i)->es_final = 1;
                break;
            }
            /* Sino, continuamos con el siguiente final */
            actual = actual->siguiente;
        }
    }
    return;
}