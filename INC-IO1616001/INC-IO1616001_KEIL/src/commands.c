#include	"commands.h"
#include 	"IO.h"
#include 	"EEPROM.h"
#include 	"IIC_SOFT.h"
#include 	"Delay.h"
#include 	"UART1.h"

#include 	<string.h>
#include	<stdlib.h>

//静态函数声明
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

//大写字母转小写
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

//通讯命令解析处理
u8 ProcessCommand(char *ptr)				
{
  charConvert(ptr);
	if(strcmp("help",ptr)==0)							{Help();															return 1;	}		//命令提示
  else if(strcmp("reset",ptr)==0)				{Reset();															return 1;	}		//IO板子复位
	/******************************参数读取设置******************************************/
  else if(strcmp("sv",ptr)==0)					{Software_version();									return 1;	}		//软件版本
  else if(strcmp("hv",ptr)==0)					{Hardware_version();									return 1;	}		//硬件版本
  else if(strcmp("fsn",ptr)==0)					{Read_SN();														return 1;	}		//读取FSN
  else if(Write_SN(ptr)==1)							{UART1_SendStr("set sn ok\n");				return 1;	}		//设置FSN
	/*****************************基本IO操作*********************************************/	
	else if(CMD_GetInputStatus(ptr)==1) 																				return 1;			
	else if(CMD_SetOutputStatus(ptr)==1) 	{UART1_SendStr("set output ok\n");		return 1;	}	
	/*******QT1_X2B命令封装：传感器采集，气缸动作，继电器切换，返回值需要不同，加以区别*/
	else if(CMD_GetSensorStatus(ptr)==1) 																				return 1;			//传感器输入检测	
	else if(CMD_AirControl(ptr)==1) 			{return 1;	}		//气缸输出控制
	else if(CMD_X2B_TEST(ptr)==1) 				{ 																		return 1;	}		//继电器小板切换测试项目
	
	else	if(XPCL_RomPage(ptr)==1)							return 1;		
	
	else if(strcmp("io test",		ptr)==0)			{		IoTestFlag=1;							return 1;		}
	else if(strcmp("start test",		ptr)==0)	{		BoardTestFlag=1;							return 1;		}
	else if(strcmp("stop test",		ptr)==0)		{		BoardTestFlag=0;	IoTestFlag=0;						return 1;		}

	
	else if(ptr[0]=='\0')									{UART1_SendStr("\n");									return 1;	}		//发送回车	
	else																	{UART1_SendStr("NA\n");								return 0;	}		//
}
/******************************板		子		基		本		功		能****************************/
//基本输入口状态检测	eg:		send: "input 01" ; return:"senser1 turn on/off"  如果对应输入口接的是按键，则需要延时去抖动
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
//基本输出口状态控制 eg:		send: "output 01 1" ; 1 闭合，0断开
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
/******************************对   应  项  目  控	制	命	令	封	装****************************/
//输入传感器检测
static u8 CMD_GetSensorStatus(char *str)
{
	if( strcmp(str,"left status")==0 ) 						//左边光栅状态检测，光栅无触碰时为0，触碰后卫1.
	{
		if( INPUT3==1 || INPUT4==1 )
	  {
			UART1_SendStr("left true@\n");return 1;
		}		
		else UART1_SendStr("left false@\n");return 1;
	}	
	else if( strcmp(str,"light status")==0 ) 			//左右光栅一起检测
	{			
		if( INPUT3==1 || INPUT4==1 || INPUT5==1 || INPUT6==1)
		{
			UART1_SendStr("light touched true@\n");return 1;
		}		
		else UART1_SendStr("light touched false@\n");return 1;
	}
	
	else if( strcmp(str,"right status")==0 ) 			//右光栅状态检测
	{
		if( INPUT5==1 || INPUT6==1 )
		{
			UART1_SendStr("right true@\n");return 1;
		}	
		else UART1_SendStr("right false@\n");return 1;
	}
	
	else if( strcmp(str,"p0 status")==0 ) 				//P0位置有无产品检测，无产品时为0，可设置传感器
	{
		if( INPUT1==1)
		{	
			UART1_SendStr("p0 true@\n");return 1;	
		}
		else UART1_SendStr("p0 false@\n");return 1;
	}
	else if( strcmp(str,"p4 status")==0 ) 				//P4位置有无产品检测
	{
		if( INPUT2==1 )
		{
			UART1_SendStr("p4 true@\n");return 1;
		}		
		else UART1_SendStr("p4 false@\n");return 1;
	}
	else if( strcmp(str,"inside status")==0 ) 		//按键气缸是否处于缩回状态	 	
	{
		if( INPUT7==0 && INPUT8==1)
		{
			UART1_SendStr("inside true@\n");return 1;
		}		
		else UART1_SendStr("inside false@\n");return 1;
	}
	
	else if( strcmp(str,"outside status")==0 ) 		//按键气缸是否处于弹出状态	
	{
		if( INPUT7==1 && INPUT8==0)
		{
			UART1_SendStr("outside true@\n");return 1;
		}		
		else UART1_SendStr("outside false@\n");return 1;
	}
	else if( strcmp(str,"p2 upside status")==0 ) 	//P2垂直气缸所处位置查询	
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
	else if( strcmp(str,"p3 upside status")==0 ) 	//P3垂直气缸所处位置查询		
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

	else if( strcmp(str,"p2 status")==0 ) 				//P2爪子状态，左右一起	
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
	else if( strcmp(str,"p3 status")==0 ) 				//P3爪子状态	
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
//输出气缸控制
static u8 CMD_AirControl(char *str)
{
	if( strcmp(str,"air in")==0 ) 						//按键气缸缩进
	{
		OUTPUT15=1;
		UART1_SendStr("ok@AIR IN\n");
		return 1;	
	}
	else if( strcmp(str,"air out")==0 ) 			//按键气缸弹出
	{
		OUTPUT15=0;
		UART1_SendStr("ok@AIR OUT\n");
		return 1;
	}
	else if( strcmp(str,"p2 open")==0 ) 			//P2左右爪子都打松开
	{
		OUTPUT1=0;OUTPUT2=1;
		OUTPUT3=0;OUTPUT4=1;
		UART1_SendStr("ok@P2 OPEN\n");
		return 1;
	}
	else if( strcmp(str,"p2 close")==0 ) 			//P2左右爪子都闭合
	{
		OUTPUT1=1;OUTPUT2=0;
		OUTPUT3=1;OUTPUT4=0;
		UART1_SendStr("ok@P2 CLOSE\n");
		return 1;
	}
	else if( strcmp(str,"p3 open")==0 ) 			//P3左右爪子松开
	{
		OUTPUT5=0;OUTPUT6=1;
		OUTPUT7=0;OUTPUT8=1;
		UART1_SendStr("ok@P3 OPEN\n");
		return 1;
	}
	else if( strcmp(str,"p3 close")==0 ) 			//P3左右爪子闭合
	{
		OUTPUT5=1;OUTPUT6=0;
		OUTPUT7=1;OUTPUT8=0;
		UART1_SendStr("ok@P3 CLOSE\n");
		return 1;
	}
	return 0;
}
//测试项电路切换
static u8 CMD_X2B_TEST(char *str)
{
	if( strcmp(str,"i dut")==0 ) 																//测试DUT充电电流
	{
		OUTPUT12=1;OUTPUT11=1;OUTPUT10=1;OUTPUT9=1;								//断开其它线路
		OUTPUT13=0;OUTPUT16=0;																		//地线闭合，电源线断开
		OUTPUT14=0;																							  //串入电流表
		UART1_SendStr("ok@I DUT\n");return 1;
	}
	else if( strcmp(str,"r ea")==0 ) 														//测试DUT左边电阻
	{
		OUTPUT16=1;																								//断开地线
		OUTPUT13=1;OUTPUT14=0;OUTPUT12=1;OUTPUT11=1;OUTPUT10=1;		//断开电源线
		OUTPUT9=0;																									//接入电阻表	
		UART1_SendStr("ok@R EA\n");return 1;
	}
	else if( strcmp(str,"r eb")==0 ) 														//测试DUT右边电阻
	{
		OUTPUT16=1;																								//断开地线
		OUTPUT13=1;OUTPUT14=0;OUTPUT12=1;OUTPUT11=1;OUTPUT9=1;		//断开电源线
		OUTPUT10=0;																								//接入电阻表
		UART1_SendStr("ok@R EB\n");return 1;
	}
	else if( strcmp(str,"i eb")==0 ) 														//测试DUT左耳电流
	{
		OUTPUT16=0;																								//地线闭合
		OUTPUT13=1;OUTPUT14=1;OUTPUT11=1;OUTPUT10=1;OUTPUT9=1;		//电源线闭合
		OUTPUT12=0;																								//电流表串入耳机线路中
		UART1_SendStr("ok@I EB\n");return 1;	
	}	
	else if( strcmp(str,"i ea")==0 ) 														//测试DUT右耳电流
	{
		OUTPUT16=0;																								//DUT地线闭合
		OUTPUT13=1;OUTPUT14=1;OUTPUT12=1;OUTPUT10=1;OUTPUT9=1;		//其它继电器断开
		OUTPUT11=0;																									//电流表串入耳机线路中
		UART1_SendStr("ok@I EA\n");return 1;
	}	
	else if( strcmp(str,"power on")==0 ) 												//DUT：GND与VCC闭合导通
	{
		OUTPUT16=0;	OUTPUT14=1;	OUTPUT13=1;																  //闭合地线、电源线																		
		OUTPUT9=1;OUTPUT10=1;OUTPUT11=1;OUTPUT12=1;	  //断开其他
		UART1_SendStr("ok@POWER ON\n");return 1;
	}	
	else if( strcmp(str,"power off")==0 ) 											//DUT：GND与VCC断开
	{
		OUTPUT16=0;	OUTPUT14=0;	OUTPUT13=1;												//电源线   保留地线
		OUTPUT9=1;OUTPUT10=1;OUTPUT11=1;OUTPUT12=1;							  //断开其他	
		UART1_SendStr("ok@POWER OFF\n");return 1;
	}
	else if( strcmp(str,"p2 done")==0 ) 												//P2测试完成，线路切换为充电状态，不接如万用表
	{	
		OUTPUT16=0;		
		OUTPUT13=1;OUTPUT14=1;OUTPUT12=1;OUTPUT11=1;OUTPUT10=1;OUTPUT9=1;
		UART1_SendStr("ok@P2 DONE\n");return 1;
	}
	return 0;
}
//帮助提示
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
//板子软复位
static void Reset(void)
{
  IAP_CONTR=0xa0;
}
//软件版本
static void Software_version(void)
{
  UART1_Printf("ver3.0\n");
}
///硬件版本
static void Hardware_version(void)
{
  UART1_Printf("ver2.2\n"); 
}
//读SN
static void Read_SN(void)
{
  u8 i = 0;
	u8 SNNO[40];
	EEP_Read(SNNO,40);
	SNNO[39]='\0';
	UART1_Printf("fsn:%S\n",SNNO);
}
//写SN
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
		if(	*p==' ' && PageNum>0 && PageNum <(256-10)	)			//前10页用于FSN+ROM 
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
		if(	*p=='\0' && PageNum>0 && PageNum <(256-10)	)			//前10页用于FSN+ROM 
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