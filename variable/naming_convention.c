/**
 * Purpose: this file test some naming convention for variable and function
 * What to test
    * letter as first charactier
    * why not _ as first character
**/

#include <stdio.h>
#include "naming_convention.h"

int main() {
    // section for naming _
    printf("before define _source in main: %d\n", _source);
    int _source = 30; // same variable name in stdio.h (why not _ as first character): Because many library file define variable with the start of underscore, by doing so the variable may be overritten by function scope
    printf("after define _source in main:%d\n", _source);
}

// test makefile for adding second file