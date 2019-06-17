#include "shumaguan.h"
uchar code smgduan[10] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
void delay(uint i)
{
	while(i--);	
}
void DisPlay(uchar dat,uchar i)
{
	switch(i)
	{
		case(0):
			LSA=0;LSB=0;LSC=0;break;
		case(1):
			LSA=1;LSB=0;LSC=0;break;
		case(2):
			LSA=0;LSB=1;LSC=0;break;
		case(3):
			LSA=1;LSB=1;LSC=0;break;
		case(4):
			LSA=0;LSB=0;LSC=1;break;
		case(5):
			LSA=1;LSB=0;LSC=1;break;
		case(6):
			LSA=0;LSB=1;LSC=1;break;
		case(7):
			LSA=1;LSB=1;LSC=1;break; 
	}
	if(i==2)
		P0 = smgduan[dat]|0x80;
	else
		P0 = smgduan[dat];
//	if(dat == 20)
//		P0 = 0x40;
//	else
//	{
//		if(dat > 9 || dat < 0)
//			P0 = 0x40;
//		P0 = smgduan[dat];
//	}

//	switch(dat)
//	{
//		case(0):
//			P0 = smgduan[0];break;
//		case(1):
//			P0 = smgduan[1];break;
//		case(2):
//			P0 = smgduan[2];break;
//		case(3):
//			P0 = smgduan[3];break;
//		case(4):
//			P0 = smgduan[4];break;
//		case(5):
//			P0 = smgduan[5];break;
//		case(6):
//			P0 = smgduan[6];break;
//		case(7):
//			P0 = smgduan[7];break;
//		case(8):
//			P0 = smgduan[8];break;
//		case(9):
//			P0 = smgduan[9];break;
//		default:
//			P0 = 0x40;
//	}
	
	delay(100);
	P0 = 0x00;

}