/**
	\file 			IO.c
  \author 		Xcping2016
  \version 		1.00

  \brief 			I/O functions

  This file provides functions for using the I/O ports and some other miscellaneous stuff.
*/
#include <IO.h>
#include "UART.h"
#include "delay.h"
#include <stdlib.h> 
#include <stdio.h>
#include <string.h>

u8 timecount=0;

static u8 GetInput(u8 ch);
static void PrintNA(void);

static u8 GetInput(u8 ch)
{	
	if		 (ch==1) 	return INPUT1 ? 0:1;
	else if(ch==2) 	return INPUT2 ? 0:1;
	else if(ch==3) 	return INPUT3 ? 0:1;
	else if(ch==4) 	return INPUT4 ? 0:1;
	else if(ch==5) 	return INPUT5 ? 0:1;
	else if(ch==6) 	return INPUT6 ? 0:1;
	else if(ch==7) 	return INPUT7 ? 0:1;
	else if(ch==8) 	return INPUT8 ? 0:1;
	else if(ch==9) 	return INPUT9 ? 0:1;
	else if(ch==10) return INPUT10 ? 0:1;
	else if(ch==11) return INPUT11 ? 0:1;
	else 						return INPUT12 ? 0:1;
}
//////////////////////////////////
u8 PrintInputStatus(u8 *Commands)
{
	if( strncmp(Commands,"int[",4)==0  ) 
	{	
		char *p = NULL;
		char *s = &Commands[4];	
		u8 channel=0;		
		channel=(u8)strtol(s, &p, 10);	
		if(*p==']'&& *(p+1)=='\0'	&& channel>0 && channel<=12)
		{	
			UART_Printf("INT[%d]<%d>\n",(u16)channel,(u16)GetInput(channel));
			return 1;
		}
		PrintNA();
		return 1;
	}	
	else return 0;	
}
/**		   
**
**/
u8 SetOutputStatus(u8 *Commands)
{
	if( strncmp(Commands,"out[",4)==0  ) 
	{	
		char *p = NULL;
		char *s = &Commands[4];		
		bit Val;		
		u8 channel=(u8)strtol(s, &p, 10);	
		if(*p==']'&& *(p+1)=='[' && channel>0 && channel<=12)	
		{
			Val=*(p+2)-'0';	
			if(*(p+3)==']'&& *(p+4)=='\0' )
			{
				switch(channel)
				{
					 case 1:  OUTPUT1  = ~Val; break;
					 case 2:  OUTPUT2  = ~Val; break;
					 case 3:  OUTPUT3  = ~Val; break;
					 case 4:  OUTPUT4  = ~Val; break;
					 case 5:  OUTPUT5  = ~Val; break;
					 case 6:  OUTPUT6  = ~Val; break;
					 case 7:  OUTPUT7  = ~Val; break;	 
					 case 8:  OUTPUT8  = ~Val; break;
					 
					 case 9:  OUTPUT9  = ~Val; break;
					 case 10: OUTPUT10 = ~Val; break;
					 case 11: OUTPUT11 = ~Val; break;
					 case 12: OUTPUT12 = ~Val; break;
				 
					 default: break;
				}
				UART_Printf("OUT[%d][%d]<OK>\n",(u16)channel,(u16)Val); return 1;
			}
		}	 
		PrintNA();
		return 1;
	}	
	else return 0;
}
//
static void PrintNA(void)
{
	UART_SendStr("<NA>\n");
}


void BoardTest(void)
{
	INPUT1=0;OUTPUT1=0;delay_ms(50);INPUT1=1;OUTPUT1=1;
	INPUT2=0;OUTPUT2=0;delay_ms(50);INPUT2=1;OUTPUT2=1;
	INPUT3=0;OUTPUT3=0;delay_ms(50);INPUT3=1;OUTPUT3=1;
	INPUT4=0;OUTPUT4=0;delay_ms(50);INPUT4=1;OUTPUT4=1;
	INPUT5=0;OUTPUT5=0;delay_ms(50);INPUT5=1;OUTPUT5=1;
	INPUT6=0;OUTPUT6=0;delay_ms(50);INPUT6=1;OUTPUT6=1;
	INPUT7=0;OUTPUT7=0;delay_ms(50);INPUT7=1;OUTPUT7=1;
	INPUT8=0;OUTPUT8=0;delay_ms(50);INPUT8=1;OUTPUT8=1;
	INPUT9=0;OUTPUT9=0;delay_ms(50);INPUT9=1;OUTPUT9=1;
	INPUT10=0;OUTPUT10=0;delay_ms(50);INPUT10=1;OUTPUT10=1;
	INPUT11=0;OUTPUT11=0;delay_ms(50);INPUT11=1;OUTPUT11=1;
	INPUT12=0;OUTPUT12=0;delay_ms(50);INPUT12=1;OUTPUT12=1;
}















