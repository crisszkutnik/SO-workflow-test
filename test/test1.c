#include "../headers/func.h"
#include <assert.h>

int main() {
  int num = 22;
  int *ptr = &num;
  doRandomStuff(ptr);
  //assert(*ptr == 0);
  return 0;
}
