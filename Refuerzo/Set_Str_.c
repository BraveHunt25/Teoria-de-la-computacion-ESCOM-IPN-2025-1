#include <stdio.h>
#include <stdlib.h>
#include "../Practica_2/langman.h"
#include "../Practica_1/stringmanipulation.h"
#include "./List_Str_.h"
#include "./Set_Str_.h"

Set_Str_ *Set_Str__init_(char *primer_elemento, char *alias){
    Set_Str_ *resultado = (Set_Str_*)malloc(sizeof(Set_Str_));
    resultado->contenido = List_Str__init_(primer_elemento);
    resultado->alias = alias;
    resultado->tamano = 1;
    return resultado;
}

char *Set_Str__str_(Set_Str_ *set){
    char *res;
    if(set){
        res = __str__concat(__str__copy(set->alias), __str__concat(": ", List_Str__str_(set->contenido)));
    }
    else{
        res = "[]";
    }
    return res;
}

void Set_Str__add_(Set_Str_ *set, void *elemento){
    if (!List_Str__in_(set->contenido, elemento))
    {
        List_Str__append_(set->contenido, (char*)elemento);
    }    
    set->tamano = List_Str__len_(set->contenido);
    return;
}

int Set_Str__len_(Set_Str_ *set){
    int resultado = 0;
    if (set->tamano){
        resultado = set->tamano;
    }
    return resultado;
}

void Set_Str__remove_(Set_Str_ *set, void *elemento){
    if (List_Str__in_(set->contenido, elemento))
    {
        List_Str__remove_(set->contenido, (char*)elemento);
    }    
    set->tamano = List_Str__len_(set->contenido);
    return;
}

int Set_Str__in_(Set_Str_ *set, char *elemento){
    int resultado = 0;
    if (List_Str__in_(set->contenido, elemento)){
        resultado = 1;
    }
    return resultado;
}

Set_Str_ *Set_Str__union_(Set_Str_ *set_1, Set_Str_ *set_2, char *nombre_union){
    Set_Str_ *resultado = Set_Str__init_(set_1->contenido->contenido, nombre_union);
    List_Str_ *current = set_1->contenido->siguiente;
    while(current){
        Set_Str__add_(resultado, current->contenido);
        current = current->siguiente;
    }
    if (set_2){
        current = set_2->contenido;
        while(current){
            Set_Str__add_(resultado, current->contenido);
            current = current->siguiente;
        }
    }
    return resultado;
}

int Set_Str__eq__(Set_Str_ *set_1, Set_Str_ *set_2){
    int resultado = 1;
    if (Set_Str__len_(set_1) != Set_Str__len_(set_2)){
        resultado = 0;
    }
    else{
        List_Str_ *current = set_1->contenido;
        for (int i = 0; i < Set_Str__len_(set_1); i++){
            if(!List_Str__in_(set_2->contenido, current->contenido)){
                resultado = 0;
                break;
            }
            current = current->siguiente;
        }
    }
    return resultado;
}