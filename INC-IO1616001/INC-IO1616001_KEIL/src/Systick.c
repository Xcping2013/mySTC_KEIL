#include "STC12C5A60S2.h"
#include "IO.h"

u32 time_ms=5000;

void SysTickStart(void)		//1����@11.0592MHz
{
	AUXR |= 0x80;						//��ʱ��0ʱ��1Tģʽ
	TMOD &= 0xF0;						//���ö�ʱ��ģʽ   13λ��ʱ��0  ��ʱ��1��Ч
	TMOD |= 0x01;						//���ö�ʱ��ģʽ   16λ��ʱ��0
	TL0 = 0xCD;							//���ö�ʱ��ֵ
	TH0 = 0xD4;							//���ö�ʱ��ֵ
	TF0 = 0;								//���TF0��־       �����ʶ
	TR0 = 1;								//��ʱ��0��ʼ��ʱ   ���п���λ
	ET0=1;									//��ʱ���ж�ʹ��    ����ж�����
}

void Timer0Routine(void) interrupt 1 
{	
	TF0=0;
  TR0=0; 

	if(time_ms<=600000) time_ms++; 
  TL0 = 0xCD;		
	TH0 = 0xD4;
	TR0=1;
}