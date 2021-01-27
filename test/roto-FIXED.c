#include <stdio.h>
#include <stdlib.h>

int main() {

  char *leak = malloc(1000);
  free(leak);

  // TOO - BAD!

  return 0;
}