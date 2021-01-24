/*
	Purpose: This file intend to test the scope of static global variable.
	Relating File: header.h invalid_access.c
*/

#include <stdio.h>
#include "header.h"

int global = 20; // static keyword can be comment out to see the compliation result

int main() {
	printf("global file: %d\n", global);
	invalid_access();
}