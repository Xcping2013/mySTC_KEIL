/********************************************************************
本程序只供学习使用，未经作者许可，不得用于其它任何用途
程序结构参考 安徽师范大学  Lyzhangxiang的EasyHW OS结构设计
uart1.h
作者：bg8wj
建立日期: 2010.10.23
版本：V1.0

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