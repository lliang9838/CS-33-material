/* 
 * CS:APP Data Lab 
 * 
 * Leslie Liang 204625818
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/*
 * isTmin - returns 1 if x is the minimum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmin(int x) 
{
  int temp = x^(~x+1); //condition to check if it's Tmin
  return !(!x + (temp)); //the !x checks if my x is 0!
}
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {

  int a = x & y; //using the & operator
  int b = ~x & ~y;//also known as nor operator

  //with trial and error, we see that if we nor again, we can "XOR"
  
  return (~a & ~b);//if we nor again, we get xor


}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x)
{
  //Since I can't simply declare 0xAAAAAAAA
  //I'm going to need to play around with shifts to make my 0xAAAAAAAA mask

  int a = 0xAA << 8; //just trying to make the mask
  a = (a + 0xAA) << 8; //making the mask
  a = (a + 0xAA) << 8; //making the mask
  a +=0xAA; //.....
  
  //use the & operator for the mask to only extract the 1's in the odd's place

  return !((x&a)^a); //if we have 1's in odd pos, then this func returns true

}


/* 
 * sign - return 1 if positive, 0 if zero, and -1 if negative
 *  Examples: sign(130) = 1
 *            sign(-23) = -1
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 10
 *  Rating: 2
 */
int sign(int x)
{
  //should have a condition here to check if x is neg
  
  //need to check this guy

  // int y = 1 << 31;
  // int save = x & y;
  // save >> 31;
  
  int msb = x >> 31;
  //msb takes care of the sign
  //!x & 1 will be 1 if x is 0, and we NOT that again to get 1

  return (   msb   | !(!x & 1));

  
}
/* 
 * allEvenBits - return 1 if all even-numbered bits in word set to 1
 *   Examples allEvenBits(0xFFFFFFFE) = 0, allEvenBits(0x55555555) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allEvenBits(int x) 
{
  int a = 0x55 << 8; //very similar approach to allOddBits
  a = (a + 0x55) << 8;
  a = (a + 0x55) << 8;
  a +=0x55;
  
  

  return !((x&a)^a); 

}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) 
{
  int num = n << 3; //basically the same as multiplying by 8 
  int shift = x >> num; //shift the byte that we want to the front

  return ( shift & 0xFF); //everything in front of FF is zero, only extract what we want


  
}
/* 
 * isNonNegative - return 1 if x >= 0, return 0 otherwise 
 *   Example: isNonNegative(-1) = 0.  isNonNegative(0) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int isNonNegative(int x)
{
  int shift = x >> 31; //check the sign bit



  return ( !(shift)); //return whatever the sign bit is, and invert it
  

}
/* 
 * rotateRight - Rotate x to the right by n
 *   Can assume that 0 <= n <= 31
 *   Examples: rotateRight(0x87654321,4) = 0x76543218
 *   Legal ops: ~ & ^ | + << >> !
 *   Max ops: 25
 *   Rating: 3 
 */
int rotateRight(int x, int n) 
{
 

  int shifted = x >> n; //shift it by that many "n" bits to the right
  int save = x << (32 +(~n+1)); //shift it back by that many bits to the left

  //now I need to mask the shifted so that I can perform a right shift "logically"

  int update = shifted & ~( (~0) << (32+(~n+1))); //this makes it so that my right shift is always "logical" instead of arithmetic, funny things happen when its arith. shift
  
  int final = update | save;

  return final; //return final

}
/*
 * isPower2 - returns 1 if x is a power of 2, and 0 otherwise
 *   Examples: isPower2(5) = 0, isPower2(8) = 1, isPower2(0) = 0
 *   Note that no negative number is a power of 2.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int isPower2(int x) 
{

  //if a num is a power2, then that # -1 would be all 1's after
  // x & (x-1) should yield all zero's, logical invert that should give true

  int save = !(x&(x+(~1+1))); //checking if it's a power of 2

  int isPositive = !((x&(1<<31))| !x); //the number has to be positive

  int combine = save & isPositive;//combine these two

  return combine;//return 'em


} 
/* 
 * sm2tc - Convert from sign-magnitude to two's complement
 *   where the MSB is the sign bit
 *   Example: sm2tc(0x80000005) = -5.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 4
 */
int sm2tc(int x) 
{

  //int mask = 1 << 31;
  //int neg = (mask & x) >> 31;
  // int pos = ~neg;
  // int sign = mask & x;

  


   int mask = x >> 31; //creating a mask of sign bit
  
   mask = ~mask; //flip the bits for the mask

   //int temp = 1<<31; // creating a mask 1000 ... 0000, funny stuff happens <<

  //int positive = mask & x; //this side only works for positives
  //int negative = ((x & temp) +(~x+1)) & ~mask;

   return ((mask&x)|(((1<<31)&x)+(~x+1))&~mask); //left side is for pos, right side for neg



  


}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x)
{
  
  int search =0; //need to declare everything before the actual code runs
  
  x = x ^ (x>>31); // is negative, complement it 
  x = x | (x>>1); //fill everything to the right of my sign 1 bit with 1's
  x = x | (x>>2); //same thing as the line before
  x = x | (x>>4); //same thing as the line before
  x = x | (x>>8); //same thing as the line before
  x = x | (x>>16); // same thing as the line before

  //logarithmic search

  search = (!!(x>>16))<<4; //binary process of counting the number of leading 0's
  search += (!!(x>>(search+8)))<<3; //shift right 16 bits and see if it's equal to 0
  search += (!!(x>>(search+4)))<<2; //shift right 8 more
  search += (!!(x>>(search+2)))<<1; //shift 4
  search += (!!(x>>(search+1))); //shift 2
  search += (!!search) + (!(1^x)) + 1; //then 1

  return search;


}
