#include <stdio.h>

void paraFunc(a);
int a;

void paraFunc(a) {
    printf("a: %d\nb: %d\nc: %d\n", a);
}


int main(int argc, char **argv) {
    int a = 12;
    paraFunc(a);
    return 0;
}
