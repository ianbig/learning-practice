#include <stdio.h>

void paraFunc(a) 
{
    printf("a: %d\n", a);
}


int main(int argc, char **argv) {
    int a = 12;
    paraFunc(a);
    return 0;
}
