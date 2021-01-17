/**
 * purpose: this file test some constant language concept in c
 * testing case:
    * constant name with suffix 
    * what is \ooo and \xhh
    * enumeration with and without value
 * Conclusion
    * compiler would check whether the precision of value is lost (const long to 1000000000l): Apple clang version 11.0.0 
 * **/

#include <stdio.h>

#define CONST 100
#define CONST_FLOAT 0.01
#define CONST_LONG 1000000000l
#define CONST_BIG_VALUE 10000000000l
#define OCT_CONST 010
#define HEX_CONST 0x11
#define OCT '\011'
#define HEX '\x11'

int main() {

    // section for const name with suffix
    float float_num = CONST_FLOAT;
    int oct_num = OCT_CONST, hex_num = HEX_CONST;
    // int float_num_int = CONST_FLOAT, long_num_int = CONST_LONG;
    long long_num = CONST_LONG;

    printf("floating CONST_FLOAT: %f\n", float_num);
    // printf("int CONST_FLOAT: %d\n", float_num_int);
    printf("OCT_NUM: %d\n", oct_num);
    printf("HEX NUM: %d\n", hex_num);
    printf("long CONST_LONG: %ld\n", long_num);
    // printf("int CONST_LONG: %d\n", long_num_int);

    // section for \ooo and \xhh
    int oct = OCT;
    int hex = HEX;

    printf("oct is %d\n", oct);
    printf("hex is %d\n", hex);

    // section for enumeration
    enum boolean {
        No,
        Yes
    };

    enum super {
        Big_Value = CONST_BIG_VALUE,
    };

    int bool = No;
    // int invalid = Big_Value;
    long valid = Big_Value;
    printf("testing boolean value: %d\n", bool);
    // printf("printing big value: %d\n", invalid);
    printf("printing valid number: %ld\n", valid);
}