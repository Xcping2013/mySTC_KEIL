#include "main.h"

#include "IO.h"
#include "UART.h"
#include "SysControl.h"
#include "EEPROM_OnChip.h"

#include <stdio.h>
#include <string.h>

u8 BoardTestFlag=0;
u8 IoTestFlag=0;

void main(void)
{ 
	SetUpMcu();
	ReadDatasFromEEPROM_OnChip();

	UART_SendStr("Fixture Reset OK\n>>");	
	
	while(1)
	{
		CommandCheckAndExe();
		
		HandleTaskPerMS(350);
		
		if(BoardTestFlag) {	BoardTest();	}
		if(IoTestFlag)		HandleDebugTaskPerMS();//IoTest();
	}
}


/********************************************************************
		//ICTest_AT24C128();
		//CylinderCoolDown();					//空函数，对应项目需要再补充
    //HandleTaskPerMS(1000);		//需要在SetUpMcu中初始化定时器
********************************************************************/
void IoTest(void)
{
	if(INPUT1==0)		OUTPUT1=0; else OUTPUT1=1;
	if(INPUT2==0)		OUTPUT2=0; else OUTPUT2=1;
	if(INPUT3==0)		OUTPUT3=0; else OUTPUT3=1;
	if(INPUT4==0)		OUTPUT4=0; else OUTPUT4=1;
	if(INPUT5==0)		OUTPUT5=0; else OUTPUT5=1;
	if(INPUT6==0)		OUTPUT6=0; else OUTPUT6=1;
	if(INPUT7==0)		OUTPUT7=0; else OUTPUT7=1;
	if(INPUT8==0)		OUTPUT8=0; else OUTPUT8=1;
	if(INPUT9==0)		OUTPUT9=0; else OUTPUT9=1;
	if(INPUT10==0)	OUTPUT10=0; else OUTPUT10=1;
	if(INPUT11==0)	OUTPUT11=0; else OUTPUT11=1;
	if(INPUT12==0)	OUTPUT12=0; else OUTPUT12=1;
	
}


