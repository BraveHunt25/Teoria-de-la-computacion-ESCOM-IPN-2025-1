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
* - Extender el lenguaje: Lista
* - Reiniciar el lenguaje
* - Unión o alternativa: Lista
* - Concatenación: Lista
* - Potencia de un lenguaje: Lista
* - Obtener potencias negativas : Lista
* - Estandarizar lambda: Lista ''
* - Verificar que no se repita la palabra: Lista
*/
#include <stdio.h>
#include <stdlib.h>
#include "../Practica_1/stringmanipulation.h"
#include "langman.h"

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