#include "IIC_SOFT.h"
#include "delay.h"

//����IIC��ʼ�ź�
void IIC_Start(void)
{
	//IIC_SDA_OUT();     //sda�����
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	delay_us(4);
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL=0;//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
void IIC_Stop(void)
{
	//IIC_SDA_OUT();//sda�����
	IIC_SCL=0;
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_SCL=1; 
	IIC_SDA=1;//����I2C���߽����ź�
	delay_us(4);							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	//IIC_SDA_IN();      //SDA����Ϊ����  
	IIC_SDA=1;delay_us(1);	   
	IIC_SCL=1;delay_us(1);	 
	while(IIC_READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL=0;//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
void IIC_Ack(void)
{
	IIC_SCL=0;
	//IIC_SDA_OUT();
	IIC_SDA=0;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}
//������ACKӦ��		    
void IIC_NAck(void)
{
	IIC_SCL=0;
	//IIC_SDA_OUT();
	IIC_SDA=1;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
		//IIC_SDA_OUT(); 	    
    IIC_SCL=0;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        IIC_SDA=(txd&0x80)>>7;
        txd<<=1; 	  
		delay_us(2);  //��TEA5767��������ʱ���Ǳ����
		IIC_SCL=1;
		delay_us(2);
		IIC_SCL=0;	
		delay_us(2);
    }	 
		//delay_us(5);
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	IIC_SDA_IN();//SDA����Ϊ����
    for(i=0;i<8;i++ )
	{
        IIC_SCL=0; 
        delay_us(2);
				IIC_SCL=1;
		
        receive<<=1;
        if(IIC_READ_SDA)receive++;   
				delay_us(1); 
    }					 
    if (!ack)
        IIC_NAck();//����nACK
    else
        IIC_Ack(); //����ACK   
    return receive;
}


//
void IIC_DeviceReadBytes(u8 DeviceAddr, u16 ReadAddr, u8 *RegData, u8 len, u8 DeviceType )
{	  	    																 
  IIC_Start();  
	if(DeviceType==3)						//�Ĵ�����ַ��������ַ���ã���AT24C02~AT24C64
	{
		IIC_Send_Byte(DeviceAddr & 0xFE +((ReadAddr/256)<<1));   //����������ַ0XA0,д���� 
		IIC_Wait_Ack();	
	  IIC_Send_Byte(ReadAddr%256);   			 //���͵͵�ַ
	  IIC_Wait_Ack(); 
	}	
	else if(DeviceType==2)		//���ֽڼĴ�����ַ��	       ��AT24C125~AT24C512
	{
		IIC_Send_Byte(DeviceAddr & 0xFE);   //д������ַ 	  
		IIC_Wait_Ack();
		IIC_Send_Byte(ReadAddr>>8);				 //���͸ߵ�ַ
		IIC_Wait_Ack();
		IIC_Send_Byte(ReadAddr%256);  		 //���͵͵�ַ
		IIC_Wait_Ack(); 	 										  		
	}	
	else if(DeviceType==1)	//һ�ֽڼĴ�����ַ						
	{
		IIC_Send_Byte(DeviceAddr & 0xFE);   //д������ַ 	  
		IIC_Wait_Ack();
		IIC_Send_Byte(ReadAddr%256);  		  //���͵͵�ַ
		IIC_Wait_Ack(); 	 										  		
	}	
	
	IIC_Start();  	 	   
	IIC_Send_Byte(DeviceAddr | 0x01);    //�������ģʽ			   
	IIC_Wait_Ack();	
	
//	while(len--)
//	{
//		*(RegData++)=IIC_Read_Byte(1);	
//	}
		while(len!=1)
	{
		len--;
		*(RegData++)=IIC_Read_Byte(1);	
	}
	*(RegData++)=IIC_Read_Byte(0);
  IIC_Stop();												 //����һ��ֹͣ����	    
}
//
void IIC_DeviceWriteBytes(u8 DeviceAddr, u16 WriteAddr, u8  *RegData , u8 len, u8 DeviceType)
{	
  IIC_Start();  
	if(DeviceType==3)
	{
		IIC_Send_Byte(DeviceAddr & 0xFE +((WriteAddr/256)<<1));   //����������ַ0XA0,д���� 
		IIC_Wait_Ack();	
	  IIC_Send_Byte(WriteAddr%256);   			 //���͵͵�ַ
	  IIC_Wait_Ack(); 
	}	
	else if(DeviceType==2)
	{
		IIC_Send_Byte(DeviceAddr & 0xFE);   //д������ַ 	  
		IIC_Wait_Ack();
		IIC_Send_Byte(WriteAddr>>8);				//���͸ߵ�ַ
		IIC_Wait_Ack();
		IIC_Send_Byte(WriteAddr%256);  		 //���͵͵�ַ
		IIC_Wait_Ack(); 	 										  		
	}	
	else if(DeviceType==1)
	{
		IIC_Send_Byte(DeviceAddr & 0xFE);   //д������ַ 	  
		IIC_Wait_Ack();
		IIC_Send_Byte(WriteAddr%256);  		 //���͵͵�ַ
		IIC_Wait_Ack(); 	 										  		
	}	
 	
  while(len--)
	{
		IIC_Send_Byte(*(RegData++));     	//�����ֽ�							   
		IIC_Wait_Ack();
		//HAL_Delay(10);		
	}
	
  IIC_Stop();													//����һ��ֹͣ���� 
	//HAL_Delay(10);
	delay_ms(10);
}
//





















