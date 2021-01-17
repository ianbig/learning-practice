/**
 * purpose: change global variable with or without extern keyword
 * testing outcome
    * extern keyword can not initialize
    * with in the same source file, extern could help to connect with function
**/

#include <stdio.h>

void change_extern_function(void) {
    extern int g_var;

    g_var = 10;
}

int main( int argc, char **argv) {
    // printf("before declare variable: %d\n", g_var);
    extern int g_var;
    printf("after declare variable: %d\n", g_var);
    g_var = 15;
    printf("after assign 15 value to extern in main: %d\n", g_var);
    change_extern_function();
    printf("after assign 10 value to extern in function: %d\n", g_var);
}

int g_var = 20;