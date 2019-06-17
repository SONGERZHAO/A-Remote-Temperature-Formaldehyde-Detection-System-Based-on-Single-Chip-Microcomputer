#include "reg52.h"
#include "ESP8266.h"
#include "tem.h"
#include "ZE08.h"
//#include "LCD1602.h"

uchar myID = 1;
uchar num = 0;
uchar ZE08Data[9] = {0};
void delay500ms(void)   //Îó²î 0us
{
    unsigned char a,b,c;
    for(c=23;c>0;c--)
        for(b=152;b>0;b--)
            for(a=70;a>0;a--);
}
void GetAndSendData(int temp)
{
	uchar i;
	uchar n = 5;
	uchar arr[7];
	arr[1] = myID&0xff;
	arr[2] = (myID>>8)&0xff;
	arr[3] = temp&0xff;
	arr[4] = (temp>>8)&0xff;
	if(ZE08Data[0] == 0xff)
	{
		arr[5] = ZE08Data[6];
		arr[6] = ZE08Data[7];
		n = 7;
	}
	for(i=0; i<9;i++)
	{
		ZE08Data[i]=1;
	}
	arr[0] = n +'0';
	InitESP8266();
	SendString("AT+CIPSTART=\"TCP\",\"39.97.98.37\",8080\r\n");
	delay500ms();
	SendString("AT+CIPSEND=7\r\n");
	delay500ms();
	Sendarr(arr,n);	//AT+CIPCLOSE
	SendString("AT+CIPCLOSE\r\n");

} 


void GetZE08Data() interrupt 4
{
	if(RI)
	{
		RI = 0;
		ZE08Data[num]=SBUF;
		switch(num)
		{
			case(0):
				if(ZE08Data[num] == 0xFF)
				{
					num = 1;
				}
				else
				{
					num = 0;
				}
				break;
			case(1):
				if(ZE08Data[num] == 0x86)
				{
					num = 2;
				}
				else
				{
					num = 0;
				}
				break;
			case(2):
				num = 3;
				break;	
			case(3):
				num = 4;
				break;
			case(4):
				if(ZE08Data[num] == 0x00)
				{
					num = 5;
				}
				else
				{
					num = 0;
				}
				break;
			case(5):
				if(ZE08Data[num] == 0x00)
				{
					num = 6;
				}
				else
				{
					num = 0;
				}
				break;
			case(6):
				num = 7;
				break;
			case(7):
				num = 8;
				break;
			case(8):
				if((ZE08Data[num]+ZE08Data[1]+ZE08Data[2]+ZE08Data[3]+ZE08Data[4]+ZE08Data[5]+
				ZE08Data[6]+ZE08Data[7])%256 == 0)
				{
					num = 0;
				}
				else
				{
					num = 0;
				}
		}	
	}
}

int main (void)
{
	int temp1;
	int temp;
	static uint i;
//  InitTimer0();
//	LCD_Init();
	while(1)
	{
		i++;
		temp = DS18B20ReadTemp();
		temp1 = DealTemp(temp);
		//ShowTempAndCH02(temp1);
		if(i%100 ==0)
		{
			GetData();
		}
		if(i == 1050)
		{
			i = 0;
			GetAndSendData(temp);		
		}
	}
}