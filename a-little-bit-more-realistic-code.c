#include <stdio.h>
#include <stdlib.h>

int global_1 = 1, global_2 = 2;

int main() {
  int *list = malloc(10 * sizeof(int));

  for (int i = 0; i < 10; i++) {
    list[i] = i * i * i;
  }

  for (int i = 0; i < 10; printf("%d\n", list[i++]))
    ;

  return 0;
}

// this code was written by