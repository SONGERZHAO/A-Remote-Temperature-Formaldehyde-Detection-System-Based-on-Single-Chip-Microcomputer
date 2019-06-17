#ifndef  __SHUMAGUAN_H__
#define  __SHUMAGUAN_H__

#include "reg52.h"

#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint
#define uint unsigned int 
#endif

sbit LSA = P2^2;
sbit LSB = P2^3;
sbit LSC = P2^4;


void DisPlay(uchar dat,uchar i);


#endif