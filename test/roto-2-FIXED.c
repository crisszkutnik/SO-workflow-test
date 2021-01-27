#include <stdlib.h>
#define LEAKS 1000

typedef int LEAK;

int main() {

  LEAK *wikileaks = malloc(LEAKS);

  free(wikileaks);

  return 0;

  // fixed!!!
}