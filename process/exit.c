/* 
	Test exit handler called order
*/

#include <stdio.h>
#include <stdlib.h>

void exit_1() {
	fprintf(stderr, "Exit 1 called\n");
}

void exit_2() {
	fprintf(stderr, "Exit 2 called\n");
}

int main() {
	atexit(exit_1);
	atexit(exit_2);

	return 0;
}