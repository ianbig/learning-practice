#include <stdio.h>
#include <stdlib.h>

int main() {
	int *ptr = malloc(sizeof(int) * 3);
	free(ptr);
	// test realloc
}