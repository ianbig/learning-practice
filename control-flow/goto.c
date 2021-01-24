#include <stdio.h>

#define ARRAY_SIZE 6

int main() {
    int array_1[ARRAY_SIZE] = {1,2,3,4,5,6};
    int array_2[ARRAY_SIZE] = {7,8,3,2,1,6};
    int i = 0, j = 0;

    for(i = 0; i < ARRAY_SIZE; i++) {
        for(j = 0; j < ARRAY_SIZE; j++) {
            if(array_1[i] == array_2[j]) {
                goto found;
            }
        }
    }

    found: {
        printf("haha we find it\n");
        printf("i is %d, j is %d\n", i, j);
    }
}