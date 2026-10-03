/* 
 * CS:APP Data Lab 
 * 
 * 吴世强 24300810019
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
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.
  4. Interprets integer expressions using the Data Lab 32-bit bit-vector
     model: results outside the signed range retain their low 32 bits.


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

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

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
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
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
#include "bits.h"

// P1
/* 
 * signMask - return a mask with only the most significant bit set (0x80000000)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int signMask(void) {
  return 1 << 31;
}

// P2
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1, bitXor(7, 7) = 0
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 2
 */
int bitXor(int x, int y) {
  int x_ny = x & ~y;
  int nx_y = ~x & y;
  return ~(~x_ny & ~nx_y);
}

// P3
/*
 * negativePart - return -x if x < 0, otherwise return 0
 *   Examples: negativePart(-10) = 10, negativePart(5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int negativePart(int x){
  int mask = x >> 31;
  int neg = ~x + 1;
  return mask & neg;
}


// P4
/*
 * copyByteWithin - copy byte src of x to byte dst, leaving all other bytes unchanged
 *   Bytes are numbered from 0 (least significant) to 3 (most significant).
 *   You can assume 0 <= src <= 3 and 0 <= dst <= 3.
 *   Example: copyByteWithin(0x11223344, 0, 2) = 0x11443344
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int copyByteWithin(int x, int src, int dst) {
  // get the byte that is from source
  int byte = (x >> (src << 3)) & 0xFF;
  // clean the destination source from the number
  int mask = ~(0xFF << (dst << 3));
  int masked_x = mask & x;
  return masked_x | (byte << (dst << 3)); 
}

// P5
/* 
 * logicalShift - shift x to the right by n bits, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int logicalShift(int x, int n) {
  // mask 的高 n 位全是 0， 低 32 - n 位全是 1
  int mask = ~(((1 << 31) >> n) << 1);
  return (x >> n) & mask;
}

// P6
/*
 * swapNibblePairs - swap the low and high 4 bits within each byte of x
 *   Examples: swapNibblePairs(0xAB) = 0xBA
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 18
 *   Rating: 4
 */
int swapNibblePairs(int x) {
  int mask = (0x0F << 24) | (0x0F << 16) | (0x0F << 8) | 0x0F;
  return ((x >> 4) & mask) | ((x & mask) << 4);
}

// P7
/*
 * secondLowestZeroBit - return a mask that marks the position of the second least significant 0 bit
 *   Examples: secondLowestZeroBit(0xFFFFFFFA) = 0x4, secondLowestZeroBit(0x7FFFFFFF) = 0
 *             secondLowestZeroBit(-1) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 4
 */
int secondLowestZeroBit(int x) {
  /* x + 1 负责把第一个0之后的所有1全部清成0, 然后我们这个第一个0变成1
  注意到，如果我们对于 x 来进行 ~ 操作，那么第一个0变成1，前面所有位都和 x 相反，也就和 x + 1 相反
  然后再进行 & 操作，我们就得到了只有最低一位是0的这个掩码
  */
  int lowest_zero_mask = (~x) & (x + 1);
  /* 然后我们把这个最低位的0变成1*/
  int x1 = x ^ lowest_zero_mask;
  /* 重复一次取掩码操作，得到第二个最低位的0的掩码*/
  return (~x1) & (x1 + 1);
}

// P8
/*
 * oddParity - return the odd parity bit of x, that is,
 *      when the number of 1s in the binary representation of x is even, then the return 1, otherwise return 0.
 *   Examples: oddParity(5) = 1, oddParity(7) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 56
 *   Rating: 5
 */
