#ifndef __EEPROM_H__
#define __EEPROM_H__

#include "STC12C5A60S2.h"
/*Define ISP/IAP/EEPROM command */
#define CMD_IDLE		  0  //Stand-By
#define CMD_READ 			1  //byte-read
#define CMD_PROGRAM 	2 //byte-program
#define CMD_ERASE 		3  //sector-erase

#define ENABLE_IAP    0x80
#define IAP_STARTADDRESS   0x0000  
#define IAP_ENDADDRESS     0x03FF



void HW_IapIdle(void);
//void HW_OpenIAP(void);
//void HW_CloseIAP(void);
unsigned char HW_ReadIAPByte(unsigned int addr);
void HW_WriteIAPByte(unsigned int addr, unsigned char dat);
//void HW_WriteIAPByte(unsigned int addr, unsigned char dat);
void HW_EraseIAPSector(unsigned int addr);
void EEP_Write(u8 *write,u8 len);
void EEP_Read(u8 *read,u8	len);
//0000H~03FFH
//void memcpy_to_eeprom_with_checksum(unsigned int destination, char *source, unsigned int size);
//int memcpy_from_eeprom_with_checksum(char *destination, unsigned int source, unsigned int size);
#endif