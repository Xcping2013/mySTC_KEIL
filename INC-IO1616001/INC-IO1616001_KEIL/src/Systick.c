#include "STC12C5A60S2.h"
#include "IO.h"

u32 time_ms=5000;

void SysTickStart(void)		//1毫秒@11.0592MHz
{
	AUXR |= 0x80;						//定时器0时钟1T模式
	TMOD &= 0xF0;						//设置定时器模式   13位定时器0  定时器1无效
	TMOD |= 0x01;						//设置定时器模式   16位定时器0
	TL0 = 0xCD;							//设置定时初值
	TH0 = 0xD4;							//设置定时初值
	TF0 = 0;								//清除TF0标志       溢出标识
	TR0 = 1;								//定时器0开始计时   运行控制位
	ET0=1;									//定时器中断使能    溢出中断允许
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