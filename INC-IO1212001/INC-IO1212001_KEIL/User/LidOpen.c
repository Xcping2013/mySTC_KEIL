/**
  \file 		LidOpen.c
  \author 	Xcping2016	2016-4-23
  \version 	1.00

  \brief 		

  This file contains the major function which does all necessary for project.
*/

#include "main.h"

#if	(PROJECT==LIDOPEN)

#include "LidOpen.h"
#include "IO.h"
#include "UART.h"
#include "Delay.h"
#include "SysControl.h"
#include 	<string.h>

#define PB_START		INPUT1
#define PRESS				0

#define STANDBY 				0
#define DUT_GO_INSIDE 	1
#define CLOSE_DOOR 			2
#define OPEN_DOOR 			3
#define DUT_GO_OUTSIDE 	4

#define	INSIDE			0
#define	OUTSIDE			1
#define	UNDEFINE		3
#define	UPSIDE			0
#define DOWNSIDE		1

#define DutGoInside()		OUTPUT8=1;OUTPUT9=0
#define DutGoOutside()	OUTPUT8=0;OUTPUT9=1
#define CloseTheDoor()	OUTPUT6=1;OUTPUT7=0
#define OpenTheDoor()		OUTPUT6=0;OUTPUT7=1

uchar	OpStep=STANDBY;
uchar	Test_Enable=0;
uchar START_Enable;

uchar DutPosition(void);
uchar DoorPosition(void);

void SetCylinderPowerOn(void)
{

}
u8 LidOpen_Commands(u8 *ptr)
{
	if(strcmp("button enable",ptr)==0)
	{
		START_Enable=1;Test_Enable=0;OUTPUT12=1;
		UART_SendStr("OK\n*_*\n");
		return 1;
	}
	else if(strcmp("button disable",ptr)==0)
	{
		START_Enable=0;Test_Enable=0;OUTPUT12=1;
		UART_SendStr("OK\n*_*\n");
		return 1;
	}
	else if(strcmp("is button ok",ptr)==0)
	{
		if(Test_Enable==1)
		{	
			UART_SendStr("OK\n*_*\n");
			return 1;
		}
		else 
		{	
			UART_SendStr("is not ready\n*_*\n");	
			return 1;
		}
	}
  else return 0; 
}
//
void ButtonProcess_START(void)												
{
	switch(OpStep)						
	{	
		case STANDBY:
			if(DutPosition()==OUTSIDE && DoorPosition()==UPSIDE )					
			{
				if(PB_START==PRESS) 																								
				{	
					delay_ms(20);
					if(PB_START==PRESS)	OpStep=DUT_GO_INSIDE;					
				}
				//else	OpStep=DUT_GO_OUTSIDE;//防止进出气缸一直处于弹出状态而不受控制
			}	
			break;
			
		case DUT_GO_INSIDE:	
			if(PB_START==PRESS)	
			{	
				 OUTPUT12=0;DutGoInside();delay_ms(100);
				 if(DutPosition()==INSIDE )	OpStep=CLOSE_DOOR;
				// else DutGoInside();	
			}
			else	OpStep=DUT_GO_OUTSIDE;
			break;	
			
		case CLOSE_DOOR:
			if(PB_START==PRESS)	
			{	
				 OUTPUT12=0;CloseTheDoor();delay_ms(100);
				 if(DoorPosition()==DOWNSIDE )	
				 {
					 START_Enable=0;Test_Enable=1;UART_SendStr("ready to test\n");OpStep=STANDBY;
				 }
				 //else CloseTheDoor();
			}
			else	OpStep=OPEN_DOOR;
			break;
			
		case OPEN_DOOR:
			if(PB_START!=PRESS)	
			{
				OUTPUT12=1;OpenTheDoor();delay_ms(100);
				if(DoorPosition()==UPSIDE) OpStep=DUT_GO_OUTSIDE;
				//else OpenTheDoor();	
			}
			else OpStep=CLOSE_DOOR;
			break;
			
		case DUT_GO_OUTSIDE:		
			if(PB_START!=PRESS)	
			{	
				 OUTPUT12=1;DutGoOutside();delay_ms(100);
				 if(DutPosition()==OUTSIDE) OpStep=STANDBY;
				 else DutGoOutside();
			}
			else	OpStep=DUT_GO_INSIDE;
			break;
			
		default:
			break;	
//UART_SendStr("please check door sensor\n*_*\n");		
	}
}

uchar DutPosition(void)
{
	if		 (INPUT3==0 && INPUT4==1) return INSIDE;
	else if(INPUT3==1 && INPUT4==0) return OUTSIDE;	
	else {return UNDEFINE;}
}

uchar DoorPosition(void)
{
	if		 (INPUT6==0 && INPUT7==1) return UPSIDE;
	else if(INPUT6==1 && INPUT7==0) return DOWNSIDE;
	else {return UNDEFINE;}	
}


#endif


