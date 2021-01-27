#include <stdio.h>
#include <stdlib.h>

int main() {

  char *leak = malloc(1000);

  // TOO - BAD!

  return 0;
}