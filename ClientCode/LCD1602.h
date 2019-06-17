#ifndef __LCD1602_H__
#define __LCD1602_H__
#include "reg52.h"

#ifndef uchar
#define uchar unsigned char 
#endif

#ifndef uint
#define uint unsigned int 
#endif


sbit LCD_E = P2^7;
sbit LCD_RW = P2^5;
sbit LCD_RS = P2^6;
void LCD_Init();
void LCD_WriteData(uchar dat);
void LCD_WriteCom(uchar com);
void LCD_WriteString(uchar * p);

#endif