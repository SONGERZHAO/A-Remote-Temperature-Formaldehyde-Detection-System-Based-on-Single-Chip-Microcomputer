#ifndef __ESP8266_H__
#define __ESP8266_H__

#include "reg52.h"

#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint
#define uint unsigned int
#endif

void InitESP8266();
void SendByte(uchar dat);
void SendString(uchar* str);
void Sendarr(uchar str[],uchar i);


#endif