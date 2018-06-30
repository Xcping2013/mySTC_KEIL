#include "STC12C5A60S2.h"
#include "intrins.h"
#include "EEPROM.h"

/*Disable ISP/IAP/EEPROM function,Make MCU in a safe state*/
void HW_IapIdle(void)
{
	IAP_CONTR=0;      //Close IAP function
	IAP_CMD=0;        //Clear command to standby
	IAP_TRIG=0;       //Clear trigger register
	IAP_ADDRH=0x80;   //Data ptr point to non-EEPROM area
	IAP_ADDRL=0;      //Clear IAP address To prevent misuse
}


///*
//* 函 数 名：Open_IAP
//* 功能描述：允许ISP/IAP
//*/
//void HW_OpenIAP(void)
//{
//    IAP_CONTR= 0x80;           //充许ISP/IAP
//} 
///*
//* 函 数 名：Close_IAP
//* 功能描述：禁止ISP/IAP
//*/
//void HW_CloseIAP(void)
//{
//    IAP_CONTR = 0x00;           //禁止ISP/IAP
//    IAP_ADDRH = 0xFF;
//    IAP_ADDRL = 0xFF;
//}
/*
* 函 数 名：Read_IAP_Byte
* 功能描述：从EEPROM指定的单元读取一个字节数据
*/
unsigned char HW_ReadIAPByte(unsigned int addr)
{  
	unsigned char dat;
	IAP_CONTR=ENABLE_IAP;
	IAP_CMD = CMD_READ;
  IAP_ADDRL = addr;
	IAP_ADDRH = addr>>8;
  IAP_TRIG = 0x5A;
  IAP_TRIG = 0xA5;                     //对IAP_TRIG先写0x5A再写0xA5，ISP/IAP命令才会生效
	_nop_();
	dat=IAP_DATA;
  HW_IapIdle();
  return dat;
}
/*
* 函 数 名：Write_IAP_Byte
* 功能描述：把一个字节数据写入EEPROM指定的单元,写入数据前应先擦除扇区
* 输入参数：addr:16bit地址；writeVal:要写入的数据
* 返 回 值：无
*/
void HW_WriteIAPByte(unsigned int addr, unsigned char dat)
{
	IAP_CONTR=ENABLE_IAP;
	IAP_CMD = CMD_PROGRAM;
	IAP_ADDRL = addr;
	IAP_ADDRH = addr >>8;
	IAP_DATA = dat;
	IAP_TRIG = 0x5A;
	IAP_TRIG = 0xA5;                     //对IAP_TRIG先写0x5A再写0xA5，ISP/IAP命令才会生效
  _nop_();
  HW_IapIdle();
}
/*
* 函 数 名：Erase_IAP_Sector
* 功能描述：擦除扇区,没有字节擦除
* 输入参数：addr：扇区地址,扇区中任意一个字节地址都是该扇区地址
* 返 回 值：无
*/
void HW_EraseIAPSector(unsigned int addr)
{ 
	 IAP_CONTR=ENABLE_IAP;
	 IAP_CMD = CMD_ERASE;
	 IAP_ADDRL = addr;
	 IAP_ADDRH = addr>>8;
	 IAP_TRIG = 0x5A;
	 IAP_TRIG = 0xA5;                     //对IAP_TRIG先写0x5A再写0xA5，ISP/IAP命令才会生效
	 _nop_();
	 HW_IapIdle();
}

//void memcpy_to_eeprom_with_checksum(unsigned int destination, char *source, unsigned int size)
//{
//  unsigned char checksum = 0;
//  for(; size > 0; size--) 
//	{ 
//    checksum = (checksum << 1) || (checksum >> 7);
//    checksum += *source;
//    HW_WriteIAPByte(destination++, *(source++)); 
//  }
//  HW_WriteIAPByte(destination, checksum);
//}

//int memcpy_from_eeprom_with_checksum(char *destination, unsigned int source, unsigned int size)
//{
//  unsigned char data checksum = 0;
//  for(; size > 0; size--) 
//	{ 
//    data = HW_ReadIAPByte(source++);
//    checksum = (checksum << 1) || (checksum >> 7);
//    checksum += data;    
//    *(destination++) = data; 
//  }
//  return(checksum == HW_ReadIAPByte(source));
//}
void EEP_Write(u8 *write,u8 len)
{
  u8 i =0;
	for(i=0;i<len;i++)
	HW_WriteIAPByte(i,write[i]);
}

void EEP_Read(u8 *read,u8	len)
{
  u8 i = 0;
	for(i=0;i<len;i++)
  read[i] = HW_ReadIAPByte(i);
}