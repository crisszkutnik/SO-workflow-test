#include <stdlib.h>

int main() {
  char* ben = malloc(1000); //This causes a memory leak. Too bad!
  return 0;
}

// Commit creado desde Lubuntu v5.0.1 en VirtualBox
