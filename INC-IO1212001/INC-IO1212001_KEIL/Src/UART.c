/**
  \file 		UART.c
  \author 	Xcping2016
  \version 	1.00

  \brief 		

  This file contains the major function which does all necessary for UART1.
*/
#include "main.h"
#include "UART.h"
#include "stdarg.h"
#include "stdio.h"	

u8 	USART_RX_BUF[USART_REC_LEN];  
u16 USART_RX_STA=0;    

bit busy;

/************************************************************
				   uart初始化 
*************************************************************/
void InitUART(void)		
{
	PCON &= 0x7F;		//波特率不倍速
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x04;		//独立波特率发生器时钟为Fosc,即1T
	
	IPH=0x10;				//串口中断较高优先级
	
	#if (HSE_USED==HSE_11MHZ)				//@11.0592MHz
	{
		#if (BR_USED==BR_9600)
			BRT = 0xDC;									//设定独立波特率发生器重装值
		#elif (BR_USED==BR_115200)
			BRT = 0xFD;
		#elif (BR_USED==BR_57600)
			BRT = 0xFA;
		#endif
	}
	#elif (HSE_USED==HSE_12MHZ)				//
	{
		#if (BR_USED==BR_9600)
			BRT = 0xD9;									//设定独立波特率发生器重装值
		#elif (BR_USED==BR_115200)
			BRT = 0xFD;
		#elif (BR_USED==BR_57600)
			BRT = 0xF9;
		#endif
	}
	#elif (HSE_USED==HSE_22MHZ)				
	{
		#if (BR_USED==BR_9600)
			BRT = 0xB8;									//设定独立波特率发生器重装值
		#elif (BR_USED==BR_115200)
			BRT = 0xFA;
		#elif (BR_USED==BR_57600)
			BRT = 0xF4;
		#endif
	}
	#endif


	AUXR |= 0x01;		//串口1选择独立波特率发生器为波特率发生器
	AUXR |= 0x10;		//启动独立波特率发生器
	
	REN  = 1;				//使能接收中断
	ES=1;						//使能串口中断	
}
/************************************************************
				   向串口1发送一个字符
*************************************************************/
void UART_SendChar(unsigned char ch)  
{
//	ES=0;						//串口中断使能
//	TI=0;						//清除发送中断
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
//	ES=1;
}
/************************************************************
	向串口uart发送一个字符串，strlen为该字符串长度
*************************************************************/
void UART_SendStr(unsigned char *str)
{
	while(*str!=('\0')) 			//Check the end of the string
	{
		UART_SendChar(*str++);	//Send current char and increment string ptr
	}
}

void UART_Printf(const char *fmt,...)
{   
	va_list ap;	   //This is support the format output 
	char xdata string[100];
	va_start(ap,fmt);
	vsprintf(string,fmt,ap); // Store the string in the String buffer
	UART_SendStr(string);
	va_end(ap);	 
}

void USART1_IRQHandler() interrupt 4  
{
	u8 Res=0;	
	if(RI==1)  
	{
		RI=0;
		Res=SBUF;		
		if((USART_RX_STA&0x8000)==0)												//接收未完成
		{
			if(USART_RX_STA&0x4000)															//接收到了0x0d
			{
				if(Res!=0x0a)	USART_RX_STA=0;											//接收错误,重新开始
				else 					USART_RX_STA|=0x8000;												//接收完成了 
			}
			else 																								//还没收到0X0D
			{	
				if(Res==0x0d)	USART_RX_STA|=0x4000;
				else
				{
					USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
					USART_RX_STA++;
					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//接收数据错误,重新开始接收	  
				}		 
			}
		}	
	}
	if (TI)
	{
		TI = 0;             //Clear transmit interrupt flag
		busy = 0;           //Clear transmit busy flag
	}
}
//
void PrintNA(void)
{
	UART_SendStr("<NA>\n");
}
//

