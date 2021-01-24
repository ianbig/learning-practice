#include <stdio.h>
#include "header.h"

// extern int global; uncommment for testing global
int global = 0;

static int limited_scope_function() {
	fprintf(stderr, "Inside limited_scope_function\n");
	return 0;
}

void invalid_access() {
	global = 30;
	limited_scope_function();
	//printf("invalid_access: %d\n", global);
}
