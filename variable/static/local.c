#include <stdio.h>

void store_static_var() {
	// int static a = 10;
	static int a = 10;
	a++;
	fprintf(stderr, "%d\n", a);
}

int main() {
	store_static_var();
	store_static_var();
	store_static_var();
	store_static_var();
	store_static_var();

}