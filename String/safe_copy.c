#include<string.h>
#include<stdlib.h>
#include <stdio.h>

int main() {
    char src[] = "I am ian";
    char des[2];
    int desSafeLength = sizeof(des) / sizeof(char);

    snprintf(des, sizeof(des)/sizeof(char), "%s", src);
    printf("des: %s\nsrc: %s\n", des, src);
}
