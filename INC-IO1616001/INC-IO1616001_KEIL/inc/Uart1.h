/********************************************************************
������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
����ṹ�ο� ����ʦ����ѧ  Lyzhangxiang��EasyHW OS�ṹ���
uart1.h
���ߣ�bg8wj
��������: 2010.10.23
�汾��V1.0

Copyright(C) bg8wj
/********************************************************************/
#ifndef _UART1_H_ 
#define _UART1_H_

#include "STC12C5A60S2.h"

extern void InitUART1();
extern void UART1_SendChar(unsigned char ch);
extern void UART1_SendStr(unsigned char *str);
extern void UART1_Printf(const char *fmt,...);
extern u8 CheckUARTTimeout(void);

#endif