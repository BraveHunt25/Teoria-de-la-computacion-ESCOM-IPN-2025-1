#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char **arreglo_cadenas = (char**)calloc((size_t)20, sizeof(char*));
    printf("`arreglo_cadenas` tiene de dirección '%x' y apunta a '%x'\n", &arreglo_cadenas, arreglo_cadenas);
    for (int i = 0; i < 20; i++){
        printf("`&arreglo_cadenas[%d]` = `%x`\n", i, arreglo_cadenas + i);
    }
    for (int i = 0; i < 20; i++){
        printf("`arreglo_cadenas[%d]` = \"%s\"\n", i, *(arreglo_cadenas + i));
    }
    for (int i = 0; i < 20; i++){
        *(arreglo_cadenas + i) = "a";
    }
    for (int i = 0; i < 20; i++){
        printf("`arreglo_cadenas[%d]` = \"%s\"\n", i, *(arreglo_cadenas + i));
    }
}