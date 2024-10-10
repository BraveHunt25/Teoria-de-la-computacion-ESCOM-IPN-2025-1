#ifndef STRMANIPULATION
#define STRMANIPULATION

#include <stdio.h>
#include <stdlib.h>

int length(char *cadena);
char *concat(char *cadena_1, char *cadena_2);
char *elevar(char *cadena, int potencia);
char *inversa(char *cadena);
char *subsecuencia(char *cadena, char* caracteres);
char *prefijo(char *cadena, int caracteres);
char *sufijo(char *cadena, int caracteres);

int length(char *cadena){
    int len=0;
    for (len = 0; cadena[len] != '\0'; len++){
        ;
    }    
    return len;  
}

char *concat(char *cadena_1, char *cadena_2){
    int len_1 = length(cadena_1), len_2 = length(cadena_2);
    char *nueva_cadena = (char*)malloc(sizeof(char)*(len_1+len_2));
    *nueva_cadena = '\0';
    int pos;
    //printf("\n%s", nueva_cadena);
    for (pos = 0; pos < len_1; pos++)
    {
        nueva_cadena[pos] = cadena_1[pos];
    }
    //printf("\n%s", nueva_cadena);
    for (pos = 0; (pos+len_1) < (len_1+len_2); pos++)
    {
        nueva_cadena[pos+len_1] = cadena_2[pos];
    }
    //printf("\n%s\n", nueva_cadena);
    nueva_cadena[len_1+len_2] = '\0';
    return nueva_cadena;
}

char *elevar(char *cadena, int potencia){
    char *new_string;
    if (potencia == 0){
        new_string = (char*)malloc(sizeof(char));
        *(new_string) = '\0';
    }
    else if (potencia < 0){
        new_string = elevar(inversa(cadena), -potencia);
    }
    
    else{
        new_string = concat(cadena, elevar(cadena, potencia-1));
    }
    
    return new_string;
}

char *inversa(char *cadena){
    int longitud = length((cadena));
    char *new_string = (char*)malloc(sizeof(char)*longitud);
    for (int i = 0; i < longitud; i++){
        *(new_string+i) = *(cadena+longitud-i-1);
    }
    *(new_string+longitud) = '\0';
    return new_string;    
}

char *subsecuencia(char *cadena, char* caracteres){
    int longitud = length((cadena)), k = 0, b;
    char *new_string = (char*)malloc(sizeof(char)*longitud+1);
    for (int i = 0; i < longitud; i++){
        b = 0;
        for (int j = 0; j < length(caracteres); j++){
            if(*(cadena+i) == *(caracteres+j)){
                b = 1;
                break;
            }
        }
        if (b == 0){
            *(new_string+k) = *(cadena+i);
            k++;
        }
    }
    k++;
    *(new_string+k) = '\0';
    return new_string;
}

char *prefijo(char *cadena, int caracteres){
    int longitud = length(cadena);
    if (caracteres > longitud){
        caracteres = longitud;
    }
    else if (caracteres < 0){
        return sufijo(cadena, -caracteres);    
    }
    int tope = longitud-caracteres;
    char *new_string = (char*)malloc(sizeof(char)*(tope+1));
    for (int i = 0; i < tope; i++){
        *(new_string+i) = *(cadena+i);        
    }
    *(new_string+tope) = '\0';
    return new_string;
}

char *sufijo(char *cadena, int caracteres){
    int longitud = length(cadena);
    if (caracteres > longitud){
        caracteres = longitud;
    }
    else if (caracteres < 0){
        return prefijo(cadena, -caracteres);    
    }
    int tope = caracteres;
    char *new_string = (char*)malloc(sizeof(char)*(longitud-tope+1));
    for (int i = 0; i < longitud; i++){
        *(new_string+i) = *(cadena+tope+i);        
    }
    *(new_string+longitud-tope+1) = '\0';
    return new_string;
}
#endif