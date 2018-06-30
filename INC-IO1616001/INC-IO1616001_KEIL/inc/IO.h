#ifndef _IO_H_ 
#define _IO_H_

#include "STC12C5A60S2.h"

#define SYS_LED	  P45			

#define INPUT1	  P06			//LOAD
#define INPUT2    P04			//UNLOAD
#define INPUT3	  P02			//P0光栅1
#define INPUT4	  P00			//P0光栅2
#define INPUT5 	  P10			//P4光栅3
#define INPUT6	  P12			//P4光栅4
#define INPUT7 	  P14			//按键气缸sensor1
#define INPUT8    P16			//按键气缸sensor2

#define INPUT9    P05			//P2左爪子sensor
#define INPUT10   P03			//P2右爪子sensor
#define INPUT11   P01			//P3左爪子sensor
#define INPUT12   P42			//P3右爪子sensor
#define INPUT13   P11			//p2上下气缸sensor1
#define INPUT14   P13			//p2上下气缸sensor2
#define INPUT15   P15			//p3上下气缸sensor1
#define INPUT16   P17			//p3上下气缸sensor2

#define OUTPUT1   P22				//P2 左爪relay1
#define OUTPUT2   P24				//P2 左爪relay2
#define OUTPUT3   P21				//P2 右爪relay1
#define OUTPUT4   P26				//P2 右爪relay2		
#define OUTPUT5   P43				//P3 左爪relay1
#define OUTPUT6   P35				//P3 左爪relay2
#define OUTPUT7   P37				//P3 右爪relay1
#define OUTPUT8   P33				//P3 右爪relay2
#define OUTPUT9   P23				//R EA     A        0
#define OUTPUT10	P20				//R EB		 B				0
#define OUTPUT11  P25				//I EA     C				0
#define OUTPUT12  P27				//I EB		 D				0
#define OUTPUT13 	P40				//I DUT    E				0 电流表
#define OUTPUT14  P36				//POWER    F        1 电源线ON			E75-USB VBUS
#define OUTPUT15  P32				//按键气缸relay
#define OUTPUT16  P34				//GND-GND  G 				0 地线ON				E75两个USB地线

#define ON 	 1
#define OFF  0

#define IN  0
#define OUT 1

#endif

extern u8 BoardTestFlag;
extern u8 IoTestFlag;
void BoardTest(void);
void IoTest(void);