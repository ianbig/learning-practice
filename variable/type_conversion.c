/**
 * 
 * Testing case
    * type conversion during artihmatic: not validate yet
    * type conversion in assignment
    * unsigned and signed data assign to char: not validate yet
    * type conversion between signed and unsigned when comparing
 * Result
   * type conversion between signed and unsigned when comparing: small to big, singed to unsigned
   * type conversion in assignment: right convert to left
**/

#include <stdio.h>

#define INT_CONST 1 << 2
#define LONG_CONST 12345.123

void type_convert(char character, float float_num) {
   printf("Inside function char is %lu, float is %lu\n", sizeof(character), sizeof(float_num));
}

int main() {
   int int_num = INT_CONST;
   double long_num = LONG_CONST;
   double long_sum = long_num + int_num;

   int drop_precision = long_num;
   double extend_precision = int_num;
   
   printf("double sum is %f and size: %lu\n", long_sum, sizeof(long_sum));
   printf("sizeof int_num: %lu\n", sizeof(int_num));
   printf("drop precision: %d\n", drop_precision);
   printf("extend precision: %f\n", extend_precision);

   // section for char
   signed int num_signed = 0xfff;
   unsigned int num_unsigned = 0xf;
   char neg_bit = num_unsigned;

   printf("unsigned number: %d\n", num_unsigned);
   printf("signed number: %d\n", num_signed);
   printf("%d\n", neg_bit);

   // section for comparison
   if( -1L < 1U ) {
      printf("-1U < 1L\n");
   } // 1U be converted to signed long since principal of small conversion

   if( -1L > 1UL) {
      printf("-1L > 1UL\n");
   } // -1L be converted to unsigned long

   type_convert(neg_bit, (float)0.123);

}