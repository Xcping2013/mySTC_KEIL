/**
  \file 	EEPROM_OnChip.c
  \author 	Xcping2016
  \version 	1.00

  \brief 		

  This file contains the major function to write ande read datas with EEPROM On Chip
*/
#include "main.h"
#include "intrins.h"
#include "EEPROM_OnChip.h"
#include "UART.h"
#include <string.h>
#include <stdlib.h>

typedef struct
{  
	//基本参数  			NBytes		Meaning
	u8	hw; 				//1   		HardWare
	u8	sw;   				//1  		SoftWare          
	u8 	de;  				//1			DeviceNum
	u8 	fsn[10];			//10 		FixtureNum
	//片上内存存储空间
	union 					
	{
		float f32;     
		u8 Byte[4];   
	}ROM[100];

}DataItem;

#define DATA_LEN		413
//#define DATA_LEN		13
DataItem	DataSave	=	{	200,200,1,
'D',	'I',	'O',	'-',	'0',	'0',	'2',	'-',	'0',	'1',
//1		2			3				4			5		6			7			8			9			10
1,	2,	3,	4,	5,	6,	7,	8,	9,	10,
11,	0,	0,	0,	0,	0,	0,	0,	0,	0,
21,	0,	0,	0,	0,	0,	0,	0,	0,	0,
31,	0,	0,	0,	0,	0,	0,	0,	0,	0,
41,	0,	0,	0,	0,	0,	0,	0,	0,	0,
51,	0,	0,	0,	0,	0,	0,	0,	0,	0,
61,	0,	0,	0,	0,	0,	0,	0,	0,	0,
71,	0,	0,	0,	0,	0,	0,	0,	0,	0,
81,	0,	0,	0,	0,	0,	0,	0,	0,	0,
91,	0,	0,	0,	0,	0,	0,	0,	0,	0,
};
//DataItem	DataSave	=	{	200,200,1,"DIO-002-01"};

static void IapIdle(void);
static void IapEraseSector(u16 addr);
static u8 	EEPROM_OnChipReadByte(u16 addr);
static void EEPROM_OnChipWriteByte(u16 addr, u8 dat);

/*----------------------------
Disable ISP/IAP/EEPROM function
Make MCU in a safe state
----------------------------*/
static void IapIdle(void)
{
    IAP_CONTR = 0;                  //Close IAP function
    IAP_CMD = 0;                    //Clear command to standby
    IAP_TRIG = 0;                   //Clear trigger register
    IAP_ADDRH = 0x80;               //Data ptr point to non-EEPROM area
    IAP_ADDRL = 0;                  //Clear IAP address to prevent misuse
}


