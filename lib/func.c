#include <stdio.h>
#include <stdlib.h>
#include "../headers/func.h"

void someFunc(int* a) {
	*a = 10;
}

void doRandomStuff(int* num) {
	int* ptr = malloc(sizeof(int));
	*ptr = *num + 50;
	*num = *ptr - 10;
	// This has a memory leak. Too bad!
}

void printSomething() {
	printf("Hello fellow reader");
}
