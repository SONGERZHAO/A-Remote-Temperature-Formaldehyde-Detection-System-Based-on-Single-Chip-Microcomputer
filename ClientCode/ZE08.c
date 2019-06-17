#include "ZE08.h"
void delay500msZE08(void)   //��� 0us
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
 	TMOD |=0x20;//��ʱ��1����  ��λ���ƶ�ʱ��1 ����λ���ƶ�ʱ��0
	TH1 = 0xfa;//������9600
	TL1 = 0xfa;
	PCON = 0x80;//���ò����ʵ�һ������		   	
	SCON = 0x50;
	EA=1;
	ES=1;
	TR1 = 1;   //��ʱ��1��ʼ����
}
void SendByteZE08(uchar dat)
{
	ES = 0;//�رմ����ж�
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
void GetData()//����Ӧ��ָ��
{
	uchar arr[9] = {0xff,0x01,0x86,0x00,0x00,0x00,0x00,0x00,0x79};
	InitZE08();
	SendarrZE08(arr,9);
	delay500msZE08();
}