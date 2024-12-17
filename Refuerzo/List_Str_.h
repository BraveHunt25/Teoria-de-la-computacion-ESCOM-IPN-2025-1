#ifndef LIST_STR__H_
#define LIST_STR__H_

#include <stdio.h>
#include <stdlib.h>
#include "../cadenas/cadenas.h"
/*
Este programa modelará la estructura de listas simples, tanto para números enteros y flotantes, como para cadenas de caracteres
*/

/* 
    `int index`
    `char *contenido`
    `struct str_list *siguiente`
*/
typedef struct str_list
{
    int index;
    char *contenido;
    struct str_list *siguiente;
} List_Str_;

/* Recibe un apuntador a una lista `List_Str_` y regresa un entero con el número de elementos después del apuntador más él mismo. */
int List_Str__len_(List_Str_ *lista);
/* Recibe un apuntador a una lista `List_Str_` y un apuntador `char`. Regresa un `1`en caso de que el elemento se encuentre en la lista, en caso contrario, regresa un `0`. */
int List_Str__in_(List_Str_* lista, char *elemento);
/* Recibe dos apuntadores `List_Str_`. Regresa `1` si el contenido de ambas listas es igual y en el mismo orden, de lo contrario, regresa 0. */
int List_Str__eq_(List_Str_ *lista_1, List_Str_ *lista_2);
/* Recibe un apuntador a una lista `List_Str_` un entero. Busca el elemento en el `indice` y devuelve la cadena contenida en la misma posición como un apuntador nuevo. */
char *List_Str__get_(List_Str_ *lista, int indice);
/* Recibe un apuntador a una lista `List_Str_` un entero. Elimina el elemento en el `indice` y devuelve la cadena contenida en la misma posición como un apuntador nuevo. */
char *List_Str__pop_(List_Str_ *lista, int indice);
/* Recibe un apuntador a una lista `List_Str_` y regresa un apuntador a una cadena con las cadenas de la lista en y después del puntero ingresado. */
char *List_Str__str_(List_Str_ *lista);
/* Recibe un apuntador a una lista `List_Str_` y un apuntador `char`. Agrega un nuevo elemento al final de la lista. */
void List_Str__append_(List_Str_ *lista, char *palabra);
/* Recibe un apuntador a una lista `List_Str_`, un apuntador `char` y un entero. Inserta un nuevo elemento en el índice indicado. Si no existe, no inserta nada. */
void List_Str__insert_(List_Str_ *lista, char *contenido, int index);
/* Recibe un apuntador a una lista `List_Str_` y un apuntador `char`. Elimina la primera cadena coincidente con `contenido`. */
void List_Str__remove_(List_Str_ *lista, char *contenido);
/* Recibe un apuntador a una lista `List_Str_`, un apuntador `char` y un entero. Modifica el elemento en el índice indicado a `contenido`. */
void List_Str__set_(List_Str_ *List_Str_, char *contenido, int indice);
/* Recibe dos listas, siendo la primera la lista `extendido` que se modificará y la lista `extension` la segunda de donde se agregarán los elementos. */
void List_Str__extend_(List_Str_ *extendido, List_Str_ *extension);
/* Recibe un apuntador `char` y regresa un apuntador `List_Str_` inicializada con `contenido` y con índice 0. */
List_Str_ *List_Str__init_(char *contenido);
/* Recibe un apuntador a una lista `List_Str` y libera la memoria de todos los elementos, regresando NULL. */
List_Str_ *List_Str__clear_(List_Str_ *lista);

#endif // !LIST_STR__H_