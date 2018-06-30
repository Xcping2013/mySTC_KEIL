/**
  \file 		Dealy.c
  \author 	Xcping2016
  \version 	1.00

  \brief 		soft delay 
*/
#include "main.h"
#include "Delay.h"
#include "intrins.h"
/**************************************/
static void Delay1us(void);
static void Delay1ms(void);
//------------------------
static void Delay1us(void)
{
	#if (HSE_USED==HSE_11MHZ)				//@11.0592MHz
	{
		_nop_();
	}
	#elif (HSE_USED==HSE_12MHZ)			//@12MHz
	{
		_nop_();
		_nop_();
	}
	#elif (HSE_USED==HSE_22MHZ)			//@22.1148MHz
	{
		unsigned char i;
		_nop_();
		_nop_();
		i = 2;
		while (--i);
	}
	#endif
}
//------------------------
static void Delay1ms(void)
{
	#if (HSE_USED==HSE_11MHZ)				//@11.0592MHz
	{
		unsigned char i, j;
		_nop_();
		i = 11;
		j = 190;
		do
		{
			while (--j);
		} while (--i);
	}
	
	#elif (HSE_USED==HSE_12MHZ)			//@12MHz
	{
		unsigned char i, j;

		_nop_();
		_nop_();
		i = 12;
		j = 168;
		do
		{
			while (--j);
		} while (--i);
	}
	#elif (HSE_USED==HSE_22MHZ)			//@22.1148MHz
	{
		unsigned char i, j;

		i = 22;
		j = 128;
		do
		{
			while (--j);
		} while (--i);
	}
	#endif
}
//------------------------
void delay_us(unsigned char us)
{
	while (us--)
		Delay1us();
}
//------------------------
void delay_ms(unsigned char ms)
{ 
	while(ms--)
		Delay1ms();
}
/**************************************/

