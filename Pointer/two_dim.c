#include <stdio.h>
#include <stdlib.h>

#define ROW 2
#define COLUMN 3

// the following function would be unable to calculate row number since sizeof(junk) == 8 (pointer size)
/*
size_t calculate_row(int junk[][COLUMN]) {
    size_t number_of_element = sizeof(junk) / sizeof(int); // use int (*)[3]: it is an array of pointer
    fprintf(stderr, "number of element: %lu\n", number_of_element);
    size_t column = sizeof(junk[0])/ sizeof(int);

    return number_of_element/ column;
}
*/

int sum_2d(int junk[][COLUMN], int row) {
    int r = -1;
    int col = -1;
    int sum = 0;

    for(r = 0; r < row; r++) {
        for( col = 0; col < COLUMN; col++) {
            sum += junk[r][col];
        }
    }
    return sum;
} // but this can only calculete column size == COLUMN, what if you need different size

int sum_2d_VLA(int row, int column, int junk[row][column]) {
    int r = -1;
    int col = -1;
    int sum = 0;

    for(r = 0; r < row; r++) {
        for( col = 0; col < column; col++) {
            sum += junk[r][col];
        }
    }
    return sum;
}

void changeArrayItem(int arr[]) {
    arr[0] = 10;
}

int main(int argc, char **argv) {
    int junk[ROW][COLUMN] = {
        {1,2,3},
        {4,5,6}
    };

    // section for checking variable index (allow in c99)
    int index = 30;
    char size_arr[index];
    printf("the number of element: %lu\n", sizeof(size_arr));

    /** section that chage array item via function**/
    int arr[ROW] = {1,2};
    printf("before entering array: %d\n", arr[0]);
    changeArrayItem(arr);
    printf("after entering array: %d\n", arr[0]);

    /** section for calculating 2 dimension array with and without VLA**/
    // int rows = calculate_row( junk ); // faulty value
    int calculate_without_VAL = sum_2d(junk, ROW);
    int calcuate_with_VAL = sum_2d_VLA(ROW, COLUMN, junk);
    printf("sum without VAL:%d\nsum with VAL:%d\n", calculate_without_VAL, calculate_without_VAL);
}