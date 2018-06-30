#ifndef __MAIN_H
#define __MAIN_H

#include "STC12C5A60S2.h"

#define	HSE_11MHZ				11059200
#define	HSE_12MHZ				12000000
#define	HSE_22MHZ				22118400

#define	BR_9600					9600
#define	BR_57600				57600
#define	BR_115200				115200

#define	HSE_USED				HSE_11MHZ			
#define	BR_USED					BR_115200

#define TRUE 						1
#define FALSE 					0	

#define ROM_LENGTH			100						//ROM[1]~ROM[100]   芯片内部EEPROM仿真

#define USART_REC_LEN  	80 

typedef unsigned char		u8;
typedef unsigned short 	u16;         
typedef unsigned  int 	u32;
typedef unsigned char 	uchar;
typedef unsigned int  	uint;

/****************串口数据变量**************************/
extern u8  USART_RX_BUF[USART_REC_LEN]; 
extern u16 USART_RX_STA;
/****************调试专用**************************/
extern u8 BoardTestFlag;

#endif

