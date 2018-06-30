#ifndef __IIC_SOFT_H
#define __IIC_SOFT_H

#include "STC12C5A60S2.h"
#include "delay.h"

//SCL-PIN1-P15
//SDA-PIN2-P16
//IIC
#define IIC_SDA_IN()  	P07=1;	delay_us(2);
#define IIC_SDA_OUT() 	

#define IIC_SCL    			P41				 //SCL
#define IIC_SDA    			P07				 //SDA	 
#define IIC_READ_SDA   	P07  			 //输入SDA 


//IIC所有操作函数
void IIC_Start(void);										//发送IIC开始信号
void IIC_Stop(void);	  								//发送IIC停止信号
void IIC_Send_Byte(u8 txd);							//IIC发送一个字节
u8 	 IIC_Read_Byte(unsigned char ack);	//IIC读取一个字节
u8 	 IIC_Wait_Ack(void); 								//IIC等待ACK信号
void IIC_Ack(void);											//IIC发送ACK信号
void IIC_NAck(void);										//IIC不发送ACK信号

void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 Rdata);
u8 	 IIC_Read_One_Byte(u8 daddr,u8 addr);	  

void IIC_DeviceReadBytes(u8 DeviceAddr, u16 ReadAddr, u8 *RegData, u8 len, u8 DeviceType );
void IIC_DeviceWriteBytes(u8 DeviceAddr, u16 RegAddr, u8 *RegData , u8 len, u8 DeviceType);

#endif
















