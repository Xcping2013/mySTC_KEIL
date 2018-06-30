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
	AUXR |= 0x80;						//��ʱ��ʱ��1Tģʽ
	TMOD &= 0xF0;						//���ö�ʱ��ģʽ
	TMOD |= 0x01;						//���ö�ʱ��ģʽ
	
	#if (HSE_USED==HSE_11MHZ)			//@11.0592MHz
	{
		TL0 = 0xCD;						//���ö�ʱ��ֵ
		TH0 = 0xD4;						//���ö�ʱ��ֵ
	}
	#elif (HSE_USED==HSE_12MHZ)			//@12MHz
	{
		TL0 = 0x20;						//���ö�ʱ��ֵ
		TH0 = 0xD1;						//���ö�ʱ��ֵ
	}
	#elif (HSE_USED==HSE_22MHZ)			//@22.1148MHz
	{
		TL0 = 0x9A;						//���ö�ʱ��ֵ
		TH0 = 0xA9;						//���ö�ʱ��ֵ
	}
	#endif	
	//TF0 = 0;							//���TF0��־
	TR0 = 1;							//��ʱ��0��ʼ��ʱ	
	ET0=1;								//��ʱ���ж�ʹ��    ����ж�����
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
		TL0 = 0xCD;						//���ö�ʱ��ֵ
		TH0 = 0xD4;						//���ö�ʱ��ֵ
	}
	#elif (HSE_USED==HSE_12MHZ)			//@12MHz
	{
		TL0 = 0x20;						//���ö�ʱ��ֵ
		TH0 = 0xD1;						//���ö�ʱ��ֵ
	}
	#elif (HSE_USED==HSE_22MHZ)			//@22.1148MHz
	{
		TL0 = 0x9A;						//���ö�ʱ��ֵ
		TH0 = 0xA9;						//���ö�ʱ��ֵ
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

