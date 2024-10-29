/*
Hernández Jiménez Erick Yael 2023630748
Con un menú se podrá acceder a las siguientes operaciones:
- Prefijo = Lista
- Sufijo = Lista
- Subcadena = Lista
- subsecuencia = Lista
- Inversa = Lista
- Potencia = Lista
*/
#include <stdio.h>
#include <stdlib.h>
#include "./stringmanipulation.h"

#define TAM 50

int main(){
    char cadena_1[TAM] = "\0", cadena_2[TAM] = "\0", chars[TAM] = "\0", *aux_str;
    char *arreglos[2] = {cadena_1, cadena_2};
    int aux, op = 0, seleccion = 0;
    while (op != 8){
        printf("\n\n\n\n\n\n\n---------- Manipulador de cadenas -----------\nCadena 1: '%s'\nCadena 2: '%s'\n", cadena_1, cadena_2);
        printf("Ingrese la opcion que desea realizar: \n1. Cambiar cadena\n2. Obtener el prefijo de una cadena\n3. Obtener el sufijo de una cadena");
        printf("\n4. Obtener una subcadena\n5. Obtener una subsecuencia\n6. Obtener el inverso de una cadena\n7. Elevar una cadena a una potencia\n8. Salir\n");
        scanf("%d", &op);
        fflush(stdin);
        printf("Ingrese la cadena a operar:\nCadena 1: '%s'\nCadena 2: '%s'\n", cadena_1, cadena_2);
        scanf("%d", &seleccion);
        fflush(stdin);
        if (seleccion <= 1){
                seleccion = 0;
        }
        else{
                seleccion = 1;
        }
        switch (op){
        case 1:
            printf("Ingresa la nueva cadena:\n");
            scanf("%[^\n]", arreglos[seleccion]);
            break;
        case 2:
            printf("Ingresa el numero de caracteres que deseas eliminar para obtener el prefijo:\n");
            fflush(stdin);
            scanf("%d", &aux);
            printf("El prefijo es: '%s'\n", prefijo(arreglos[seleccion], aux));
            break;
        case 3:
            printf("Ingresa el numero de caracteres que deseas eliminar para obtener el sufijo:\n");
            fflush(stdin);
            scanf("%d", &aux);
            printf("El sufijo es: '%s'\n", sufijo(arreglos[seleccion], aux));
            break;
        case 4:
            printf("Ingresa la cantidad de caracteres que deseas eliminar del prefijo:\n");
            fflush(stdin);
            scanf("%d", &aux);
            aux_str = (char*)malloc(sizeof(char)*length(arreglos[seleccion]));
            aux_str = sufijo(arreglos[seleccion], aux);
            printf("%s\n", aux_str);
            printf("Ingresa la cantidad de caracteres que deseas eliminar del sufijo:\n");
            fflush(stdin);
            scanf("%d", &aux);
            printf("La subcadena es: '%s'\n", prefijo(aux_str, aux));
            free(aux_str);
            break;
        case 5:
            printf("Ingresa los caracteres que deseas eliminar:\n");
            scanf("%[^\n]", chars);
            printf("La subsecuencia resultantes es: '%s'\n", subsecuencia(arreglos[seleccion], chars));
            break;
        case 6:
            printf("Su inversa es '%s'\n", inversa(arreglos[seleccion]));
            break;
        case 7:
            printf(("Ingresa la potencia:\n"));
            scanf("%d", &aux);
            printf("%s\n", (elevar(arreglos[seleccion], aux)));
            break;
        case 8:
            printf("Saliendo\n");
            break;
        default:
            printf("Selecciona una opcion valida\n");
            break;
        }
    }
    return 0;
}