/*
	Purpose: Testing the scope of register
	Testing case:
		1. global variable
		2. local variable
		3. function parameter
*/
#include <stdio.h>
// register int global;

void func(register int para) {
	fprintf(stderr, "%d\n", para);
}

int main(int argc, char const *argv[])
{
	register int x = 10;
	fprintf(stderr, "%d\n", x);
	func(x);

	return 0;
}