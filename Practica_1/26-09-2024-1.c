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

#define TAM 50/* code */

int length(char *cadena);
char *concat(char *cadena_1, char *cadena_2);
char *elevar(char *cadena, int potencia);
char *inversa(/* code */char *cadena);
char *subsecuencia(char *cadena, char* caracteres);
char *prefijo(char *cadena, int caracteres);
char *sufijo(char *cadena, int caracteres);

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