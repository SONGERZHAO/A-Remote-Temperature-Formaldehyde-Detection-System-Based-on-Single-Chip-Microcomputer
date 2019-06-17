#include "ZE08.h"
void delay500msZE08(void)   //误差 0us
{
    unsigned char a,b,c;
    for(c=23;c>0;c--)
        for(b=152;b>0;b--)
            for(a=70;a>0;a--);

}
void us_delayZE08(uchar t)
{
      while(t--);
}
void InitZE08()
{
 	TMOD |=0x20;//定时器1启动  高位控制定时器1 ，低位控制定时器0
	TH1 = 0xfa;//波特率9600
	TL1 = 0xfa;
	PCON = 0x80;//设置波特率的一个倍数		   	
	SCON = 0x50;
	EA=1;
	ES=1;
	TR1 = 1;   //定时器1开始工作
}
void SendByteZE08(uchar dat)
{
	ES = 0;//关闭串口中断
	TI = 0;
	SBUF = dat;				   
	while(!TI);
	TI = 0;
	ES = 1;
	
}
void SendarrZE08(uchar str[],uchar num)
{
	uchar i = 0;
	for(i=0; i<num; i++)
	{
		SendByteZE08(str[i]);
	   	us_delayZE08(5);
	}
}
void GetData()//发送应答指令
{
	uchar arr[9] = {0xff,0x01,0x86,0x00,0x00,0x00,0x00,0x00,0x79};
	InitZE08();
	SendarrZE08(arr,9);
	delay500msZE08();
}