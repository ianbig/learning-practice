#include <stdio.h>

do_nothing() {}

int main() {
    printf("return: %ld\n", sizeof(&do_nothing)); // why 1
    sizeof(do_nothing()) == 4 ? printf("do nothing returns a int\n") : printf("do nothing do not return a int\n");
}
