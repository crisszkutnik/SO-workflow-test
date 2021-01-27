#include "../headers/func.h"
#include "../headers/other-func.h"
#include <stdlib.h>

int main() {
    int* bruh = malloc(sizeof(int));
    // doRandomStuff(bruh); // no! this leacc! i'll comment it!
    free(bruh);

    generateALeakForMePleaseThanks(); // looks good to me!

    return 0;
}