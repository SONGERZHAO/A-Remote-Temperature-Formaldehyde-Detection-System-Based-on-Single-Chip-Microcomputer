//#include "LCD1602.h"
//
//void LCD_Delay1ms(uint c)   //��� 0us
//{
//    uchar a,b;
//	for (; c>0; c--)
//	{
//		 for (b=199;b>0;b--)
//		 {
//		  	for(a=1;a>0;a--);
//		 }      
//	}
//}
//
//
//void LCD_Init()
//{
//	LCD_WriteCom(0x38);//����ʾ
//	LCD_WriteCom(0x0c);//����ʾ����ʾ���
//	LCD_WriteCom(0x06);//дһ��ָ���1
//	LCD_WriteCom(0x01);//����
//	LCD_WriteCom(0x80);//D7����Ϊ1
//
//}
//void LCD_WriteData(uchar dat)
//{
//	LCD_E = 0; 
//	LCD_RS = 1;//ѡ��������
//	LCD_RW = 0; //ѡ��д��
//
//	P0 = dat;
//	LCD_Delay1ms(1);
//
//	LCD_E = 1;  //��дʱ��
//	LCD_Delay1ms(5);
//	LCD_E = 0;
//}
//void LCD_WriteCom(uchar com)
//{
//	LCD_E = 0; 
//	LCD_RS = 0;//ѡ��������
//	LCD_RW = 0; //ѡ��д��
//
//	P0 = com;
//	LCD_Delay1ms(1);
//
//	LCD_E = 1;  //��дʱ��
//	LCD_Delay1ms(5);
//	LCD_E = 0;
//}
//
//void LCD_WriteString(uchar * p)
//{
//	while(*p)
//	{
//		 LCD_WriteData(*p);
//		 p++;
//	}
//
//}
//
//
