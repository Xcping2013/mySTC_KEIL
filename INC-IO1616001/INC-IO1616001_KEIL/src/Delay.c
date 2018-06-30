#include "intrins.h"

static void Delay1us(void);
static void Delay1ms(void);


//------------------------
void delay_us(unsigned char us)
{
	while (us--)
		Delay1us();
}
//------------------------
void delay_ms(unsigned int ms)
{ 
	while(ms--)
		Delay1ms();
}
//

/**************************************/
static void Delay1us(void)		//@11.0592MHz
{
	_nop_();
}
/**************************************/
static void Delay1ms(void)		//@11.0592MHz
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
