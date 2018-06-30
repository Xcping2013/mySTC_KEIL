/**
  \file 		UART.c
  \author 	Xcping2016
  \version 	1.00

  \brief 		

  This file contains the major function which does all necessary for UART1.
*/
#include "main.h"
#include "UART.h"
#include "stdarg.h"
#include "stdio.h"	

u8 	USART_RX_BUF[USART_REC_LEN];  
u16 USART_RX_STA=0;    

bit busy;

/************************************************************
				   uart��ʼ�� 
*************************************************************/
void InitUART(void)		
{
	PCON &= 0x7F;		//�����ʲ�����
	SCON = 0x50;		//8λ����,�ɱ䲨����
	AUXR |= 0x04;		//���������ʷ�����ʱ��ΪFosc,��1T
	
	IPH=0x10;				//�����жϽϸ����ȼ�
	
	#if (HSE_USED==HSE_11MHZ)				//@11.0592MHz
	{
		#if (BR_USED==BR_9600)
			BRT = 0xDC;									//�趨���������ʷ�������װֵ
		#elif (BR_USED==BR_115200)
			BRT = 0xFD;
		#elif (BR_USED==BR_57600)
			BRT = 0xFA;
		#endif
	}
	#elif (HSE_USED==HSE_12MHZ)				//
	{
		#if (BR_USED==BR_9600)
			BRT = 0xD9;									//�趨���������ʷ�������װֵ
		#elif (BR_USED==BR_115200)
			BRT = 0xFD;
		#elif (BR_USED==BR_57600)
			BRT = 0xF9;
		#endif
	}
	#elif (HSE_USED==HSE_22MHZ)				
	{
		#if (BR_USED==BR_9600)
			BRT = 0xB8;									//�趨���������ʷ�������װֵ
		#elif (BR_USED==BR_115200)
			BRT = 0xFA;
		#elif (BR_USED==BR_57600)
			BRT = 0xF4;
		#endif
	}
	#endif


	AUXR |= 0x01;		//����1ѡ����������ʷ�����Ϊ�����ʷ�����
	AUXR |= 0x10;		//�������������ʷ�����
	
	REN  = 1;				//ʹ�ܽ����ж�
	ES=1;						//ʹ�ܴ����ж�	
}
/************************************************************
				   �򴮿�1����һ���ַ�
*************************************************************/
void UART_SendChar(unsigned char ch)  
{
//	ES=0;						//�����ж�ʹ��
//	TI=0;						//��������ж�
	if(ch=='\n')
	{
		while(busy);		//Wait for the completion of the previous data is sent
		busy = 1;
		SBUF='\r';			//Send data to UART buffer
		while(busy);
		busy = 1;
		SBUF=ch;
	}
	else
	{
		while(busy);	//Wait for the completion of the previous data is sent
		busy = 1;
		SBUF=ch;			//Send data to UART buffer
	}
//	ES=1;
}
/************************************************************
	�򴮿�uart����һ���ַ�����strlenΪ���ַ�������
*************************************************************/
void UART_SendStr(unsigned char *str)
{
	while(*str!=('\0')) 			//Check the end of the string
	{
		UART_SendChar(*str++);	//Send current char and increment string ptr
	}
}

void UART_Printf(const char *fmt,...)
{   
	va_list ap;	   //This is support the format output 
	char xdata string[100];
	va_start(ap,fmt);
	vsprintf(string,fmt,ap); // Store the string in the String buffer
	UART_SendStr(string);
	va_end(ap);	 
}

void USART1_IRQHandler() interrupt 4  
{
	u8 Res=0;	
	if(RI==1)  
	{
		RI=0;
		Res=SBUF;		
		if((USART_RX_STA&0x8000)==0)												//����δ���
		{
			if(USART_RX_STA&0x4000)															//���յ���0x0d
			{
				if(Res!=0x0a)	USART_RX_STA=0;											//���մ���,���¿�ʼ
				else 					USART_RX_STA|=0x8000;												//��������� 
			}
			else 																								//��û�յ�0X0D
			{	
				if(Res==0x0d)	USART_RX_STA|=0x4000;
				else
				{
					USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
					USART_RX_STA++;
					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
				}		 
			}
		}	
	}
	if (TI)
	{
		TI = 0;             //Clear transmit interrupt flag
		busy = 0;           //Clear transmit busy flag
	}
}
//
void PrintNA(void)
{
	UART_SendStr("<NA>\n");
}
//

