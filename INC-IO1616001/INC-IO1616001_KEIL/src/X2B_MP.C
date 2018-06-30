#include "IO.h"
#include "UART1.h"	
#include "commands.h"
#include "delay.h"

#include <stdlib.h> 
#include <stdio.h>
#include <string.h>

/****************�������ݱ���**************************/
extern u8  UART1_Buffer[100];   					//������
extern u8  UART1_Count;										//�����±�
extern u8  UART1_Flag;										//����������ɱ�־

u8 BoardTestFlag=0;
u8 IoTestFlag=0;


void main(void)
{ 
	u32 BlinkDelay=0;
	CLK_DIV=0x00;  													//����Ƶ������ 
	P4SW=0xFF;      												//P4����ΪIO
	P4M0=0x10;															//P45 LED�������
	
	P1=0xFF;P2=0xFF;P3=0xFF;P4=0xFF;				//VHUB-VUSB				DUT������VBUS�պ�
							
	OUTPUT16=0;															//HUBGND1-USBGND2	DUT��VGND�պ�
	OUTPUT15=1;															//�������׽�ȥ
	
	OUTPUT1=1;OUTPUT2=0;										//P2���צ�ӱպ�
	OUTPUT3=1;OUTPUT4=0;										//P2�ұ�צ�ӱպ�
	
	OUTPUT5=1;OUTPUT6=0;										//P3���צ�ӱպ�
	OUTPUT7=1;OUTPUT8=0;										//P3�ұ�צ�ӱպ�
	
	EA=0;																		//�����ж�		
	InitUART1();    												//����1��ʼ�� 		115200��22.1184MHZ��	
	EA=1;       		    										//�����ж�

	UART1_SendStr("Fixture Reset OK\n");		//��ʼ�������ʾ
	UART1_SendStr(">>\n");									//��ʽ
	while(1)
	{
		if(UART1_Flag==1)																				//�����ж��н��յ���Ч���ݺ�
		{
			ProcessCommand((char *)UART1_Buffer);									//�������
			UART1_SendStr(">>\n");																//��ʾ��
			UART1_Count=0;																				//�±����㣬���ݽ��մ�UART1_Buffer[0]��ʼ
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



















