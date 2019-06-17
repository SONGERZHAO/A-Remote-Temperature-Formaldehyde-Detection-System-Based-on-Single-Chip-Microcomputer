//#include "LCD1602.h"
//
//void LCD_Delay1ms(uint c)   //误差 0us
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
//	LCD_WriteCom(0x38);//开显示
//	LCD_WriteCom(0x0c);//开显示不显示光标
//	LCD_WriteCom(0x06);//写一个指针加1
//	LCD_WriteCom(0x01);//清屏
//	LCD_WriteCom(0x80);//D7保持为1
//
//}
//void LCD_WriteData(uchar dat)
//{
//	LCD_E = 0; 
//	LCD_RS = 1;//选择发送数据
//	LCD_RW = 0; //选择写入
//
//	P0 = dat;
//	LCD_Delay1ms(1);
//
//	LCD_E = 1;  //描写时序
//	LCD_Delay1ms(5);
//	LCD_E = 0;
//}
//void LCD_WriteCom(uchar com)
//{
//	LCD_E = 0; 
//	LCD_RS = 0;//选择发送命令
//	LCD_RW = 0; //选择写入
//
//	P0 = com;
//	LCD_Delay1ms(1);
//
//	LCD_E = 1;  //描写时序
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