int oddParity(int x) {
  /* 我们把 x 分成两部分，每部分16位，然后我们分别计算每部分的奇偶性*/
  int up_16bit = (x & ((0xFF << 24) | (0xFF << 16))) >> 16;
  int down_16bit = x & ((0xFF << 8) | 0xFF);
  int half = up_16bit ^ down_16bit;
  
  /* 我们把 half 分成两部分，每部分8位，然后我们分别计算每部分的奇偶性*/
  int up_8bit = (half & ((0xFF << 8))) >> 8;
  int down_8bit = half & (0xFF);
  int quarter = up_8bit ^ down_8bit;
  
  /* 我们把 quarter 分成两部分，每部分4位，然后我们分别计算每部分的奇偶性*/
  int up_4bit = (quarter & (0xF0)) >> 4;
  int down_4bit = quarter & 0xF;
  int eighth = up_4bit ^ down_4bit;

  /* 我们把 eighth 分成两部分，每部分2位，然后我们分别计算每部分的奇偶性*/
  int up_2bit = (eighth & (0xC)) >> 2;
  int down_2bit = eighth & 0x3;
  int sixteenth = up_2bit ^ down_2bit;

  /* 我们把 sixteenth 分成两部分，每部分1位，然后我们分别计算每部分的奇偶性*/
  int up_1bit = (sixteenth & (0x2)) >> 1;
  int down_1bit = sixteenth & 0x1;
  int thirty_second = up_1bit ^ down_1bit;

  return (thirty_second & 0x1) ^ 1;
}

// P9
/* 
 * rotateRightBits - rotate x to right by n bits
 *   you can assume n >= 0
 *   Examples: rotateRightBits(0x12345678, 8) = 0x78123456
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 5
 */
int rotateRightBits(int x, int n) {
  int thirtytwo_minus_n = 0x20 + (~n + 1);
  /*最低的 n 位都是 1 的mask*/
  int mask = (1 << n) + ~0;
  /*最高的 n 位是 0 的mask*/
  int high_mask = ~(((1 << 31) >> n) << 1);

  int masked_x = mask & x;

  return ((x >> n) & high_mask) | (masked_x << thirtytwo_minus_n);
}

// P10
/*
 * roundEvenPow2 - round nonnegative x to the nearest multiple of 2^n.
 *   If x is exactly halfway between two multiples, choose the multiple whose
 *   quotient by 2^n is even.
 *   You can assume 0 <= x <= 0x3fffffff and 1 <= n <= 16.
 *   Examples: roundEvenPow2(10, 2) = 8, roundEvenPow2(14, 2) = 16
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 5
 */
int roundEvenPow2(int x, int n) {
  /* 低 n 位是余数 r，half 是 2^(n-1) */
  int mask = (1 << n) + ~0;
  int r = x & mask;
  int half = 1 << (n + ~0);
  int q = x >> n;
  /* 正好在中点、且向下的商是奇数时才额外进 1 */
  int tie_up = (!(r ^ half)) & (q & 1);
  int bias = half + ~0 + tie_up;
  return ((x + bias) >> n) << n;
}

// P11
/* 
 * midpointTowardFirst - return the exact mathematical midpoint (x+y)/2
 *   without overflow. If the exact midpoint lies halfway between two
 *   integers, choose the adjacent integer that is closer to the first
 *   argument x.
 *   Examples: midpointTowardFirst(4, 7) = 5,
 *             midpointTowardFirst(7, 4) = 6
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 32
 *   Rating: 5
 */
int midpointTowardFirst(int x, int y) {
  /* 算术右移是向下取整，两数都是奇数时最低位还要补一个进位 */
  int floor_mid = (x >> 1) + (y >> 1) + ((x & y) & 1);
  int odd_sum = (x ^ y) & 1;
  int sign_x = (x >> 31) & 1;
  int sign_y = (y >> 31) & 1;
  int diff_sign = sign_x ^ sign_y;
  int sub = y + (~x + 1);
  int sub_sign = (sub >> 31) & 1;
  /* 符号不同时看 x 是否非负；符号相同时看 y - x 是否为负 */
  int x_gt_y = (diff_sign & !sign_x) | ((!diff_sign) & sub_sign);
  return floor_mid + (odd_sum & x_gt_y);
}


// P12
/* 
 * isBetweenEitherOrder - return 1 when x lies in the inclusive interval whose
 *   endpoints are a and b. The endpoints may be given in either order.
 *   Example: isBetweenEitherOrder(5, 8, 3) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 48
 *   Rating: 7
 */
int isBetweenEitherOrder(int x, int a, int b) {
  int sx = x >> 31;
  int sa = a >> 31;
  int sb = b >> 31;

  int sxa = sx ^ sa;
  int nsxa = ~sxa;
  int nsx = ~sx;
  int dxa = x + (~a + 1);
  /* 掩码为全 1 表示成立。符号不同时不会用可能溢出的差值 */
  int x_ge_a = (sxa & nsx) | (nsxa & ~(dxa >> 31));
  int a_ge_x = (sxa & sx) | (nsxa & ((dxa + ~0) >> 31));

  int sxb = sx ^ sb;
  int nsxb = ~sxb;
  int dxb = x + (~b + 1);
  int x_ge_b = (sxb & nsx) | (nsxb & ~(dxb >> 31));
  int b_ge_x = (sxb & sx) | (nsxb & ((dxb + ~0) >> 31));

  return !!((x_ge_a & b_ge_x) | (x_ge_b & a_ge_x));
}

