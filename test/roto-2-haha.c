#include <stdlib.h>
#define LEAKS 1000

typedef int LEAK;

int main() {

	LEAK *wikileaks = malloc(LEAKS);

	return 0;

	// TOO
	// BAD!
}