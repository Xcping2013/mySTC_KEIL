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
#define IIC_READ_SDA   	P07  			 //����SDA 


//IIC���в�������
void IIC_Start(void);										//����IIC��ʼ�ź�
void IIC_Stop(void);	  								//����IICֹͣ�ź�
void IIC_Send_Byte(u8 txd);							//IIC����һ���ֽ�
u8 	 IIC_Read_Byte(unsigned char ack);	//IIC��ȡһ���ֽ�
u8 	 IIC_Wait_Ack(void); 								//IIC�ȴ�ACK�ź�
void IIC_Ack(void);											//IIC����ACK�ź�
void IIC_NAck(void);										//IIC������ACK�ź�

void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 Rdata);
u8 	 IIC_Read_One_Byte(u8 daddr,u8 addr);	  

void IIC_DeviceReadBytes(u8 DeviceAddr, u16 ReadAddr, u8 *RegData, u8 len, u8 DeviceType );
void IIC_DeviceWriteBytes(u8 DeviceAddr, u16 RegAddr, u8 *RegData , u8 len, u8 DeviceType);

#endif
















