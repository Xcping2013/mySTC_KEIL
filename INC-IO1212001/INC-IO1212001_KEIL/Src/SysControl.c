/**
  \file 		SysControl.c
  \author 	Xcping2016
  \version 	1.00

  \brief 		

  This file contains the major function which does all necessary for project.
*/
#include "main.h"
#include "IO.h"
#include "UART.h"
#include "Delay.h"
#include "Timer.h"
#include "Commands.h"
#include "SysControl.h"
#include <stdlib.h> 

void SetUpMcu(void)
{
	CLK_DIV=0x00; 												
	//P4SW=0xFF;      											//P4口设为IO
	P1=0xFF;P2=0xFF;P3=0xFF;P4=0xFF;	
	P2M0=0x80; 															//P27强挽输出	
	
	EA=0;																		//关总中断	
	InitUART();    													//串口1初始化 	
	Timer0Init(); 													//定时器中断默认低优先级
	delay_ms(100);
	EA=1;          												  //开总中断
}
//
void CylinderCoolDown(void)
{
}
//
void CommandCheckAndExe(void)
{
	u8 len;
	if(USART_RX_STA&0x8000)											
	{
		len=USART_RX_STA&0x3fff;							
		USART_RX_BUF[len]='\0';								
		UART_SendStr((char*)USART_RX_BUF);
		UART_SendChar('\n');
		if(USART_RX_BUF[0]=='\0')											{	;}//UART_SendStr("\n");}
		else if(ProcessCommand((char*)USART_RX_BUF))	{										;}
		else																					{	UART_SendStr("<NA>\n");}
									
		UART_SendStr(">>");	
		USART_RX_STA=0;
	}	
}
//                    
void HandleTaskPerMS(u16 ms)
{
	 static u16 BlinkDelay;
	
		if(abs(GetTickTimer0()-BlinkDelay)>ms)
  	{
  		SYS_LED=!SYS_LED;
  		BlinkDelay=GetTickTimer0();
  	}	
}
//
void HandleDebugTaskPerMS(void)
{
	 static u16 BlinkDelay1;
	
		if(abs(GetTickTimer0()-BlinkDelay1)>1000)
  	{
			INPUT1=1;INPUT3=1;INPUT5=1;INPUT7=1;INPUT9=1;INPUT11=1;
			INPUT2=0;INPUT4=0;INPUT6=0;INPUT8=0;INPUT10=0;INPUT12=0;
			OUTPUT1=1;OUTPUT3=1;OUTPUT5=1;OUTPUT7=1;OUTPUT9=1;OUTPUT11=1;
			OUTPUT2=0;OUTPUT4=0;OUTPUT6=0;OUTPUT8=0;OUTPUT10=0;OUTPUT12=0;
			
			BlinkDelay1=GetTickTimer0();
  	}	
		else if(abs(GetTickTimer0()-BlinkDelay1)>500)
  	{
			INPUT1=0;INPUT3=0;INPUT5=0;INPUT7=0;INPUT9=0;INPUT11=0;
			INPUT2=1;INPUT4=1;INPUT6=1;INPUT8=1;INPUT10=1;INPUT12=1;
			OUTPUT1=0;OUTPUT3=0;OUTPUT5=0;OUTPUT7=0;OUTPUT9=0;OUTPUT11=0;
			OUTPUT2=1;OUTPUT4=1;OUTPUT6=1;OUTPUT8=1;OUTPUT10=1;OUTPUT12=1;	
  	}	
}
//
void ResetMpuIntoISP(void)
{
	IAP_CONTR=0x60;
}
//
//板子软复位
void ResetMcuToMain(void)
{
  IAP_CONTR=0x20;
}
//





