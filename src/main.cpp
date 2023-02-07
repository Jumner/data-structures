#include "utils.h"
#include "tests.h"
#include <stdio.h>

int main() {
	if(fullTest()==ERR) panic("Tests failed");
	printf("\nAll tests passed!\n");
	return 0;
}
