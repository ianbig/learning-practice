/*
	Purpose: Test some basic concept of pointer
	1. deference pointer
	2. assign pointer to pointer to see
	3. Test array as pointer
	4. Test use negative index within bound of array
*/

#include <stdio.h>

void test_neg_index_in_array_bound(int *ptr) {
	fprintf(stderr, "the -1 index %d\n", ptr[-1]);
}

int main(int argc, char const *argv[])
{	
	// deference void pointer
	int a = 20, b = 30;
	void *ptr = &a;
	// fprintf(stderr, "%d\n", *ptr);
	// assign pointer to pointer
	int *inptr = (int *)ptr;
	fprintf(stderr, "Now ptr point to a: %d\n", *inptr);
	ptr = &b;
	fprintf(stderr, "Now ptr point to b: %d\n", *inptr);
	// array as pointer
	int arr_1[4] = {1, 2, 4, 6};
	int arr_2[4] = {3, 6, 7, 9};
	int *arr_ptr = NULL;

	// arr_1 = &arr_2[3]; invalid

	test_neg_index_in_array_bound(&arr_2[3]);


	return 0;
}