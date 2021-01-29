#include <stdio.h>

typedef struct {
	int mem;
} POINTER_ARG_S;

void test_void(void *arg) {
	int *fun_ptr = (int *)arg;
	// fun_ptr += 2;
	// int content = *fun_ptr;
	int content = (int)arg;
	arg += 1;
	content = (int)arg;

	fprintf(stderr, "Inside Func: %d\n", content);

	// arg += 1;

	// fprintf(stderr, "addr: %p\n", arg);
	// fprintf(stderr, "content: %d", content);
}

int main() {
	int a = 105;
	int arr[3] = {101, 102, 103};
	int *main_ptr = arr;
	POINTER_ARG_S arg;
	// Test passing value
	test_void(a);
	fprintf(stderr, "Inside Main: %d\n", a);
	// Test Passing address
	// test_void(&a);
	// test_void(main_ptr);
	// fprintf(stderr, "main items: %d\n", *main_ptr);
}

/*
	Conclusion
	 1. pass value enable
	 2. pass address enable
	 3. but all would be seen as address to handle
*/