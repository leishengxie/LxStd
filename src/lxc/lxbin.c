//and 1 //判断奇数偶数
//or 1 //最近奇数偶数
//not unsign int a //上界-a
//xor 1 //某位取反
//（a xor b) xor b = a //交换
//a shl 1 //乘2
//a shr 1 //除2
#include "lxbin.h"
#include <stdio.h>
#include <stdbool.h>

//#include <iostream>

//register char *g_strRegiseter;
//char *g_strRegiseter = "usually used";

int getMaxInt()
{
    return (1 << 31) - 1;//2147483647
    //or
    //return ((unsigned int) - 1) >> 1;//214748364
}


int getMinInt()
{
    return 1 << 31;//-2147483648
}

long getMaxLong()
{
    return ((unsigned long) - 1) >> 1;//2147483647
}

int mulTwo(int n)
{
    return n << 1; //n*2
}

int divTwo(int n)
{
    return n >> 1;  //n/2
}

int mulTwoPower(int n,int m)
{
    return n << m; //n*(2^m)
}

int divTwoPower(int n,int m)
{
    return n >> m; //n/(2^m)
}

bool isOddNumber(int n)
{
    return (n & 1) == 1;
}

void swap(int *a,int *b)
{
    (*a) ^= (*b) ^= (*a) ^= (*b);
    //or
    //    a ^= b;
    //    b ^= a;
    //    a ^= b;
}

/* n>>31 取得n的符号，若n为正数，n>>31等于0，若n为负数，n>>31等于-1
若n为正数 n^0=0,数不变，若n为负数有n^-1 需要计算n和-1的补码，然后进行异或运算，
结果n变号并且为n的绝对值减1，再减去-1就是绝对值 */
int abs(int n)
{
    return (n ^ (n >> 31)) - (n >> 31);
}

/*如果a>=b,(a-b)>>31为0，否则为-1*/
int max(int a,int b)
{
    return b & ((a-b) >> 31) | a & (~(a-b) >> 31);
    //or
    //return x ^ ((x ^ y) & -(x < y));
}

int min(int a,int b)
{
    return a & ((a-b) >> 31) | b & (~(a-b) >> 31);
    //or
    //return y ^ ((x ^ y) & -(x < y));
}

bool isSameSign(int x, int y)
{ //有0的情况例外
    return (x ^ y) >= 0;
}

int getFactorialofTwo(int n)
{//n > 0
    return 2 << (n-1);//2的n次方
}


bool isFactorialofTwo(int n)
{
    return n > 0 ? (n & (n - 1)) == 0 : false;
}


int quyu(int m,int n)
{//n为2的次方
    return m & (n - 1);

}

int getAverage(int x, int y)
{
    return (x + y) >> 1;
}

//从低位到高位,取n的第m位
int getBit(int n, int m)
{
    return (n >> (m-1)) & 1;
}

//从低位到高位.将n的第m位置1
/*将1左移m-1位找到第m位，得到000...1...000
  n在和这个数做或运算*/
int setBitToOne(int n, int m)
{
    return n | (1 << (m-1));
}

//从低位到高位,将n的第m位置0
int setBitToZero(int n, int m)
{
    return n & ~(1 << (m-1));
    /* 将1左移m-1位找到第m位，取反后变成111...0...1111
       n再和这个数做与运算*/
}

/*
 *
 *
 *
 */

int add1(int n)
{
    return -~n;
}

int sub1(int n)
{
    return ~-n;
}

int getOpposite(int n)
{
    return ~n + 1;
}





