/**
 * This program aims to test different conditions for extern
    * simply extern a variable (only declare, not define, meaning no memory allocation)
    * extern without including source.h (where extern etually place)
    * extern with including source.h
    * extern with including source.h and change value
**/

/** key concept
 * with only declation, extern variable would not allocate memory
 * the use of extern is not needed in function declarations or definitions. Its use is implicit.
 * extern variable is declared with initialization, it's the definition of variable
 * */

#include <stdio.h>

extern int source_var;

int main(int argc, char **argv) {
    source_var = 30;
    printf("source var is %d\n", source_var);
    return 0;
}