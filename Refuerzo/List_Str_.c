#include <stdio.h>
#include <stdlib.h>
#include "List_Str_.h"
#include "../cadenas/cadenas.h"
/*
Este programa modelará la estructura de listas simples, tanto para números enteros y flotantes, como para cadenas de caracteres
*/

List_Str_ *List_Str__init_(char *contenido){
    if (!contenido){
        perror("Apuntador NULL en `List_Str_ *lista`");
        return NULL;
    }
    else{
        List_Str_ *nuevo_elemento = (List_Str_*)malloc(sizeof(List_Str_));
        nuevo_elemento->contenido = contenido;
        nuevo_elemento->index = 0;
        nuevo_elemento->siguiente = NULL;
        return nuevo_elemento;
    }
}

char *List_Str__str_(List_Str_ *lista){
    char *resultado = "[";
    if (!lista){
        perror("Apuntador NULL en `List_Str_ *lista`");
        resultado = __str__concat(resultado, "]");
    }
    else{
        for (; lista; lista = lista->siguiente){
            resultado = __str__concat(resultado, lista->contenido);
            resultado = __str__concat(resultado, ",");
        }
        *(resultado + __str__len(resultado) - 1) = ']';
    }
    return resultado;
}

void List_Str__append_(List_Str_ *lista, char *palabra){
    if (!lista){
        perror("Apuntador NULL en `List_Str_ *lista`");
    }
    else{
        while(lista->siguiente){
            lista = lista->siguiente;
        }
        lista->siguiente = List_Str__init_(palabra);
        if(lista->siguiente){
            lista->siguiente->index = lista->index + 1;
        }
    }
    return;
}

int List_Str__len_(List_Str_ *lista){
    int resultado = 0;
    if (!lista){
        perror("Apuntador NULL en `List_Str_ *lista`");
    }
    else{
        while (lista){
            resultado++;
            lista = lista->siguiente;
        }   
    }
    return resultado;
}

int List_Str__in_(List_Str_* lista, char *elemento){
    int resultado = 0;
    int len = List_Str__len_(lista);
    for(int i = 0; i<len; i++){
        if (__str__eq(lista->contenido, elemento)){
            resultado = 1;
            break;
        }
        lista = lista->siguiente;
    }
    return resultado;
}

int List_Str__eq_(List_Str_ *lista_1, List_Str_ *lista_2){
    int resultado = 1;
    if (List_Str__len_(lista_1) != List_Str__len_(lista_2)){
        resultado = 0;
    }
    else{
        for (int i = 0; i < List_Str__len_(lista_1); i++){
            if(!__str__eq(lista_1->contenido, lista_2->contenido)){
                resultado = 0;
                break;
            }
            lista_1 = lista_1->siguiente;
            lista_2 = lista_2->siguiente;
        }
    }
    return resultado;
}

void List_Str__insert_(List_Str_ *lista, char *contenido, int index){
    if (!lista){
        perror("Apuntador NULL en `List_Str_ *lista`");
    }
    else if (!contenido){
        perror("Apuntador NULL en `char *contenido`");
    }
    else if (index<0){
        perror("Índice `int index` negativo o no válido");
    }
    else{
        List_Str_ *elemento_anterior = lista;
        while (lista->index < index){
            elemento_anterior = lista;
            lista = lista->siguiente;
            if (!lista){
                perror("Número de elementos insuficientes");
                break;
            }
            else if(lista->index == index){
                elemento_anterior->siguiente = List_Str__init_(contenido);
                elemento_anterior->siguiente->index = index;
                elemento_anterior->siguiente->siguiente = lista;
                while (lista){
                    lista->index++;
                    lista = lista->siguiente;
                }
                break;
            }
        }
    }
    return;
}

void List_Str__remove_(List_Str_ *lista, char *contenido){
    if(!lista){
        perror("Apuntador NULL en `lista`");
    }
    else if (!contenido){
        perror("Apuntador NULL en `char *contenido`");
    }
    else{
        List_Str_ *elemento_anterior = lista;
        while (lista){
            elemento_anterior = lista;
            lista = lista->siguiente;
            if (!lista){
                perror("No se encontró la cadena contenida en `char *contenido`");
                break;
            }
            else if(__str__eq(lista->contenido, contenido) == 1){
                elemento_anterior->siguiente = lista->siguiente;
                free(lista);
                lista = elemento_anterior->siguiente;
                while (lista){
                    lista->index--;
                    lista = lista->siguiente;
                }
                break;
            }
        }
    }   
    return;
}

char *List_Str__pop_(List_Str_ *lista, int indice){
    char *resultado = NULL;
    if (!lista){
        perror("Apuntador NULL en `List_Str_ *lista`");
    }
    else if (indice<0){
        perror("Índice `int index` negativo o no válido");
    }
    else{
        List_Str_ *elemento_anterior = lista;
        while (lista->index < indice){
            elemento_anterior = lista;
            lista = lista->siguiente;
            if (!lista){
                perror("Número de elementos insuficientes");
                break;
            }
            else if(lista->index == indice){
                resultado = __str__copy(lista->contenido);
                elemento_anterior->siguiente = lista->siguiente;
                free(lista);
                lista = elemento_anterior->siguiente;
                while (lista){
                    lista->index--;
                    lista = lista->siguiente;
                }
                break;
            }
        }
    }
    return resultado;
}

char *List_Str__get_(List_Str_ *lista, int indice){
    char *resultado = NULL;
    if (!lista){
        perror("Apuntador NULL en `List_Str_ *lista`");
    }
    else if (indice<0){
        perror("Índice `int index` negativo o no válido");
    }
    else{
        while (lista->index < indice){
            lista = lista->siguiente;
            if (!lista){
                perror("Número de elementos insuficientes");
                break;
            }
            else if(lista->index == indice){
                resultado = __str__copy(lista->contenido);
                break;
            }
        }
    }
    return resultado;   
}

void List_Str__set_(List_Str_ *lista, char *contenido, int indice){
    if (!lista){
        perror("Apuntador NULL en `List_Str_ *lista`");
    }
    else if (indice<0){
        perror("Índice `int index` negativo o no válido");
    }
    else if (indice == 0){
        lista->contenido = __str__copy(contenido);
    }
    else{
        while (lista->index < indice){
            lista = lista->siguiente;
            if (!lista){
                perror("Número de elementos insuficientes");
                break;
            }
            else if(lista->index == indice){
                lista->contenido = __str__copy(contenido);
                break;
            }
        }
    }
    return;
}

void List_Str__extend_(List_Str_ *extendido, List_Str_ *extension){
    if (!extendido){
        perror("Apuntador NULL en `List_Str_ *extendido`");
    }
    else if (!extension){
        perror("Apuntador NULL en `List_Str_ *extension`");
    }
    else{
        List_Str_ *cola = extendido;
        while (cola->siguiente){
            cola = cola->siguiente;
        }
        while (extension){
            cola->siguiente = List_Str__init_(extension->contenido);
            cola->siguiente->index = cola->index + 1;
            cola = cola->siguiente;
            extension = extension->siguiente;
        }
    }
    return;
}

List_Str_ *List_Str__clear_(List_Str_ *lista){
    if (!lista){
        perror("Apuntador NULL en `List_Str_ *lista`");
    }
    else if (lista->siguiente){
        lista->siguiente = List_Str__clear_(lista->siguiente);
    }
    free(lista);
    return NULL;
}