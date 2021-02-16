#include "../headers/func.h"
#include <stdio.h>
#include <stdlib.h>

void someFunc(int* a) {
    *a = 10;
}

void doRandomStuff(int* num) {
    int* ptr = malloc(sizeof(int));
    *ptr = *num + 50;
    *num = *ptr - 10;
    // free(ptr);
    // Wow! I solved the memory leak!
    // No you didn't! ha!
}

void printSomething() {
    printf("Hello fellow reader");
}
