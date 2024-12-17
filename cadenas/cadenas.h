#ifndef __CADENAS_H__
#define __CADENAS_H__

#include <stdlib.h>
#include <stdio.h>

int __str__len(char *palabra);
char *__str__concat(char *palabra_1, char *palabra_2);
char *__str__reverse(char *palabra);
char *__str__copy(char *contenido);
int __str__eq(char *palabra_1, char *palabra_2);

#endif // !__CADENAS_H__
