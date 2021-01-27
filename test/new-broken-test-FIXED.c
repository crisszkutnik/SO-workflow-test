#include <stdlib.h>

int main() {
  int a = 0;
  char *ben = malloc(5); // too bad!
  free(ben);

  return 0;
}