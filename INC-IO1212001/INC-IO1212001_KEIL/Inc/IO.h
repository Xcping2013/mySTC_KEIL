/**
  \file 		IO.h
  \author 	Xcping2016
  \version 	1.00

  \brief 		GPIO Pin Set and Fuction definitions
*/

#ifndef _IO_H_ 
#define _IO_H_

#include "main.h"

#define INPUT1	  P33			
#define INPUT2    P34			
#define INPUT3	  P35			
#define INPUT4	  P36	

#define INPUT5 	  P37

#define INPUT6	  P20			
#define INPUT7 	  P21			
#define INPUT8    P22			
#define INPUT9    P23			
#define INPUT10   P24			
#define INPUT11   P25			
#define INPUT12   P26	

#define SYS_LED   P27

#define OUTPUT1   P05				
#define OUTPUT2   P04				
#define OUTPUT3   P03				
#define OUTPUT4   P02			
#define OUTPUT5   P01				
#define OUTPUT6   P00

#define OUTPUT7   P13				
#define OUTPUT8   P14			
#define OUTPUT9   P15

#define OUTPUT10  P10				
#define OUTPUT11  P11				
#define OUTPUT12  P12		

#define OUT_5V_1  P41
#define OUT_5V_2  P07
#define OUT_5V_3  P06
	
u8 PrintInputStatus(u8 *Commands);
u8 SetOutputStatus(u8 *Commands);

extern u8 BoardTestFlag;
extern u8 IoTestFlag;
void BoardTest(void);
void IoTest(void);

#endif
//
