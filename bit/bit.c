/**
 * bit operation only on intergal type
 * how to mask bit
 * how to set on bit
 * testing machine right shift is arithmetic shift or logic shift: fortunately is arithmatic shift 
**/

#include <stdio.h>

#define MAX_BINARY_LINE 1000
#define MASK 077

typedef struct {
    int real;
    int psed;
} REAL_S;

// incompetent in dealing with negative number
void get_binary_form(int num) {
    char binary[MAX_BINARY_LINE] = {0};
    int index = 0;

    while (num > 1 || num < -1)
    {   
        binary[index++] = num % 2;
        num = num / 2;
    }
    binary[index] = 1;

    for(int i = index; i > -1; i--) {
        printf("%d ", binary[i]);
    }
    printf("\n");
}


int main() {

    // section for test bit operation on intergral type
    REAL_S real_1, real_2;

    real_1.real = 10;
    real_1.psed = 10;

    real_2.real = 20;
    real_2.psed = 30;
    /* only allow intergral type: int, short, long, double, float */
    // REAL_S and =  real_1 & real_2;
    // section for testing mask off 6 bits
    int maskee = 0777;
    fprintf(stderr, "Before Masking: ");
    get_binary_form(maskee);
    fprintf(stderr, "After Masking: ");
    int mask_result = maskee & MASK;
    get_binary_form(mask_result);
    // section for turning bits on
    int setee = 5;
    fprintf(stderr, "Before On: ");
    get_binary_form(setee);
    fprintf(stderr, "After On: ");
    int set_result = setee | MASK;
    get_binary_form(set_result);
    // section for testing right shift on signed number
    signed int sign_number = 6;
    fprintf(stderr, "right shifting 1 bit for %d: \n", ~sign_number + 1); // for two's complement
    fprintf(stderr, "right shifting 1 bit for %d: \n", (~sign_number + 1) >> 1); // for two's complement
}
