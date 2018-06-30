#include "STC12C5A60S2.h"

#include <string.h>
#include <stdarg.h>
#include <stdio.h>	

u8  UART1_Buffer[100];   
u8  UART1_Count = 0;
u8  UART1_Flag=0;

bit busy;
/************************************************************
				   uart1初始化
*************************************************************/
void InitUART1(void)		
{
	PCON &= 0x7F;		//波特率不倍速
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x04;	
	
	BRT = 0xFD;
/****************@11.0592MHz*******************************/
//	BRT = 0xDC;		//9600
//	BRT = 0xFA;			//57600
//	BRT = 0xFD;			//115200
/****************@22.1184MHz*******************************/	
//	BRT = 0xF4;			//57600
//	BRT = 0xFA;			//115200
	
	AUXR |= 0x01;		//独立波特率发生器
	AUXR |= 0x10;		
  
	REN  = 1;
	ES=1;						//使能串口中断	
}

/************************************************************
				   向串口1发送一个字符
*************************************************************/
void UART1_SendChar(unsigned char ch)  
{
	if(ch=='\n')
	{
		while(busy);		//Wait for the completion of the previous data is sent
		busy = 1;
		SBUF='\r';			//Send data to UART buffer
		while(busy);
		busy = 1;
		SBUF=ch;
	}
	else
	{
		while(busy);	//Wait for the completion of the previous data is sent
		busy = 1;
		SBUF=ch;			//Send data to UART buffer
	}
}
/************************************************************
	向串口uart1发送一个字符串，strlen为该字符串长度
*************************************************************/
void UART1_SendStr(unsigned char *str)
{
	while(*str!=('\0')) UART1_SendChar(*str++);
}

void UART1_Printf(const char *fmt,...)
{   
	va_list ap;	   //This is support the format output 
	char xdata string[100];
	va_start(ap,fmt);
	vsprintf(string,fmt,ap); // Store the string in the String buffer
	UART1_SendStr(string);
	va_end(ap);	 
}
//连续发送命令只会处理第一条命令
void UART1Routine() interrupt 4  
{
	u8 RxValue=0;	

	if(RI==1)  
	{
		RI=0;
		RxValue=SBUF;					//读取接收到的数据
		
		if(RxValue=='\r') 		//回到行首 接收结束标志 
		{
			UART1_Buffer[UART1_Count] ='\0';		
			UART1_Flag=1;
		}
		else if(RxValue=='\n')
		{
//			UART1_Buffer[UART1_Count] ='\0';		
//			UART1_Flag=1;			
		}	
		else
		{
			if( UART1_Count < (sizeof(UART1_Buffer-1))) UART1_Buffer[UART1_Count++]=RxValue;
		}
   } 
	if (TI)
	{
		TI = 0;             //Clear transmit interrupt flag
		busy = 0;           //Clear transmit busy flag
	}
}

