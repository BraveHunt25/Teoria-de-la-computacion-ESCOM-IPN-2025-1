#ifndef STRMANIPULATION
#define STRMANIPULATION
int length(char *cadena);
char *concat(char *cadena_1, char *cadena_2);
char *elevar(char *cadena, int potencia);
char *inversa(char *cadena);
char *subsecuencia(char *cadena, char* caracteres);
char *prefijo(char *cadena, int caracteres);
char *sufijo(char *cadena, int caracteres);
#endif