// P13
/* 
 * mul5Sat - return x*5, and if x*5 overflow, change the result to 
 * INT_MAX(0x7fffffff) or INT_MIN(0x80000000) correspondingly
 *   Examples: mul5Sat(1) = 0x5, mul5Sat(0x40000000) = 0x7fffffff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 7
 */
int mul5Sat(int x) {
  int sign = x >> 31;
  /* 左移 2 位不溢出时，高 3 位必须相同，也就是 x>>29 等于符号掩码 */
  int shift_ov = (x >> 29) ^ sign;
  int prod = (x << 2) + x;
  int add_ov = (prod ^ x) >> 31;
  int ov = !(!shift_ov) | !(!add_ov);
  int sat = sign ^ ~(1 << 31);
  int ov_mask = ~ov + 1;
  return (ov_mask & sat) | (~ov_mask & prod);
}

// P14
/* 
 * classifyAdd3 - classify the exact mathematical sum x+y+z.
 *   Return 1 if the sum is greater than INT_MAX, -1 if it is less than
 *   INT_MIN, and 0 otherwise. You may not use a wider integer type.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 52
 *   Rating: 7
 */
int classifyAdd3(int x, int y, int z) {
  int s1 = x + y;
  int s2 = s1 + z;
  int sx = x >> 31;
  int sy = y >> 31;
  int sz = z >> 31;
  int ss1 = s1 >> 31;
  int ss2 = s2 >> 31;
  /* 正溢出、负溢出的掩码。两步方向相反时正好抵消 */
  int pos = (~sx & ~sy & ss1) | (~ss1 & ~sz & ss2);
  int neg = (sx & sy & ~ss1) | (ss1 & sz & ~ss2);
  pos = (pos >> 31) & 1;
  neg = (neg >> 31) & 1;
  return pos + (~neg + 1);
}

// P15
/*
 * floatScaleThreeHalves - Return bit-level equivalent of expression f*3/2 for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   Use round-to-nearest-even. Preserve the sign of both +0 and -0.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 60
 *   Rating: 7
 */
unsigned floatScaleThreeHalves(unsigned uf) {
  unsigned sign = uf & 0x80000000u;
  unsigned exp = (uf >> 23) & 0xffu;
  unsigned frac = uf & 0x7fffffu;
  unsigned sig;
  unsigned kept;
  unsigned round;

  if (exp == 255u)
    return uf;
  if (!(uf & 0x7fffffffu))
    return uf;

  /* 非规格化数：尾数乘 3 再右移 1 位，向偶舍入。进位到 2^23 时自然变成最小规格化数 */
  if (exp == 0u) {
    sig = frac * 3u;
    kept = sig >> 1;
    if ((sig & 1u) && (kept & 1u))
      kept = kept + 1u;
    return sign | kept;
  }

  sig = (frac | 0x800000u) * 3u;
  if (sig & 0x2000000u) {
    /* 乘完后超过 2^25，阶码加 1，丢掉低 2 位 */
    kept = sig >> 2;
    round = sig & 3u;
    if (round > 2u || (round == 2u && (kept & 1u)))
      kept = kept + 1u;
    exp = exp + 1u;
  } else {
    kept = sig >> 1;
    if ((sig & 1u) && (kept & 1u))
      kept = kept + 1u;
    if (kept == 0x1000000u) {
      kept = 0u;
      exp = exp + 1u;
    }
  }
  if (exp == 255u)
    return sign | 0x7f800000u;
  return sign | (exp << 23) | (kept & 0x7fffffu);
}

// P16
/* 
 * floatRoundEven - round the floating-point value represented by uf to the
 *   nearest integer, with halfway cases rounded to the even integer. Return
 *   the bit-level representation of that integer as a single-precision float.
 *   If rounding produces zero, preserve the input sign; thus a negative
 *   value that rounds to zero returns -0. When uf is NaN or infinity,
 *   return uf unchanged.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 65
 *   Rating: 10
 */
