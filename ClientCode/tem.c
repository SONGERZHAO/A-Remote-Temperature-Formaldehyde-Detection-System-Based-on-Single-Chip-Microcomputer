#include "tem.h"
sbit led = P2^0;
void Delay1ms(uint y)  //��ʱ����
{
	uint x;
	for(;y>0;y--)
	{
		for(x=110;x>0;x--)
			;
	}
}

void delay640us(void)   //��� 0us
{
    unsigned char a,b;
    for(b=91;b>0;b--)
        for(a=2;a>0;a--);
}
void delay80us(void)   //��� 0us
{
    unsigned char a,b;
    for(b=11;b>0;b--)
        for(a=2;a>0;a--);
}
uchar DS18B20Init()
{
	uint i;
	DSP = 0;
	delay640us();
	DSP = 1;
	delay80us();
	while(DSP)
	{
		Delay1ms(1);
		i++;
		if(i > 5)
			return 0;
	}
	return 1;
} 
void DS18B20WriteByte(uchar dat)
{
	uchar i,j;
	for(i=0; i<8; i++)
	{
		DSP = 0;
		j++;
		DSP =dat&0x01;
		j=6;	   // ��ʱ68΢��
		while(j--);
		DSP = 1;
		dat>>=1;
	}	
}

uchar DS18B20ReadByte()
{
	uchar i,j;
	uchar ret;
	uchar tmp;
	for(i=0; i<8; i++)
	{
		DSP = 0;
		j++ ;// һ������ָ���4΢��
		DSP = 1;
		j++;
		j++; // ��ʱ��Լ10΢��
		tmp = DSP;
		ret = (ret>>1) |(tmp <<7);		
		j = 4;
		while(j--);
	}
	return ret;
}

void DS18B20StarCheck()
{
	DS18B20Init();
	Delay1ms(1);
	DS18B20WriteByte(0xcc);	// ѡ����������
	DS18B20WriteByte(0x44); // ���������ݽ����¶��滻�����Ҵ浽�ڲ�RAM��
	//Delay1ms(800);
}

void DS18B20TemStartRead()
{
	DS18B20Init();
	Delay1ms(1);
	DS18B20WriteByte(0xcc);	 //ѡ����������
	DS18B20WriteByte(0xbe);	 //��ʼ��ȡ��RAM���¶�

}

int DS18B20ReadTemp()
{
	int temp = 0;
	uchar tmh,tml;
	DS18B20StarCheck();
	DS18B20TemStartRead();
	tml = DS18B20ReadByte();  //��ȡ��8λ
	tmh = DS18B20ReadByte();  //��ȡ��8λ
	temp = tmh;
	temp<<=8;
	temp|=tml;
	return temp;
}
int DealTemp(int temp)
{
	float tmp;
	if(temp < 0)
	{
		temp -= 1;
		temp = ~temp;
	}
	else
	{
		led = ~led;
	}
	tmp = temp;
	temp = tmp * 0.0625 *100;
	return temp;
}