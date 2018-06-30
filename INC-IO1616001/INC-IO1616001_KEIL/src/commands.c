#include	"commands.h"
#include 	"IO.h"
#include 	"EEPROM.h"
#include 	"IIC_SOFT.h"
#include 	"Delay.h"
#include 	"UART1.h"

#include 	<string.h>
#include	<stdlib.h>

//��̬��������
static void charConvert( char *str);
static void Help(void);
static void Reset(void);
static void Software_version(void);
static void Hardware_version(void);
static void Read_SN(void);
static u8 Write_SN(char *str);

static u8 CMD_GetInputStatus(char *str);
static u8 CMD_GetSensorStatus(char *str);
static u8 CMD_SetOutputStatus(char *str);
static u8 CMD_AirControl(char *str);
static u8 CMD_X2B_TEST(char *str);
static u8 XPCL_RomPage(char *Commands);

//��д��ĸתСд
static void charConvert( char *str)		
{
    while(*str!='\0')
    {
        if( ((*str)>='A')&&((*str)<='Z') )
        {
            *str=*str+32;
        }
        str++;
    }
}

//ͨѶ�����������
u8 ProcessCommand(char *ptr)				
{
  charConvert(ptr);
	if(strcmp("help",ptr)==0)							{Help();															return 1;	}		//������ʾ
  else if(strcmp("reset",ptr)==0)				{Reset();															return 1;	}		//IO���Ӹ�λ
	/******************************������ȡ����******************************************/
  else if(strcmp("sv",ptr)==0)					{Software_version();									return 1;	}		//����汾
  else if(strcmp("hv",ptr)==0)					{Hardware_version();									return 1;	}		//Ӳ���汾
  else if(strcmp("fsn",ptr)==0)					{Read_SN();														return 1;	}		//��ȡFSN
  else if(Write_SN(ptr)==1)							{UART1_SendStr("set sn ok\n");				return 1;	}		//����FSN
	/*****************************����IO����*********************************************/	
	else if(CMD_GetInputStatus(ptr)==1) 																				return 1;			
	else if(CMD_SetOutputStatus(ptr)==1) 	{UART1_SendStr("set output ok\n");		return 1;	}	
	/*******QT1_X2B�����װ���������ɼ������׶������̵����л�������ֵ��Ҫ��ͬ����������*/
	else if(CMD_GetSensorStatus(ptr)==1) 																				return 1;			//������������	
	else if(CMD_AirControl(ptr)==1) 			{return 1;	}		//�����������
	else if(CMD_X2B_TEST(ptr)==1) 				{ 																		return 1;	}		//�̵���С���л�������Ŀ
	
	else	if(XPCL_RomPage(ptr)==1)							return 1;		
	
	else if(strcmp("io test",		ptr)==0)			{		IoTestFlag=1;							return 1;		}
	else if(strcmp("start test",		ptr)==0)	{		BoardTestFlag=1;							return 1;		}
	else if(strcmp("stop test",		ptr)==0)		{		BoardTestFlag=0;	IoTestFlag=0;						return 1;		}

	
	else if(ptr[0]=='\0')									{UART1_SendStr("\n");									return 1;	}		//���ͻس�	
	else																	{UART1_SendStr("NA\n");								return 0;	}		//
}
/******************************��		��		��		��		��		��****************************/
//���������״̬���	eg:		send: "input 01" ; return:"senser1 turn on/off"  �����Ӧ����ڽӵ��ǰ���������Ҫ��ʱȥ����
static u8 CMD_GetInputStatus(char *str)
{
  if((strncmp("input",str,5)==0) && (str[5]==' ') )
   {
		 u8 Pin = ((str[6]-0x30)*10)+((str[7])-0x30);	
     switch(Pin)
		 {
				case 1:	if(INPUT1  ==  0)
								{						
									UART1_SendStr("senser1 turn on\n"); return 1;
								}
								else UART1_SendStr("senser1 turn off\n");return 1;
								//break;
								
				case 2:	if(INPUT2  ==  0)
								{
									UART1_SendStr("senser2 turn on\n"); return 1;
								}
								else UART1_SendStr("senser2 turn off\n");return 1;
								//break;
				
				case 3:	if(INPUT3==0)
								{
									UART1_SendStr("senser3 turn on\n");return 1;
								}
								else UART1_SendStr("senser3 turn off\n");return 1;
								//break;
				
				case 4:	if(INPUT4==0)
								{
									UART1_SendStr("senser4 turn on\n");return 1;
								}
								else UART1_SendStr("senser4 turn off\n");return 1;
								//break;
				
				case 5:	if(INPUT5==0)
								{
									UART1_Printf("senser5 turn on\n");return 1;
								}
								else UART1_Printf("senser5 turn off\n");return 1;
								//break;
				
				case 6:	if(INPUT6==0)
								{	
									UART1_Printf("senser6 turn on\n");return 1;
								}
								else UART1_Printf("senser6 turn off\n");return 1;
								//break;
				
				case 7:	if(INPUT7==0)
								{	
									UART1_Printf("senser7 turn on\n");return 1;
								}
								else UART1_Printf("senser7 turn off\n");return 1;
								//break;
				case 8:	if(INPUT8==0){UART1_Printf("senser8 turn on\n");return 1;}
								UART1_Printf("senser8 turn off\n");return 1;
								break;
				case 9:	if(INPUT9==0){UART1_Printf("senser9 turn on\n");return 1;}
								UART1_Printf("senser9 turn off\n");return 1;
								break;
				case 10:	if(INPUT10==0){UART1_Printf("senser10 turn on\n");return 1;}
								UART1_Printf("senser10 turn off\n");return 1;
								break;
				case 11:	if(INPUT11==0){UART1_Printf("senser11 turn on\n");return 1;}
								UART1_Printf("senser11 turn off\n");return 1;
								break;
				case 12:	if(INPUT12==0){UART1_Printf("senser12 turn on\n");return 1;}
								UART1_Printf("senser12 turn off\n");return 1;
								break;		
				case 13:	if(INPUT13==0){UART1_Printf("senser13 turn on\n");return 1;}
								UART1_Printf("senser13 turn off\n");return 1;
								break;		
				case 14:	if(INPUT14==0){UART1_Printf("senser14 turn on\n");return 1;}
								UART1_Printf("senser14 turn off\n");return 1;
								break;			
				case 15:	if(INPUT15==0){UART1_Printf("senser15 turn on\n");return 1;}
								UART1_Printf("senser15 turn off\n");return 1;
								break;	
				case 16:	if(INPUT16==0){UART1_Printf("senser16 turn on\n");return 1;}
								UART1_Printf("senser16 turn off\n");return 1;
								break;					
				
				default: return 0;	//break;
		 }
   }
  	return 0;	
}
//���������״̬���� eg:		send: "output 01 1" ; 1 �պϣ�0�Ͽ�
static u8 CMD_SetOutputStatus(char *str)
{
  if((strncmp("output",str,6)==0) && (str[6]==' ') )
   {
		 u8 Pin = ((str[7]-0x30)*10)+((str[8])-0x30);
     bit Val	= str[10]-0x30;	 
     switch(Pin)
     {
       case 1:  OUTPUT1  = ~Val; return 1;//break;
			 case 2:  OUTPUT2  = ~Val; return 1;//break;
			 case 3:  OUTPUT3  = ~Val; return 1;//break;
			 case 4:  OUTPUT4  = ~Val; return 1;//break;
			 case 5:  OUTPUT5  = ~Val; return 1;//break;
			 case 6:  OUTPUT6  = ~Val; return 1;//break;
			 case 7:  OUTPUT7  = ~Val; return 1;//break;		 
			 case 8:  OUTPUT8  = ~Val; return 1;//break;
			 
			 case 9:  OUTPUT9  = ~Val; return 1;//break;
			 case 10: OUTPUT10 = ~Val; return 1;//break;
			 case 11: OUTPUT11 = ~Val; return 1;//break;
			 case 12: OUTPUT12 = ~Val; return 1;//break;
			 case 13: OUTPUT13 = ~Val; return 1;//break;
			 case 14: OUTPUT14 = ~Val; return 1;//break;
			 case 15: OUTPUT15 = ~Val; return 1;//break;
			 case 16: OUTPUT16 = ~Val; return 1;//break;
			 
			 default: return 0;//break;			 
     }
   }
  return 0;	 
}
/******************************��   Ӧ  ��  Ŀ  ��	��	��	��	��	װ****************************/
//���봫�������
static u8 CMD_GetSensorStatus(char *str)
{
	if( strcmp(str,"left status")==0 ) 						//��߹�դ״̬��⣬��դ�޴���ʱΪ0����������1.
	{
		if( INPUT3==1 || INPUT4==1 )
	  {
			UART1_SendStr("left true@\n");return 1;
		}		
		else UART1_SendStr("left false@\n");return 1;
	}	
	else if( strcmp(str,"light status")==0 ) 			//���ҹ�դһ����
	{			
		if( INPUT3==1 || INPUT4==1 || INPUT5==1 || INPUT6==1)
		{
			UART1_SendStr("light touched true@\n");return 1;
		}		
		else UART1_SendStr("light touched false@\n");return 1;
	}
	
	else if( strcmp(str,"right status")==0 ) 			//�ҹ�դ״̬���
	{
		if( INPUT5==1 || INPUT6==1 )
		{
			UART1_SendStr("right true@\n");return 1;
		}	
		else UART1_SendStr("right false@\n");return 1;
	}
	
	else if( strcmp(str,"p0 status")==0 ) 				//P0λ�����޲�Ʒ��⣬�޲�ƷʱΪ0�������ô�����
	{
		if( INPUT1==1)
		{	
			UART1_SendStr("p0 true@\n");return 1;	
		}
		else UART1_SendStr("p0 false@\n");return 1;
	}
	else if( strcmp(str,"p4 status")==0 ) 				//P4λ�����޲�Ʒ���
	{
		if( INPUT2==1 )
		{
			UART1_SendStr("p4 true@\n");return 1;
		}		
		else UART1_SendStr("p4 false@\n");return 1;
	}
	else if( strcmp(str,"inside status")==0 ) 		//���������Ƿ�������״̬	 	
	{
		if( INPUT7==0 && INPUT8==1)
		{
			UART1_SendStr("inside true@\n");return 1;
		}		
		else UART1_SendStr("inside false@\n");return 1;
	}
	
	else if( strcmp(str,"outside status")==0 ) 		//���������Ƿ��ڵ���״̬	
	{
		if( INPUT7==1 && INPUT8==0)
		{
			UART1_SendStr("outside true@\n");return 1;
		}		
		else UART1_SendStr("outside false@\n");return 1;
	}
	else if( strcmp(str,"p2 upside status")==0 ) 	//P2��ֱ��������λ�ò�ѯ	
	{
		if( INPUT13==0 && INPUT14==1 )
		{				
			UART1_SendStr("p2 downside true@\n");return 1;
		}		
		else if( INPUT13==1 && INPUT14==0 )
		{	
			UART1_SendStr("p2 upside true@\n");return 1;
		}		
		else	UART1_SendStr("p2 status undefine@\n");return 1;
	}
	else if( strcmp(str,"p3 upside status")==0 ) 	//P3��ֱ��������λ�ò�ѯ		
	{
		if( INPUT15==0 && INPUT16==1 )
		{
			UART1_SendStr("p3 downside true@\n");return 1;
		}		
		else if( INPUT15==1 && INPUT16==0 )
		{	
			UART1_SendStr("p3 upside true@\n");return 1;
		}		
		else	UART1_SendStr("p3 status undefine@\n");return 1;
	}

	else if( strcmp(str,"p2 status")==0 ) 				//P2צ��״̬������һ��	
	{
		if( INPUT9==1 && INPUT10==1 )
		{	
			UART1_SendStr("p2 open@\n");return 1;	
		}
		else if( INPUT9==0 && INPUT10==0 )
		{	
			UART1_SendStr("p2 close@\n");return 1;
		}				
		else	UART1_SendStr("p2 undefine@\n");return 1;
	}	
	else if( strcmp(str,"p3 status")==0 ) 				//P3צ��״̬	
	{
		if( INPUT11==0 && INPUT12==0 )
		{	
			UART1_SendStr("p3 close@\n");return 1;	
		}
		else if( INPUT11==1 && INPUT12==1 )
		{	
			UART1_SendStr("p3 open@\n");return 1;
		}		
		else UART1_SendStr("p3 undefine@\n");return 1;
	}	
	return 0;
}
//������׿���
static u8 CMD_AirControl(char *str)
{
	if( strcmp(str,"air in")==0 ) 						//������������
	{
		OUTPUT15=1;
		UART1_SendStr("ok@AIR IN\n");
		return 1;	
	}
	else if( strcmp(str,"air out")==0 ) 			//�������׵���
	{
		OUTPUT15=0;
		UART1_SendStr("ok@AIR OUT\n");
		return 1;
	}
	else if( strcmp(str,"p2 open")==0 ) 			//P2����צ�Ӷ����ɿ�
	{
		OUTPUT1=0;OUTPUT2=1;
		OUTPUT3=0;OUTPUT4=1;
		UART1_SendStr("ok@P2 OPEN\n");
		return 1;
	}
	else if( strcmp(str,"p2 close")==0 ) 			//P2����צ�Ӷ��պ�
	{
		OUTPUT1=1;OUTPUT2=0;
		OUTPUT3=1;OUTPUT4=0;
		UART1_SendStr("ok@P2 CLOSE\n");
		return 1;
	}
	else if( strcmp(str,"p3 open")==0 ) 			//P3����צ���ɿ�
	{
		OUTPUT5=0;OUTPUT6=1;
		OUTPUT7=0;OUTPUT8=1;
		UART1_SendStr("ok@P3 OPEN\n");
		return 1;
	}
	else if( strcmp(str,"p3 close")==0 ) 			//P3����צ�ӱպ�
	{
		OUTPUT5=1;OUTPUT6=0;
		OUTPUT7=1;OUTPUT8=0;
		UART1_SendStr("ok@P3 CLOSE\n");
		return 1;
	}
	return 0;
}
//�������·�л�
static u8 CMD_X2B_TEST(char *str)
{
	if( strcmp(str,"i dut")==0 ) 																//����DUT������
	{
		OUTPUT12=1;OUTPUT11=1;OUTPUT10=1;OUTPUT9=1;								//�Ͽ�������·
		OUTPUT13=0;OUTPUT16=0;																		//���߱պϣ���Դ�߶Ͽ�
		OUTPUT14=0;																							  //���������
		UART1_SendStr("ok@I DUT\n");return 1;
	}
	else if( strcmp(str,"r ea")==0 ) 														//����DUT��ߵ���
	{
		OUTPUT16=1;																								//�Ͽ�����
		OUTPUT13=1;OUTPUT14=0;OUTPUT12=1;OUTPUT11=1;OUTPUT10=1;		//�Ͽ���Դ��
		OUTPUT9=0;																									//��������	
		UART1_SendStr("ok@R EA\n");return 1;
	}
	else if( strcmp(str,"r eb")==0 ) 														//����DUT�ұߵ���
	{
		OUTPUT16=1;																								//�Ͽ�����
		OUTPUT13=1;OUTPUT14=0;OUTPUT12=1;OUTPUT11=1;OUTPUT9=1;		//�Ͽ���Դ��
		OUTPUT10=0;																								//��������
		UART1_SendStr("ok@R EB\n");return 1;
	}
	else if( strcmp(str,"i eb")==0 ) 														//����DUT�������
	{
		OUTPUT16=0;																								//���߱պ�
		OUTPUT13=1;OUTPUT14=1;OUTPUT11=1;OUTPUT10=1;OUTPUT9=1;		//��Դ�߱պ�
		OUTPUT12=0;																								//�������������·��
		UART1_SendStr("ok@I EB\n");return 1;	
	}	
	else if( strcmp(str,"i ea")==0 ) 														//����DUT�Ҷ�����
	{
		OUTPUT16=0;																								//DUT���߱պ�
		OUTPUT13=1;OUTPUT14=1;OUTPUT12=1;OUTPUT10=1;OUTPUT9=1;		//�����̵����Ͽ�
		OUTPUT11=0;																									//�������������·��
		UART1_SendStr("ok@I EA\n");return 1;
	}	
	else if( strcmp(str,"power on")==0 ) 												//DUT��GND��VCC�պϵ�ͨ
	{
		OUTPUT16=0;	OUTPUT14=1;	OUTPUT13=1;																  //�պϵ��ߡ���Դ��																		
		OUTPUT9=1;OUTPUT10=1;OUTPUT11=1;OUTPUT12=1;	  //�Ͽ�����
		UART1_SendStr("ok@POWER ON\n");return 1;
	}	
	else if( strcmp(str,"power off")==0 ) 											//DUT��GND��VCC�Ͽ�
	{
		OUTPUT16=0;	OUTPUT14=0;	OUTPUT13=1;												//��Դ��   ��������
		OUTPUT9=1;OUTPUT10=1;OUTPUT11=1;OUTPUT12=1;							  //�Ͽ�����	
		UART1_SendStr("ok@POWER OFF\n");return 1;
	}
	else if( strcmp(str,"p2 done")==0 ) 												//P2������ɣ���·�л�Ϊ���״̬�����������ñ�
	{	
		OUTPUT16=0;		
		OUTPUT13=1;OUTPUT14=1;OUTPUT12=1;OUTPUT11=1;OUTPUT10=1;OUTPUT9=1;
		UART1_SendStr("ok@P2 DONE\n");return 1;
	}
	return 0;
}
//������ʾ
static void Help(void)
{
	UART1_Printf("help-------------------------command list and description\n");
	UART1_Printf("reset------------------------reset fixture\n");
	UART1_Printf("fsn--------------------------get the fixture SN number\n");
	UART1_Printf("sn:xx---xxxx-----------------set the fixture SN number\n");		
	UART1_Printf("sv---------------------------get the fixture software version number\n");
	UART1_Printf("hv---------------------------get the fixture hardware version number\n");		
	UART1_Printf("SAVE INFO XX YYYYY\n");
	UART1_Printf("READ INFO XX\n");

	UART1_Printf("input xx---------------------get the input pin status\n");
	UART1_Printf("output xx y------------------set the output pin to y\n");	
	
	UART1_Printf("air in ----------------------cylinder in\n");
	UART1_Printf("air out ---------------------cylinder out\n");
	UART1_Printf("p2 open ---------------------p2 claw open\n");
	UART1_Printf("p2 close --------------------p2 claw close\n");
	UART1_Printf("p3 open ---------------------p3 claw open\n");
	UART1_Printf("p3 close --------------------p3 claw close\n");

	UART1_Printf("i dut -----------------------switch to measure dut charging current\n");	
	UART1_Printf("r ea ------------------------switch to measure earphoneA resistance\n");
	UART1_Printf("r eb ------------------------switch to measure earphoneB resistance\n");
	UART1_Printf("i ea ------------------------switch to measure earphoneA current\n");
	UART1_Printf("i eb ------------------------switch to measure earphoneB current\n");
	UART1_Printf("p2 done ---------------------dut connect to power supply,out of measure mode\n");
	UART1_Printf("power on --------------------dut connect to power supply\n");
	UART1_Printf("power off -------------------dut disconnect to power supply\n");
	
	UART1_Printf("left status------------------\n");
	UART1_Printf("right status-----------------\n");
	UART1_Printf("light status-----------------\n");
	UART1_Printf("p0/1/4 status----------------\n");
	
	UART1_Printf("inside status----------------\n");
	UART1_Printf("outside status--------------\n");	

	UART1_Printf("p2 status----------------\n");
	UART1_Printf("p2 upside status----------------\n");
	
	UART1_Printf("p3 status----------------\n");
	UART1_Printf("p3 upside status----------------\n");
	
}
//������λ
static void Reset(void)
{
  IAP_CONTR=0xa0;
}
//����汾
static void Software_version(void)
{
  UART1_Printf("ver3.0\n");
}
///Ӳ���汾
static void Hardware_version(void)
{
  UART1_Printf("ver2.2\n"); 
}
//��SN
static void Read_SN(void)
{
  u8 i = 0;
	u8 SNNO[40];
	EEP_Read(SNNO,40);
	SNNO[39]='\0';
	UART1_Printf("fsn:%S\n",SNNO);
}
//дSN
static u8 Write_SN(u8 *str)
{
  u8 m = 0;
	u8 buf[40];
	if(	(str[0]=='s')	&&	(str[1]=='n')	&&	(str[2]==':')	)
	{
    for(m=3;m<37;m++)
		{
      buf[m-3] = str[m];
    }
		HW_EraseIAPSector(0);
		EEP_Write(buf,40);
		return 1;
  }
	else
	{
    return 0;
  }
}
//
static u8 XPCL_RomPage(char *Commands)
{
	if( strncmp(Commands,"save info ",10)==0  ) 
	{	
		char *p = NULL;
		char *s = &Commands[10];	
		u16 PageNum=0;	
		PageNum=strtol(s, &p, 10);	
		P15=1;P16=1;
		if(	*p==' ' && PageNum>0 && PageNum <(256-10)	)			//ǰ10ҳ����FSN+ROM 
		{
			IIC_DeviceWriteBytes(0xA0,64*(10+PageNum),(u8 *)p+1,64,2);
			UART1_Printf("save info %d OK\n",PageNum); 
			return 1;
		}	
	  UART1_SendStr("<NA>\n");return 1;
	}
	if( strncmp(Commands,"read info ",10)==0  ) 
	{	
		char *p = NULL;
		char *s = &Commands[10];	
		u16 PageNum=0;	
		u8 DataRead[64]={'\0'};
		PageNum=strtol(s, &p, 10);	
		P15=1;P16=1;
		if(	*p=='\0' && PageNum>0 && PageNum <(256-10)	)			//ǰ10ҳ����FSN+ROM 
		{
			IIC_DeviceReadBytes(0xA0,64*(10+PageNum),	DataRead,64,2);
			UART1_Printf("read info %d %.64s\n",PageNum,DataRead);
			return 1;
		}	
	  UART1_SendStr("<NA>\n");return 1;
	}
	else return 0;
}
//
////////////////////////////////