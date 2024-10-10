#include <stdio.h>
#include <stdlib.h>
#include "../Practica_1/strmanipulation.h"

void imprimir_lenguaje(char **lenguaje);
int cadenas_iguales(char *palabra_1, char* palabra_2);
int longitud_lenguaje(char **lenguaje);
int elevar_num(int base, int exponente);
char **concatenar_lenguajes(char **lenguaje_1, char **lenguaje_2);
char **expandir_lenguaje(char **lenguaje_original, char *nueva_palabra, int long_max_palabra);
char **invertir_lenguaje(char **lenguaje);
char **elevar_potencia_lenguaje(char** lenguaje, int potencia);
char **union_lenguajes(char **lenguaje_1, char **lenguaje_2);

int main()
{
    char **lenguaje_1 = (char**)malloc(sizeof(char*)*1);
    char **lenguaje_2 = (char**)malloc(sizeof(char*)*1);
    *lenguaje_1 = NULL;
    *lenguaje_2 = NULL;
    int op, seleccion, potencia;
    while (op != 6){
        printf("\n--- Menú de Operaciones ---\n");
        printf("Lenguaje 1:\t");
        imprimir_lenguaje(lenguaje_1);
        printf("\nLenguaje 2:\t");
        imprimir_lenguaje(lenguaje_2);
        printf("\n1. Agregar palabra al lenguaje\n");
        printf("2. Vaciar lenguaje\n");
        printf("3. Unir lenguajes\n");
        printf("4. Concatenar lenguajes\n");
        printf("5. Elevar lenguaje a una potencia\n");
        printf("6. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &op);
        getchar();
        switch(op)
        {
            case 1:
                printf("Seleccione el lenguaje (1 o 2): ");
                scanf("%d", &seleccion);
                getchar();
                
                if (seleccion == 1) {
                    lenguaje_1 = expandir_lenguaje(lenguaje_1, NULL, 0);
                } else if (seleccion == 2) {
                    lenguaje_2 = expandir_lenguaje(lenguaje_2, NULL, 0);
                } else {
                    printf("Selección inválida.\n");
                }
                break;

            case 2:
                printf("Seleccione el lenguaje a vaciar (1 o 2): ");
                scanf("%d", &seleccion);
                getchar();

                if (seleccion == 1) {
                    free(lenguaje_1);
                    lenguaje_1 = (char**)malloc(sizeof(char*)*1);
                    *lenguaje_1 = NULL;
                } else if (seleccion == 2) {
                    free(lenguaje_2);
                    lenguaje_2 = (char**)malloc(sizeof(char*)*1);
                    *lenguaje_2 = NULL;
                } else {
                    printf("Selección inválida.\n");
                }
                break;

            case 3:
                printf("Uniendo lenguajes...\n");
                imprimir_lenguaje(union_lenguajes(lenguaje_1, lenguaje_2));
                break;

            case 4:
                printf("Concatenando lenguajes...\n");
                imprimir_lenguaje(concatenar_lenguajes(lenguaje_1, lenguaje_2));
                break;

            case 5:
                printf("Seleccione el lenguaje (1 o 2): ");
                scanf("%d", &seleccion);
                getchar();
                
                printf("Ingrese la potencia: ");
                scanf("%d", &potencia);
                getchar();

                if (seleccion == 1) {
                    imprimir_lenguaje(elevar_potencia_lenguaje(lenguaje_1, potencia));
                    fflush(stdin);
                } else if (seleccion == 2) {
                    imprimir_lenguaje(elevar_potencia_lenguaje(lenguaje_2, potencia));
                    fflush(stdin);
                } else {
                    printf("Selección inválida.\n");
                }
                break;

            case 6:
                printf("Saliendo del programa...\n");
                break;

            default:
                printf("Opción no válida, intente de nuevo.\n");
                break;
        }
    }
    free(lenguaje_1);
    free(lenguaje_2);
    return 0;
}

int longitud_lenguaje(char **lenguaje){
    int tamano = 0;
    if (lenguaje != NULL){
        while (*(lenguaje+tamano) != NULL){
            tamano++;
        }
    }
    return tamano;
}

char **expandir_lenguaje(char **lenguaje_original, char *nueva_palabra, int long_max_palabra){
    int es_nueva = 1;
    int longitud_actual = longitud_lenguaje(lenguaje_original);
    if (nueva_palabra == NULL){
        if (long_max_palabra <= 0){
            long_max_palabra = 100;
        }
        char *nueva_palabra = (char*)malloc(sizeof(char)*(long_max_palabra+1));
        if (nueva_palabra == NULL) {
            // printf("Error al asignar memoria para nueva_palabra\n");
            return lenguaje_original;
        }
        printf("Ingresa la nueva palabra:\n");
        fgets(nueva_palabra, 100, stdin);
        fflush(stdin);
        if (nueva_palabra[length(nueva_palabra) - 1] == '\n') {
            nueva_palabra[length(nueva_palabra) - 1] = '\0';
        }
        for (int i = 0; *(lenguaje_original+i) != NULL; i++){
            if (cadenas_iguales(nueva_palabra, *(lenguaje_original+i)) == 1){
                es_nueva = 0;
            }
        }
        if (es_nueva == 0){
            // printf("La palabra no es nueva, por lo que no se agrega...\n");
            free(nueva_palabra);
            return lenguaje_original;
        }
        else{
            char **lenguaje_expandido = (char**)realloc(lenguaje_original, sizeof(char*) * (longitud_actual + 2));
            if (lenguaje_expandido != NULL){
                *(lenguaje_expandido+longitud_actual) = nueva_palabra;
                *(lenguaje_expandido+longitud_actual+1) = NULL;
                // printf("Se logra reasignar el espacio de memoria para el lenguaje expandido\n");
            }
            else{
                // printf("No se logra reasignar el espacio de memoria para el lenguaje expandido\n");
                free(nueva_palabra);
                lenguaje_expandido = lenguaje_original;
            }
            return lenguaje_expandido;
        }
    }
    else{
        for (int i = 0; *(lenguaje_original+i) != NULL; i++){
            if (cadenas_iguales(nueva_palabra, *(lenguaje_original+i)) == 1){
                es_nueva = 0;
            }
        }
        if (es_nueva == 0){
            // printf("La palabra no es nueva, por lo que no se agrega...\n");
            return lenguaje_original;
        }
        else{
            char **lenguaje_expandido = (char**)realloc(lenguaje_original, sizeof(char*) * (longitud_actual + 2));
            if (lenguaje_expandido != NULL){
                *(lenguaje_expandido+longitud_actual) = nueva_palabra;
                *(lenguaje_expandido+longitud_actual+1) = NULL;
                // printf("Se logra reasignar el espacio de memoria para el lenguaje expandido\n");
            }
            else{
                // printf("No se logra reasignar el espacio de memoria para el lenguaje expandido\n");
                lenguaje_expandido = lenguaje_original;
            }
            return lenguaje_expandido;
        }
    }
}

void imprimir_lenguaje(char **lenguaje){
    if (lenguaje == NULL || *(lenguaje+0) == NULL){
        printf("=phi=\n");
    }
    else{
        for (int i = 0; *(lenguaje+i) != NULL; i++){
            printf("'%s'\t", *(lenguaje+i));
        }
    }
}

int cadenas_iguales(char *palabra_1, char* palabra_2){
    int iguales = 1;
    if (palabra_1 == NULL || palabra_2 == NULL){
        // printf("Se necesitan dos cadenas para comparar...\n");
        iguales = 0;
    }
    else{
        for (int posicion = 0; *(palabra_1+posicion) != '\0' || *(palabra_2+posicion) != '\0'; posicion++)
        {
            if (*(palabra_1+posicion) != *(palabra_2+posicion)){
                iguales = 0;
                break;
            }
        }
    }
    return iguales;
}

char **union_lenguajes(char **lenguaje_1, char **lenguaje_2){
    char **lenguaje_unido = (char**)malloc(sizeof(char*)*(longitud_lenguaje(lenguaje_1) + longitud_lenguaje(lenguaje_2) + 1));
    for (int palabra = 0; *(lenguaje_1+palabra) != NULL; palabra++){
        lenguaje_unido = expandir_lenguaje(lenguaje_unido, *(lenguaje_1+palabra), 0);
    }
    for (int palabra = 0; *(lenguaje_2+palabra) != NULL; palabra++){
        lenguaje_unido = expandir_lenguaje(lenguaje_unido, *(lenguaje_2+palabra), 0);
    }
    return lenguaje_unido;
}

char **concatenar_lenguajes(char **lenguaje_1, char **lenguaje_2){
    int longitud_1 = longitud_lenguaje(lenguaje_1);
    int longitud_2 = longitud_lenguaje(lenguaje_2);
    char **lenguaje_concatenado = (char**)malloc(sizeof(char*) * (longitud_1 + longitud_2 + 1));
    if (lenguaje_1 != NULL && lenguaje_2 != NULL){
        for (int leng_1 = 0; *(lenguaje_1+leng_1) != NULL; leng_1++){
            for (int leng_2 = 0; *(lenguaje_2+leng_2) != NULL; leng_2++){
                lenguaje_concatenado = expandir_lenguaje(lenguaje_concatenado, concat(*(lenguaje_1+leng_1), *(lenguaje_2+leng_2)), 0);
            }
        }
        *(lenguaje_concatenado+longitud_1*longitud_2) = NULL;
    }
    else{
        *(lenguaje_concatenado+0) = NULL;
    }
    return lenguaje_concatenado;
}

char **invertir_lenguaje(char **lenguaje){
    int tamano_lenguaje = longitud_lenguaje(lenguaje);
    char** lenguaje_invertido = (char**)malloc(sizeof(char*)*tamano_lenguaje+1);
    if (lenguaje != NULL && *(lenguaje+0) != NULL){
        for (int palabra = 0; *(lenguaje+palabra) != NULL; palabra++){
            *(lenguaje_invertido+palabra) = inversa(*(lenguaje+palabra));
        }
    }
    *(lenguaje_invertido+tamano_lenguaje) = NULL;
    return lenguaje_invertido;
}

char **elevar_potencia_lenguaje(char** lenguaje, int potencia){
    int tamano_lenguaje = longitud_lenguaje(lenguaje);
    int espacio = elevar_num(tamano_lenguaje,potencia);
    char **lenguaje_elevado = (char**)malloc(sizeof(char*) * (espacio + 1));
    if (potencia > 0){
        for (int i = 0; i < tamano_lenguaje; i++) {
            *(lenguaje_elevado+i) = *(lenguaje+i);
        }
        *(lenguaje_elevado+tamano_lenguaje) = NULL;

        for (int i = 1; i < potencia; i++){
            char **temp = concatenar_lenguajes(lenguaje_elevado, lenguaje);
            //free(lenguaje_elevado);
            lenguaje_elevado = temp;
        }
        *(lenguaje_elevado+espacio) = NULL;
    }
    else if (potencia < 0){
        lenguaje_elevado = elevar_potencia_lenguaje(invertir_lenguaje(lenguaje), -potencia);
    }
    else if (potencia == 0){
        lenguaje_elevado = (char**)malloc(sizeof(char*) * 2);
        *(lenguaje_elevado+0) = (char*)malloc(sizeof(char) * 1);
        **lenguaje_elevado = '\0';
        *(lenguaje_elevado+1) = NULL; 
    }
    else{
        *(lenguaje_elevado+espacio) = NULL;
    }
    return lenguaje_elevado;
}

int elevar_num(int base, int exponente){
    int resultado = 1;
    if (exponente < 0) {
        resultado = 0;
    }
    for (int i = 0; i < exponente; i++) {
        resultado *= base;
    }
    return resultado;
}