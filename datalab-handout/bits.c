/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
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
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
    return ~(~x|~y);
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
    x>>=n<<3;
    x=x&0xff;//bitmask
    return x;
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
    int bitMask=~((1<<31)>>(n+~0));
    int tmp=((!n)<<31)>>31;
    bitMask=bitMask|tmp;
    x=x>>n;
    return x&bitMask;
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
  int count;
 
    int bitmask1=(0x55) | (0x55 << 8);
    int mask1 = (bitmask1) | (bitmask1 << 16); //得到掩码 01010101...01010101
 
    int bitmask2 = (0x33) | (0x33 << 8);
    int mask2 = (bitmask2) | (bitmask2 << 16); //得到掩码 00110011...00110011
 
    int bitmask3 = (0x0f) | (0x0f << 8);
    int mask3 = (bitmask3) | (bitmask3 << 16);//得到掩码  00001111...00001111
 
    int mask4 = (0xff) | (0xff <<16); //得到掩码  0000 0000 1111 1111 0000 0000 1111 1111
 
    int mask5 = (0xff) | (0xff << 8);//得到掩码： 0000 0000 0000 0000 1111 1111 1111 1111
 
    count = (x & mask1) + ((x >> 1) &mask1);
    count = (count & mask2) + ((count >> 2) & mask2);
    count = (count & mask3) + ((count >> 4) & mask3);
    count = (count & mask4) + ((count >> 8) & mask4);
    count = (count & mask5) + ((count >> 16) & mask5);
    return count;
}
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
    return ((x>>31&1)|(((~x+1)>>31)&1))^1;
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
    return 0x1<<31;
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
 
/*int fitsBits(int x, int n) {
  int mask = x >> 31;
  return !(((~x & mask) + (x & ~mask)) >> (n + ~0));
}*/

int fitsBits(int x,int n){
    if(n==0x20)return 0;
    int shiftBits=32+(~n+1);//32-n
    return !(x^((x<<shiftBits)>>shiftBits));
}

/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
    int bitmask=x>>31;//符号位拓展
    int bias=(1<<n)+~0;
    return (x+(bias&bitmask))>>n;/*如果是正数，bitmask全为0，将bias掩盖，如果是负数，bitmask全为1，bias保留*/
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
    return ~x+1;
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x){
    int bitmask=((!!x)<<31)>>31;
    return (!(x>>31))&bitmask;
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y)
{
   int signx=(x>>31)&0x1;//the first n-1 set 0
   int signy=(y>>31)&0x1;
   int isSame=!(signx^signy);
   int sign=!((y+(~x)+1)>>31);
   int bias=!(y+(~x)+1);
   int ans=((isSame & sign)) | (!isSame & signx);
   return ans;
}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {
  int tmp=0,q=0;
    /*
    * at first,q=0
    * use binary search,if x[31:16]!=0,x>>!=0,!!(x>>16)=1,q=16
    * else if x[31:16]=0,that x[15:0]!=0,q=0 
    * and so on
    */
    tmp=(!!(x>>16))<<4;
    x>>=tmp;
    q|=tmp;//q+tmp, let q grow

    tmp=(!!(x>>8))<<3;
    x>>=tmp;
    q|=tmp;

    tmp=(!!(x>>4))<<2;
    x>>=tmp;
    q|=tmp;

    tmp=(!!(x>>2))<<1;
    x>>=tmp;
    q|=tmp;

    tmp=(!!(x>>1));
    x>>=tmp;
    q|=tmp;

    return q;
}
/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
    unsigned int temp=uf&0x7FFFFFFF;//将符号位变为0
    unsigned int result=uf^0x80000000;//取负
    if(temp>0x7F800000)//为NAN
        result=uf;
    return result;
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
 
unsigned float_i2f(int x){
	if(x==0x0)return 0;
	if(x==0x80000000)return 0xcf000000;
	
    int sign=(x>>31)&0x01;
	int frac_mask=(1<<23)-1;//这是尾数的掩码
	int frac=0,exp=0;
	int pos=30;//第一个为1的位置
	int round=0;
	
	if(sign)x=-x;//求绝对值
	while(!(x>>pos))pos--;
	exp=pos+127;//阶码
	x=x<<(31-pos);//将x移到最高位
	frac=(x>>8)&frac_mask;//得到尾数
	x=x&0xff;
	round=x>0x80||((x==0x80)&&(frac&0x01));//余项
	frac+=round;
	if(frac>>23){//如果frac加上round后大于23为，则阶码加一
	    exp+=1;
            frac=frac&frac_mask;
	}
	return (sign<<31)|(exp<<23)|frac;
}
 
 
 


/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
/*unsigned float_twice(unsigned uf){
    unsigned int x=uf;
    //uf----->ieee float uf

    unsigned result=0,absx,round;
    result=x&(1<<31);//取符号位
    if(result)absx=-x;//取绝对值
    else absx=x;

    unsigned E=0;//order
    unsigned tail=absx;
    for(int i=1;i<=32;i++){
        if((absx&0x80000000)){
            E=32;
            break;
        }
        if(!(absx>>i)){
            E=i;
            break;
        }
    }
    --E;// index of max =7,E=6
    //求尾数
    tail=absx<<(31-E)<<1;//舍弃第一位
    round=tail<<23>>23;
    tail>>=9;
    E=(E+127)<<23;
    //舍入
    if(round>0x100)round=1;
    else if(round<0x100)round=0;
    else round=tail&1;

    result=result|tail|E+round;

    return result;
}*/

unsigned float_twice(unsigned uf){
    if(!uf)return 0x0;
    int sign=uf>>31&&0x01;//符号位
    int exp=uf>>23&0xff;//阶码
    
    int frac=uf&0x7fffff;//尾数
    if(exp!=0xff){//不为NaN
    	if(!exp)frac=frac<<1;//阶码为0
    	else{
            exp+=1;
            if(exp==0xff){
                frac=0;
            }
        }
    }    
    return sign<<31|exp<<23|frac;
}





