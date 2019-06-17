#include"ESP8266.h"

void us_delay(uchar t)
{
      while(t--);
}

void InitESP8266()//11.0592
{
 	TMOD |=0x20;  //��ʱ��1����  ��λ���ƶ�ʱ��1 ����λ���ƶ�ʱ��0
	TH1 = 0xf4;	  //������4800
	TL1 = 0xf4;
	PCON = 0x80;	//���ò����ʵ�һ������		   	
	SCON = 0x50;
	EA=1;		// ����ģʽ 01 ģʽ1��   01 ���������1
//	ES=1;
	TR1 = 1;   //��ʱ��1��ʼ����
}
void SendByte(uchar dat)
{
//	ES = 0;//�رմ����ж�
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
