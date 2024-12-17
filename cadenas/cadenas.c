#include <stdio.h>
#include <stdlib.h>
#include "cadenas.h"

/*
Recibe un apuntador a una cadena y regresa el número de caracteres antes del caracter '\0'.
*/
int __str__len(char *palabra){
    int len = 0;
    if (palabra == NULL){
        perror("Se recibió un apuntador vacío");
    }
    else{
        for (int i = 0; *(palabra + i) != '\0'; i++){
            len++;
        }
    }
    return len;
}

/*
Recibe dos apuntadores hacia las palabras a concatenar y regresa el apuntador a la palabra concatenada.
*/
char *__str__concat(char *palabra_1, char *palabra_2){
    int i = 0;
    int len_1 = __str__len(palabra_1);
    int len_2 = __str__len(palabra_2);
    char *resultado = (char*)malloc(sizeof(char) * (len_1 + len_2 + 1));
    for ( ; i < len_1; i++){
        *(resultado + i) = *(palabra_1 + i);
    }
    for ( ; i < len_2 + len_1; i++){
        *(resultado + i) = *(palabra_2 + i - len_1);
    }
    *(resultado + i) = '\0';
    return resultado;
}

/*
Recibe un apuntador hacia la palabra a invertir y regresa un nuevo apuntador a la palabra invertida.
*/
char *__str__reverse(char *palabra){
    int len = __str__len(palabra);
    char *resultado = (char*)malloc(sizeof(char) * (len + 1));
    for (int i = 0; i < len; i++){
        *(resultado + i) = *(palabra + len - i - 1);
    }
    *(resultado + len) = '\0';
    return resultado;
}

/*
Compara la longitud y el contenido de dos cadenas. Regresa '0' si no son iguales o si alguno de los apuntadores es NULL, de lo contrario, regresa '1'.
*/
int __str__eq(char *palabra_1, char *palabra_2){
    int resultado = 1;
    if (!palabra_1 || !palabra_2){
        perror("Uno o ambas palabras es NULL");
    }
    else if (__str__len(palabra_1) != __str__len(palabra_2)){
        resultado = 0;
    }
    else{
        int longitud = __str__len(palabra_1);
        for (int i = 0; i < longitud; i++){
            if (*(palabra_1 + i) != *(palabra_2 + i)){
                resultado = 0;
                break;
            }
        }
    }
    return resultado;    
}

char *__str__copy(char *contenido){
    char *resultado = NULL;
    if (!contenido){
        perror("Se ingresó NULL en `char *contenido`");
    }
    else{
        int len = __str__len(contenido);
        resultado = (char*)malloc(sizeof(char) * (len + 1));
        for (int i = 0; i < len; i++){
            *(resultado + i) = *(contenido + i);
        }
        *(resultado + len) = '\0';
    }
    return resultado;
}