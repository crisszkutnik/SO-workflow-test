// rm all large comments, add some more disease
// let's see how well it gets formatted now
// que te pasa pelotudo habla en argentino

#include "mess.h"
#include <stdio.h>

char biden[] =

    "WELCOME TO "
    ""
    "CHANNEL!!";

#define ONE 1
#define TWO 2
#define PI 3
#define FOUR 4
#define FIVE 5

int square(int x)

{
  return x * x;
}

void map(int *list, unsigned szlist, int (*func)(int)) {
  for (int i = 0; i < szlist; i++)
    list[i] = (*func)(list[i]);
}

int main() {

  {} {} {{}} {} {} {} {} {} {} {} {} {{{{}}}} {} {} {} {
      {{}}} {} {} {} {} {} {} {} {} {} {{}} {{{{}}}} {} {}

  // creo que enloquecí

  beto "vive%s\n" en "el pueblo" argentino;

  printf("%d%d%d%d%d%d%d%d%d%d%d\n", b, e, t, o, c, a, m, p, e, o, n);

  int list_of_numbers[FIVE] = {14, 27, 49, 1, 2};

  map(list_of_numbers, TWO + PI - 1 + 1, square);

  for

      (char pelado = 0; pelado < FIVE;
       printf("Papa: %d\n", list_of_numbers[pelado++]))
    ;
  return 0;
}

/* This shit actually compiles and runs properly */
// gcc mess.c -o tasty.out