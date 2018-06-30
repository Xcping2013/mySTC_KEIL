/**
  \file 		UART.h
  \author 	Xcping2016
  \version 	1.00

  \brief 	

  This file contains the definitions of the functions from the UART.c
*/
#ifndef _UART_H_ 
#define _UART_H_

#include "main.h"

void InitUART(void);
void UART_SendChar(unsigned char ch);
void UART_SendStr(unsigned char *str);
void UART_Printf(const char *fmt,...);
void PrintNA(void);

#endif