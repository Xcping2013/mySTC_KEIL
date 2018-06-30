#include 	"main.h"
#include	"commands.h"
#include 	"SysControl.h"
#include 	"IO.h"
#include 	"UART.h"
#include 	"EEPROM_OnChip.h"
#include 	"24cxx.h"
#include 	<string.h>
#include	<stdlib.h>
#include	<ctype.h>

static void MakeLowercase( char *str);
static void PrintCommandlist(void);
static u8   Cmd_RomPage(char *Commands);

//大写字母转小写
static void MakeLowercase( char *str)		
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
u8 ProcessCommand(char *Commands)				
{
  MakeLowercase(Commands);
	if(PrintInputStatus(Commands)==1)							return 1;
	else if(SetOutputStatus(Commands)==1) 				return 1;
	else if(ROM_WriteDatas(Commands)==1) 					return 1;
	else if(ROM_ReadDatas(Commands)==1) 					return 1;
	
	else if(strcmp("help",Commands)==0)				{		PrintCommandlist();								return 1;		}		
	else if(strcmp("reset",Commands)==0)			{		ResetMcuToMain();									return 1;		}		
	//else if(strcmp("isp",Commands)==0)				{		ResetMpuIntoISP();								return 1;		}		
	else if(strcmp("sw",		Commands)==0)			{		PrintSoftVersionFromEEPROM();			return 1;		}
	else if(strcmp("hw",		Commands)==0)			{		PrintHardVersionFromEEPROM();			return 1;		}
	else if(strcmp("fsn",		Commands)==0)			{		PrintFSNFromEEPROM();							return 1;		}
	
	else if(strcmp("io test",		Commands)==0)			{		IoTestFlag=1;							return 1;		}
	else if(strcmp("start test",		Commands)==0)			{		BoardTestFlag=1;							return 1;		}
	else if(strcmp("stop test",		Commands)==0)			{		BoardTestFlag=0;							return 1;		}

	
	else if(strncmp("sw[",	Commands,3)==0)	
	{		
		char *p = NULL;
		char *s = &Commands[3];			
		u8 sw=(u8)strtol(s, &p, 10);	
		if(*p==']'&& *(p+1)=='\0')									
		{		
			WriteSWToEEPROM(sw);								
			return 1;		
		}
		else return 0;	
	}
	else if(strncmp("hw[",	Commands,3)==0)	
	{		
		char *p = NULL;
		char *s = &Commands[3];			
		u8 hw=(u8 )strtol(s, &p, 10);	
		if(*p==']'&& *(p+1)=='\0')									
		{		WriteHWToEEPROM(hw);								return 1;		}
		else return 0;	
	}	
	else if(strncmp("fsn[",	Commands,4)==0)	
	{	
		u8 i;
		for(i=0;i<11;i++)
		{
			if(Commands[i+4]==']') {Commands[i+4]='\0';	break ;}
		}
		if(	i>0	&& i<11	&& Commands[i+4]=='\0'&& Commands[i+5]=='\0')			
		{		WriteFSNToEEPROM((u8*)&Commands[4]);		return 1;		}
		else return 0;	
	}	
	else	if(Cmd_RomPage(Commands)==1)							return 1;		
	else if(strcmp("set 5v",		Commands)==0)			
	{		
		OUT_5V_1=0;	OUT_5V_2=0;	OUT_5V_3=0;
		UART_SendStr("SET 5V<OK>\n");return 1;
	}
	else if(strcmp("set 0v",		Commands)==0)			
	{		
		OUT_5V_1=1;	OUT_5V_2=1;	OUT_5V_3=1;
		UART_SendStr("SET 0V<OK>\n");return 1;
	}
	else
	{
		return 0;
	}
}
//帮助提示
static void PrintCommandlist(void)
{
  UART_SendStr("Send--------Receive----------meaning\n"); 
	UART_SendStr("sw----------SW<1.00>---------Get software version\n");
	UART_SendStr("hw----------HW<2.00>---------Get hardware version\n");
	UART_SendStr("fsn---------FSN<IN3-SMC>-----Get fixture serial number\n");	
	UART_SendStr("SW[]--------SW[110]<OK>------Set software version\n");
	UART_SendStr("HW[]--------HW[200]<OK>------Set hardware version\n");
	UART_SendStr("FSN[]-------FSN[SSS-1]<OK>---Set fixture serial number\n");
//	UART_SendStr("reset------------------------reset fixture\n");
//	UART_SendStr("isp--------------------------reset ISP\n");
	UART_SendStr("ROM[]------------------------Read Datas\n");
	UART_SendStr("ROM[][]----------------------Write Datas\n");
	UART_SendStr("SAVE INFO XX YYYYY\n");
	UART_SendStr("READ INFO XX\n");

	UART_SendStr("*************************************************\n");
	UART_SendStr("INT[]------INT[1]<0>---------Get the input status\n");
	UART_SendStr("OUT[][]----OUT[1][1]<OK>-----Set the output status\n");
	UART_SendStr("SET 5V-----SET 5V<OK>-----Set the port to 5v\n");
	UART_SendStr("SET 0V-----SET 0V<OK>-----Set the port to 0v\n");

	UART_SendStr("Please send command as above end with \\r\\n\n");
}
//
static u8  Cmd_RomPage(char *Commands)
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
			UART_Printf("save info %d OK\n",PageNum); 
			return 1;
		}	
	  UART_Printf("<NA>\n");return 1;
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
			UART_Printf("read info %d %.64s\n",PageNum,DataRead);
			return 1;
		}	
	  UART_Printf("<NA>\n");return 1;
	}
	else return 0;
}
//


