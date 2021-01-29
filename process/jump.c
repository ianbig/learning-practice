#include <stdio.h>
#include <setjmp.h>

jmp_buf jmpbuffer;

int func_stack_2() {
	int c = 0;

	if(c) {
		fprintf(stderr, "succees\n");
	} else {
		longjmp(jmpbuffer, 2);
	}

	return 0;
}

int func_stack_1() {
	int b = 1;

	if(b) {
		func_stack_2();
	}

	if(!b) {
		longjmp(jmpbuffer, 1);
	}

	return 0;
}



int main() {
	 int a = 0;
	 int ret = 0;

	 if((ret = setjmp(jmpbuffer) ) != 0) {
	 	if(ret == 1) {
	 		fprintf(stderr, "Return from stack 1\n");
	 	} else if(ret == 2) {
	 		fprintf(stderr, "Return from stack 2\n");
	 	} else {
	 		printf("Error in setting jump\n");
	 	}
	 	return 0;
	 }

	 if(!a) {
	 	func_stack_1();
	 }
}