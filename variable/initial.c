/*
	Purpose: Testing Initialization issue on the following
		1. global initialization must be constant
		2. global variable without explicit declaration would be 0
		3. automatic variable without explicit declaration would have garbage value
		4. array of char size
*/
#include <stdio.h>
#include <string.h>

int global_var;
//int global = global_var * 30 * 10;

int main(int argc, char const *argv[])
{
	int local_var;
	int local = local_var * 10 * 20;
	char string[] = "Ian";

	printf("global_var: %d\n", global_var);
	printf("local: %d\n", local_var);

	// for string
	printf("strlen: %lu\n", strlen(string)); // strlen would not cout /0
	printf("sizeof: %lu\n", sizeof(string)); // sizeof would count /0
	return 0;
}