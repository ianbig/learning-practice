#include <stdio.h>
#include "header.h"

int limited_scope_function();

int main() {
	invalid_access();
	limited_scope_function();
}