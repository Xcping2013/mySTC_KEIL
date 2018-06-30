/**
  \file 		Timer.c
  \author 	Xcping2016
  \version 	1.00

  \brief 	

  This file contains the functions to setup Timer0
*/
#include "main.h"

static volatile u16 TickTimer;

void Timer0Init(void)					//1ms
{
	AUXR |= 0x80;						//定时器时钟1T模式
	TMOD &= 0xF0;						//设置定时器模式
	TMOD |= 0x01;						//设置定时器模式
	
	#if (HSE_USED==HSE_11MHZ)			//@11.0592MHz
	{
		TL0 = 0xCD;						//设置定时初值
		TH0 = 0xD4;						//设置定时初值
	}
	#elif (HSE_USED==HSE_12MHZ)			//@12MHz
	{
		TL0 = 0x20;						//设置定时初值
		TH0 = 0xD1;						//设置定时初值
	}
	#elif (HSE_USED==HSE_22MHZ)			//@22.1148MHz
	{
		TL0 = 0x9A;						//设置定时初值
		TH0 = 0xA9;						//设置定时初值
	}
	#endif	
	//TF0 = 0;							//清除TF0标志
	TR0 = 1;							//定时器0开始计时	
	ET0=1;								//定时器中断使能    溢出中断允许
}

//
void Timer0Routine(void) interrupt 1 
{	
//  TF0=0;
//  TR0=0; 
//	if(time_ms<=600000) time_ms++;
//  InputScan(); 
	
	//reload timer0 
	#if (HSE_USED==HSE_11MHZ)			//@11.0592MHz
	{
		TL0 = 0xCD;						//设置定时初值
		TH0 = 0xD4;						//设置定时初值
	}
	#elif (HSE_USED==HSE_12MHZ)			//@12MHz
	{
		TL0 = 0x20;						//设置定时初值
		TH0 = 0xD1;						//设置定时初值
	}
	#elif (HSE_USED==HSE_22MHZ)			//@22.1148MHz
	{
		TL0 = 0x9A;						//设置定时初值
		TH0 = 0xA9;						//设置定时初值
	}
	#endif	
	
//	TR0=1;	
	TickTimer++;
}
unsigned short GetTickTimer0(void)
{
  return TickTimer;
}
//

