#include "IO.h"
#include "UART1.h"	
#include "commands.h"
#include "delay.h"

#include <stdlib.h> 
#include <stdio.h>
#include <string.h>

/****************串口数据变量**************************/
extern u8  UART1_Buffer[100];   					//缓冲区
extern u8  UART1_Count;										//接收下标
extern u8  UART1_Flag;										//接收数据完成标志

u8 BoardTestFlag=0;
u8 IoTestFlag=0;


void main(void)
{ 
	u32 BlinkDelay=0;
	CLK_DIV=0x00;  													//工作频率设置 
	P4SW=0xFF;      												//P4口设为IO
	P4M0=0x10;															//P45 LED推挽输出
	
	P1=0xFF;P2=0xFF;P3=0xFF;P4=0xFF;				//VHUB-VUSB				DUT供电线VBUS闭合
							
	OUTPUT16=0;															//HUBGND1-USBGND2	DUT供VGND闭合
	OUTPUT15=1;															//按键气缸进去
	
	OUTPUT1=1;OUTPUT2=0;										//P2左边爪子闭合
	OUTPUT3=1;OUTPUT4=0;										//P2右边爪子闭合
	
	OUTPUT5=1;OUTPUT6=0;										//P3左边爪子闭合
	OUTPUT7=1;OUTPUT8=0;										//P3右边爪子闭合
	
	EA=0;																		//关总中断		
	InitUART1();    												//串口1初始化 		115200（22.1184MHZ）	
	EA=1;       		    										//开总中断

	UART1_SendStr("Fixture Reset OK\n");		//初始化完成提示
	UART1_SendStr(">>\n");									//格式
	while(1)
	{
		if(UART1_Flag==1)																				//串口中断中接收到有效数据后
		{
			ProcessCommand((char *)UART1_Buffer);									//命令解析
			UART1_SendStr(">>\n");																//提示符
			UART1_Count=0;																				//下标清零，数据接收从UART1_Buffer[0]开始
			UART1_Flag=0;																	
		}
		if(BoardTestFlag) BoardTest();
		if(IoTestFlag)		IoTest();
		
		if(BlinkDelay++>25000) 
		{
			BlinkDelay=0;SYS_LED=!SYS_LED;		
		}

	}
}

void IoTest(void)
{
//	if(INPUT1==0)		OUTPUT1=0; else OUTPUT1=1;
//	if(INPUT2==0)		OUTPUT2=0; else OUTPUT2=1;
//	if(INPUT3==0)		OUTPUT3=0; else OUTPUT3=1;
//	if(INPUT4==0)		OUTPUT4=0; else OUTPUT4=1;
//	if(INPUT5==0)		OUTPUT5=0; else OUTPUT5=1;
//	if(INPUT6==0)		OUTPUT6=0; else OUTPUT6=1;
//	if(INPUT7==0)		OUTPUT7=0; else OUTPUT7=1;
//	if(INPUT8==0)		OUTPUT8=0; else OUTPUT8=1;
//	if(INPUT9==0)		OUTPUT9=0; else OUTPUT9=1;
//	if(INPUT10==0)	OUTPUT10=0; else OUTPUT10=1;
//	if(INPUT11==0)	OUTPUT11=0; else OUTPUT11=1;
//	if(INPUT12==0)	OUTPUT12=0; else OUTPUT12=1;
//	if(INPUT13==0)	OUTPUT13=0; else OUTPUT13=1;
//	if(INPUT14==0)	OUTPUT14=0; else OUTPUT14=1;
//	if(INPUT15==0)	OUTPUT15=0; else OUTPUT15=1;
//	if(INPUT16==0)	OUTPUT16=0; else OUTPUT16=1;	
	
	INPUT1=1;INPUT3=1;INPUT5=1;INPUT7=1;INPUT9=1;INPUT11=1;INPUT13=1;INPUT15=1;
	INPUT2=0;INPUT4=0;INPUT6=0;INPUT8=0;INPUT10=0;INPUT12=0;INPUT14=0;INPUT16=0;
	OUTPUT1=1;OUTPUT3=1;OUTPUT5=1;OUTPUT7=1;OUTPUT9=1;OUTPUT11=1;OUTPUT13=1;OUTPUT15=1;
	OUTPUT2=0;OUTPUT4=0;OUTPUT6=0;OUTPUT8=0;OUTPUT10=0;OUTPUT12=0;OUTPUT14=0;OUTPUT16=0;
	delay_ms(500);
	INPUT1=0;INPUT3=0;INPUT5=0;INPUT7=0;INPUT9=0;INPUT11=0;INPUT13=0;INPUT15=0;
	INPUT2=1;INPUT4=1;INPUT6=1;INPUT8=1;INPUT10=1;INPUT12=1;INPUT14=1;INPUT16=1;
	OUTPUT1=0;OUTPUT3=0;OUTPUT5=0;OUTPUT7=0;OUTPUT9=0;OUTPUT11=0;OUTPUT13=0;OUTPUT15=0;
	OUTPUT2=1;OUTPUT4=1;OUTPUT6=1;OUTPUT8=1;OUTPUT10=1;OUTPUT12=1;OUTPUT14=1;OUTPUT16=1;
	delay_ms(500);
}

void BoardTest(void)
{
	INPUT1=0;OUTPUT1=0;delay_ms(500);INPUT1=1;OUTPUT1=1;
	INPUT2=0;OUTPUT2=0;delay_ms(500);INPUT2=1;OUTPUT2=1;
	INPUT3=0;OUTPUT3=0;delay_ms(500);INPUT3=1;OUTPUT3=1;
	INPUT4=0;OUTPUT4=0;delay_ms(500);INPUT4=1;OUTPUT4=1;
	INPUT5=0;OUTPUT5=0;delay_ms(500);INPUT5=1;OUTPUT5=1;
	INPUT6=0;OUTPUT6=0;delay_ms(500);INPUT6=1;OUTPUT6=1;
	INPUT7=0;OUTPUT7=0;delay_ms(500);INPUT7=1;OUTPUT7=1;
	INPUT8=0;OUTPUT8=0;delay_ms(500);INPUT8=1;OUTPUT8=1;
	INPUT9=0;OUTPUT9=0;delay_ms(500);INPUT9=1;OUTPUT9=1;
	INPUT10=0;OUTPUT10=0;delay_ms(500);INPUT10=1;OUTPUT10=1;
	INPUT11=0;OUTPUT11=0;delay_ms(500);INPUT11=1;OUTPUT11=1;
	INPUT12=0;OUTPUT12=0;delay_ms(500);INPUT12=1;OUTPUT12=1;
	INPUT13=0;OUTPUT13=0;delay_ms(500);INPUT13=1;OUTPUT13=1;
	INPUT14=0;OUTPUT14=0;delay_ms(500);INPUT14=1;OUTPUT14=1;
	INPUT15=0;OUTPUT15=0;delay_ms(500);INPUT15=1;OUTPUT15=1;
	INPUT16=0;OUTPUT16=0;delay_ms(500);INPUT16=1;OUTPUT16=1;
}




















