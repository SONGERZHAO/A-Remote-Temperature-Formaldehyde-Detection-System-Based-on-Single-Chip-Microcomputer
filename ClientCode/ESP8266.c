#include"ESP8266.h"

void us_delay(uchar t)
{
      while(t--);
}

void InitESP8266()//11.0592
{
 	TMOD |=0x20;  //定时器1启动  高位控制定时器1 ，低位控制定时器0
	TH1 = 0xf4;	  //波特率4800
	TL1 = 0xf4;
	PCON = 0x80;	//设置波特率的一个倍数		   	
	SCON = 0x50;
	EA=1;		// 运行模式 01 模式1，   01 允许接收置1
//	ES=1;
	TR1 = 1;   //定时器1开始工作
}
void SendByte(uchar dat)
{
//	ES = 0;//关闭串口中断
	TI = 0;
	SBUF = dat;				   
	while(!TI);
	TI = 0;
//	ES = 1;
}
void SendString(uchar * str)
{
	while(*str != '\0')
	{
		SendByte(*str);
	   	us_delay(5);
		str++;
	}
}
void Sendarr(uchar str[],uchar num)
{
	uchar i = 0;
	for(i=0; i<num; i++)
	{
		SendByte(str[i]);
	   	us_delay(5);
	}
}