unsigned floatRoundEven(unsigned uf) {
  unsigned sign = uf & 0x80000000u;
  unsigned exp = (uf >> 23) & 0xffu;
  unsigned frac = uf & 0x7fffffu;
  unsigned frac_bits;
  unsigned half;
  unsigned mask;
  unsigned lower;
  unsigned base;
  unsigned lsb;

  if (exp == 255u)
    return uf;
  /* 绝对值小于 0.5，以及恰好等于 0.5，都舍入到带符号的 0 */
  if (exp < 126u)
    return sign;
  if (exp == 126u) {
    if (frac == 0u)
      return sign;
    return sign | 0x3f800000u;
  }
  /* 阶码足够大时，浮点数本身已经是整数 */
  if (exp >= 150u)
    return uf;

  frac_bits = 150u - exp;
  half = 1u << (frac_bits - 1u);
  mask = (half << 1) - 1u;
  lower = frac & mask;
  base = frac & ~mask;
  if (frac_bits == 23u)
    lsb = 1u;
  else
    lsb = (frac >> frac_bits) & 1u;
  if (lower > half || (lower == half && lsb)) {
    base = base + (half << 1);
    if (base >> 23) {
      exp = exp + 1u;
      base = 0u;
    }
  }
  return sign | (exp << 23) | base;
}

// P17
/*
 * float_i2f - Return bit-level equivalent of expression (float) x.
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 40
 *   Rating: 10
 */
unsigned float_i2f(int x) {
  unsigned sign;
  unsigned absx;
  unsigned frac;
  unsigned rest;
  unsigned exp;
  int shift;

  if (x == 0)
    return 0;
  /* -INT_MIN 溢出，2^31 本身可以精确表示 */
  if (x == 0x80000000)
    return 0xcf000000u;
  if (x < 0) {
    sign = 0x80000000u;
    absx = -x;
  } else {
    sign = 0u;
    absx = x;
  }
  shift = 0;
  while ((absx & 0x80000000u) == 0u) {
    absx = absx << 1;
    shift = shift + 1;
  }
  frac = (absx >> 8) & 0x7fffffu;
  rest = absx & 0xffu;
  exp = 158u - shift;
  if (rest > 0x80u || (rest == 0x80u && (frac & 1u))) {
    frac = frac + 1u;
    if (frac == 0x800000u) {
      frac = 0u;
      exp = exp + 1u;
    }
  }
  return sign | (exp << 23) | frac;
}



// P18
/*
 * bitCount - return count of number of 1's in the binary representation of x
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 10
 */
int bitCount(int x) {
  int m1 = 0x55 | (0x55 << 8);
  int m2 = 0x33 | (0x33 << 8);
  int m4 = 0x0f | (0x0f << 8);
  int m8 = 0xff | (0xff << 16);
  int m16 = 0xff | (0xff << 8);
  m1 = m1 | (m1 << 16);
  m2 = m2 | (m2 << 16);
  m4 = m4 | (m4 << 16);
  /* 先掩码再相加，避免算术右移把符号位填进计数值 */
  x = (x & m1) + ((x >> 1) & m1);
  x = (x & m2) + ((x >> 2) & m2);
  x = (x & m4) + ((x >> 4) & m4);
  x = (x & m8) + ((x >> 8) & m8);
  x = (x & m16) + ((x >> 16) & m16);
  return x;
}

// P19
/*
 * bitReverse - Reverse bits in an 32-bit integer
 *   Examples: bitReverse(0x80000004) = 0x20000001
 *             bitReverse(0x7FFFFFFF) = 0xFFFFFFFE
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 34
 *   Rating: 10
 */
int bitReverse(int x) {
  int m8 = 0xff | (0xff << 16);
  int m4 = m8 ^ (m8 << 4);
  int m2 = m4 ^ (m4 << 2);
  int m1 = m2 ^ (m2 << 1);
  int m16 = 0xff | (0xff << 8);
  x = ((x >> 1) & m1) | ((x & m1) << 1);
  x = ((x >> 2) & m2) | ((x & m2) << 2);
  x = ((x >> 4) & m4) | ((x & m4) << 4);
  x = ((x >> 8) & m8) | ((x & m8) << 8);
  return ((x >> 16) & m16) | (x << 16);
}
