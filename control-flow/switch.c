#include <stdio.h>
#include <stdlib.h>

int main() {
    int input = -1;

    scanf("%d", &input);
    switch(input) {
        case 0: case 1: case 2: case 3:
            printf("I am Ian\n");
            printf("I love cow cow\n");
            break;
        case 5: 
            printf("I am freaking hungry\n");
            printf("funck\n");
            break;
        default:
            printf("I am in default mode\n");
    }
    return 0;
}