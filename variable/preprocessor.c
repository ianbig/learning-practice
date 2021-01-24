/*
	Purpose: Testing Preprocess
		1. Macro pitsfall: max add twice, need parathensis to make sure right answer
		2. concenation of macro string
		3. test undef
		4. # before parameter
*/
#include <stdio.h>

#define max(arg1, arg2) (arg1 > arg2) ? arg1: arg2
#define square(x) (x)*(x)
#define string c ##str ##ing // test for macro concatenation
#undef printHello
// #define printHello printf("hello\n")
#define print(val) printf(#val " is here\n") // "Ian" " is here" = "Ian is here"

void printHello() {
	printf("hello\n");
}

int main(int argc, char const *argv[])
{
	int a = 100, b = 101;
	char cstring[] = "string";

	fprintf(stderr, "find max value w/ macr: %d\n", max(a++, b++));
	fprintf(stderr, "After macro: %d\n", b); // add twice thus the value would be 103
	fprintf(stderr, "square: %d\n", square(3 + 1)); // test paranthesis to make sure right answer
	// test for macro concatenation
	fprintf(stderr, "%s\n", string);
	// test for undef
	printHello();
	print(Ian);
	return 0;
}