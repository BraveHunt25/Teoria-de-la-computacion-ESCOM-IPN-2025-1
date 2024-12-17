#ifndef SET_STR__H_
#define SET_STR__H_

#include <stdio.h>
#include <stdlib.h>
#include "../Practica_2/langman.h"
#include "../Practica_1/stringmanipulation.h"
#include "./List_Str_.h"

/*
Este programa modelará el tipo de dato abstracto de un set (lista con elementos únicos)
*/

/*
    `List_Str_ *contenido`
    `char *alias`
    `int tamano`
*/
typedef struct set
{
    List_Str_ *contenido;
    char *alias;
    int tamano;
} Set_Str_;

/* Recibe un apuntador `Set_Str_` y devuelve un apuntador `char` con el contenido de `set`. */
char *Set_Str__str_(Set_Str_ *set);
/* Resibe dos apuntadores `Set_Str_` de los sets a comparar. Regresa `1` si el contenido de ambos es igual sin importar el orden, de lo contrario, regresa `0` */
int Set_Str__eq__(Set_Str_ *set_1, Set_Str_ *set_2);
/* Recibe un apuntador `Set_Str_` y un apuntador `char`. Regresa un `1` si el `elemento` está contenido en el contenido de `set`, de lo contrario, un `0`. */
int Set_Str__in_(Set_Str_ *set, char *elemento);
/* Recibe un apuntador `Set_Str_` y regresa un entero con la cantidad de elementos que contiene el `set` */
int Set_Str__len_(Set_Str_ *set);
/* Recibe dos apuntadores `char` para nombrar con `alias` e inicializar con `primer_elemento` el contenido. Regresa el apuntador `Set_Str_` con el contenido y `alias` inicializado. */
Set_Str_ *Set_Str__init_(char *primer_elemento, char *alias);
/* Recibe dos apuntadores `Set_Str_` de los sets a unir y un apuntador `char` para nombrar la unión. Regresa el apuntador `Set_Str_` con la respectiva unión y nombre. */
Set_Str_ *Set_Str__union_(Set_Str_ *set_1, Set_Str_ *set_2, char *nombre_union);
/* Recibe un apuntador `Set_Str_` del `set` al que se le agrega el `elemento` del apuntador `void` que pueda ser convertido a un apuntador `char`. Agregará el `elemento` si no se encuentra ya en el contenido del `set`. */
void Set_Str__add_(Set_Str_ *set, void *elemento);
/* Recibe un apuntador `Set_Str_` del `set` al que se le elimina el `elemento` del apuntador `void` que pueda ser convertido a un apuntador `char`. Eliminará el `elemento` si se encuentra en el contenido del `set` */
void Set_Str__remove_(Set_Str_ *set, void *elemento);


#endif // !SET_STR__H_
