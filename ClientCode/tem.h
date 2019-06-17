#ifndef __TEM_H__
#define __TEM_H__

#include "reg52.h"

#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint
#define uint unsigned int
#endif

sbit DSP = P3^7;

int DS18B20ReadTemp();
int DealTemp(int temp);


#endif