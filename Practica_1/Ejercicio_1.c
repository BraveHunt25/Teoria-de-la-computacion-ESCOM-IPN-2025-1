#include <stdio.h>

void suma(int, int);

int main(){
    printf("Hola mundo\n");
    int a = 5;
    int b = 8;
    suma(4, 5);
    printf("&a = %d, a = %d\n", &a, a);
    printf("&b = %d, b = %d\n", &b, b);
    int* ap = &a;
    void* apvoid = ap;
    float* apfloat = apvoid;
    printf("%d\n", ap);
    printf("%i\n", apvoid);
    printf("%i\n", apfloat);
    return 0;
}

void suma(int a, int b){
    printf("%d + %d = %d\n", a,b, a+b);
}