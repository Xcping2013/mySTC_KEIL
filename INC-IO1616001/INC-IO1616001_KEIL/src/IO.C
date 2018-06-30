#include <IO.h>
#include "UART1.h"
#include "Delay.h"
#include "Systick.h"

#include <stdlib.h> 
#include <stdio.h>
#include <string.h>

u8 air_IN(u8 Number )	
{
	switch(Number)
	{
		case 1:	OUTPUT15=1;return 1;break; 					//P1按键气缸
		case 2:	OUTPUT5=0;OUTPUT6=1;return 1;break;	//P2爪子
		case 3:	OUTPUT7=0;OUTPUT8=1;return 1;break;	//P3爪子
		default:	return 0;break;
	}
}
////////////////////////////////////////////
u8 air_OUT(u8 Number )	
{
	switch(Number)
	{
		case 1:	OUTPUT15=0;return 1;break;
		case 2:	OUTPUT5=1;OUTPUT6=0;return 1;break;
		case 3:	OUTPUT7=1;OUTPUT8=0;return 1;break;
		default:	return 0;break;
	}
}
/////////////////////////////////减少发热
u8 air_STANDBY(u8 Number )
{
	switch(Number)
	{
		//case 1:	OUTPUT3=1;OUTPUT4=1;return 1;break;
		case 2:	OUTPUT5=1;OUTPUT6=1;return 1;break;
		case 3:	OUTPUT7=1;OUTPUT8=1;return 1;break;
		default:	return 0;break;
	}
}
//////////////////////////////////

