/*----------------------------
Read one byte from ISP/IAP/EEPROM area
Input: addr (ISP/IAP/EEPROM address)
Output:Flash data
----------------------------*/
static u8 EEPROM_OnChipReadByte(u16 addr)
{
    u8 dat;                       //Data buffer

    IAP_CONTR = ENABLE_IAP;         //Open IAP function, and set wait time
    IAP_CMD = CMD_READ;             //Set ISP/IAP/EEPROM READ command
    IAP_ADDRL = addr;               //Set ISP/IAP/EEPROM address low
    IAP_ADDRH = addr >> 8;          //Set ISP/IAP/EEPROM address high
    IAP_TRIG = 0x5a;                //Send trigger command1 (0x5a)
    IAP_TRIG = 0xa5;                //Send trigger command2 (0xa5)
    _nop_();                        //MCU will hold here until ISP/IAP/EEPROM operation complete
    dat = IAP_DATA;                 //Read ISP/IAP/EEPROM data
    IapIdle();                      //Close ISP/IAP/EEPROM function

    return dat;                     //Return Flash data
}
/*----------------------------
Program one byte to ISP/IAP/EEPROM area
Input: addr (ISP/IAP/EEPROM address)
       dat (ISP/IAP/EEPROM data)
Output:-
----------------------------*/
static void EEPROM_OnChipWriteByte(u16 addr, u8 dat)
{
    IAP_CONTR = ENABLE_IAP;         //Open IAP function, and set wait time
    IAP_CMD = CMD_PROGRAM;          //Set ISP/IAP/EEPROM PROGRAM command
    IAP_ADDRL = addr;               //Set ISP/IAP/EEPROM address low
    IAP_ADDRH = addr >> 8;          //Set ISP/IAP/EEPROM address high
    IAP_DATA = dat;                 //Write ISP/IAP/EEPROM data
    IAP_TRIG = 0x5a;                //Send trigger command1 (0x5a)
    IAP_TRIG = 0xa5;                //Send trigger command2 (0xa5)
    _nop_();                        //MCU will hold here until ISP/IAP/EEPROM operation complete
    IapIdle();
}
/*----------------------------
Erase one sector area
Input: addr (ISP/IAP/EEPROM address)
Output:-
----------------------------*/
static void IapEraseSector(u16 addr)
{
    IAP_CONTR = ENABLE_IAP;         //Open IAP function, and set wait time
    IAP_CMD = CMD_ERASE;            //Set ISP/IAP/EEPROM ERASE command
    IAP_ADDRL = addr;               //Set ISP/IAP/EEPROM address low
    IAP_ADDRH = addr >> 8;          //Set ISP/IAP/EEPROM address high
    IAP_TRIG = 0x5a;                //Send trigger command1 (0x5a)
    IAP_TRIG = 0xa5;                //Send trigger command2 (0xa5)
    _nop_();                        //MCU will hold here until ISP/IAP/EEPROM operation complete
    IapIdle();
}
//
void SaveDatasToEEPROM_OnChip(void)
{
  u16 i =0;
  u8 *temp=&DataSave;
	IapEraseSector(0);
	for(i=0;i<DATA_LEN;i++)
	{
		EEPROM_OnChipWriteByte(i,temp[i]);
	}
}
//
void ReadDatasFromEEPROM_OnChip(void)
{
  u16 i = 0;
	u8 *temp=&DataSave;
	if( EEPROM_OnChipReadByte(0x300)!='Y')	{SaveDatasToEEPROM_OnChip();IapEraseSector(0x300);EEPROM_OnChipWriteByte(0x300,'Y');}
	
	for(i=0;i<DATA_LEN;i++)
	{
		temp[i] = EEPROM_OnChipReadByte(i);
	}
}
/**	 Get the SoftWare version number
**				110-1.10
**/
void PrintSoftVersionFromEEPROM(void)
{
	UART_Printf("SW<%01d.%01d%01d>\n",(u16)DataSave.sw/100,(u16)DataSave.sw%100/10,(u16)DataSave.sw%100%10);
}
/**	 Save the Hardware version number
**				110-1.10
**/
void WriteSWToEEPROM(u8 SoftWareNum)
{
	DataSave.sw=SoftWareNum;
	SaveDatasToEEPROM_OnChip();
	UART_Printf("SW[%01d.%01d%01d]<OK>\n",(u16)SoftWareNum/100,(u16)SoftWareNum%100/10,(u16)SoftWareNum%100%10);
}
/**	 Get the SoftWare version number
**	 110-1.10
**/
void PrintHardVersionFromEEPROM(void)
{
	UART_Printf("HW<%01d.%01d%01d>\n",(u16)DataSave.hw/100,(u16)DataSave.hw%100/10,(u16)DataSave.hw%100%10);
}
/**	 Save the Hardware version number
**				110-1.10
**/
void WriteHWToEEPROM(u8 HardWareNum)
{
	DataSave.hw=HardWareNum;
	SaveDatasToEEPROM_OnChip();
	UART_Printf("HW[%01d.%01d%01d]<OK>\n",(u16)HardWareNum/100,(u16)HardWareNum%100/10,(u16)HardWareNum%100%10);
}
/**	 Get FSN
**				
**/
void PrintFSNFromEEPROM(void)
{
	UART_Printf("FSN<%.10s>\n",DataSave.fsn);
}
/**	 Save FSN
**				
**/
void WriteFSNToEEPROM(u8 *Fsn)
{
	u8 i;
	u8 *temp=&DataSave.fsn;
	for(i=0;i<10;i++)
	{
		temp[i]=*(Fsn++);
	}
	SaveDatasToEEPROM_OnChip();
	UART_Printf("FSN[%.10s]<OK>\n",DataSave.fsn);
}
//
u8 ROM_WriteDatas(u8 *Commands)
{
	if( strncmp(Commands,"rom[",4)==0  ) 
	{	
		char *p = NULL;
		char *s = &Commands[4];		
		float DataSet;		
		u8 DataNum=strtol(s, &p, 10);	
		if(*p==']'&& *(p+1)=='[' &&  DataNum>0 && DataNum<=ROM_LENGTH)	
		{
			s=NULL;
			DataSet=strtod(p+2, &s);	
			if(*(s-1)==']'&& *(s)=='\0' )
			{
				DataSave.ROM[DataNum-1].f32=DataSet;
//				DataSave.ROM[DataNum].Byte[0]=DataSet;
//				DataSave.ROM[DataNum].Byte[1]=DataSet>>8;
//				DataSave.ROM[DataNum].Byte[2]=DataSet>>16;
//				DataSave.ROM[DataNum].Byte[3]=DataSet>>24;
				SaveDatasToEEPROM_OnChip();
				UART_Printf("ROM[%d][%.4f]<OK>\n",(u16)DataNum,DataSave.ROM[DataNum-1].f32); 
				return 1;
			}
		}	
//		PrintNA();
		return 0;
	}	
	else return 0;
}
//
u8 ROM_ReadDatas(u8 *Commands)
{
	if( strncmp(Commands,"rom[",4)==0  ) 
	{	
		char *p = NULL;
		char *s = &Commands[4];	
		u8 DataNum=0;		
		DataNum=(u8)strtol(s, &p, 10);	
		if(*p==']'&& *(p+1)=='\0'	&& (DataNum>0 && DataNum<=ROM_LENGTH))
		{	
			UART_Printf("ROM[%d]<%.4f>\n",(u16)DataNum,DataSave.ROM[DataNum-1].f32);
			return 1;
		}
		PrintNA();
		return 1;
	}	
	else return 0;	
}

//

