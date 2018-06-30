/**
  \file 		EEPROM_OnChip.h
  \author 	Xcping2016
  \version 	1.00

  \brief 	

  This file contains the definitions of the functions from the EEPROM_OnChip.c
  module.
*/
#ifndef __EEPROM_ONCHIP_H__
#define __EEPROM_ONCHIP_H__

#include "main.h"

/*Define ISP/IAP/EEPROM command */
#define CMD_IDLE		  0  //Stand-By
#define CMD_READ 			1  //byte-read
#define CMD_PROGRAM 	2 //byte-program
#define CMD_ERASE 		3  //sector-erase

/*Define ISP/IAP/EEPROM operation const for IAP_CONTR*/
//#define ENABLE_IAP 0x80          		 //if SYSCLK<30MHz
	#if (HSE_USED==HSE_22MHZ)
		#define ENABLE_IAP 0x81            //if SYSCLK<24MHz
	#elif (HSE_USED==HSE_12MHZ)
		#define ENABLE_IAP  0x82           //if SYSCLK<20MHz
	#elif (HSE_USED==HSE_11MHZ)
		#define ENABLE_IAP 0x83           //if SYSCLK<12MHz
//#define ENABLE_IAP 0x84           //if SYSCLK<6MHz
//#define ENABLE_IAP 0x85           //if SYSCLK<3MHz
//#define ENABLE_IAP 0x86           //if SYSCLK<2MHz
//#define ENABLE_IAP 0x87           //if SYSCLK<1MHz
	#endif

#define IAP_STARTADDRESS   0x0000  
#define IAP_ENDADDRESS     0x03FF

#define IAP_ADDRESS		   0x0400

	
void PrintSoftVersionFromEEPROM(void);
void PrintHardVersionFromEEPROM(void);
void PrintFSNFromEEPROM(void);

void WriteSWToEEPROM(u8 SoftWareNum);
void WriteHWToEEPROM(u8 HardWareNum);
void WriteFSNToEEPROM(u8 *Fsn);



void ReadDatasFromEEPROM_OnChip(void);
void SaveDatasToEEPROM_OnChip(void);

u8 ROM_ReadDatas(u8 *Commands);
u8 ROM_WriteDatas(u8 *Commands);

//0000H~03FFH
//void memcpy_to_eeprom_with_checksum(unsigned int destination, char *source, unsigned int size);
//int memcpy_from_eeprom_with_checksum(char *destination, unsigned int source, unsigned int size);
#endif
//
