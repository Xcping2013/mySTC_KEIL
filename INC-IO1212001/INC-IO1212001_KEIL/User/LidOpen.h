/**
  \file 		X2B_QT1.h
  \author 	Xcping2016	2016-4-23
  \version 	1.00
  \brief 		Definitions and Select the parameters match with the board
*/

#ifndef __LIDOPEN_H
#define __LIDOPEN_H

#include "IO.h"

#if	(PROJECT==LIDOPEN)			//115200 22.1184

void SetCylinderPowerOn(void);
u8 	 LidOpen_Commands(u8 *ptr);
void ButtonProcess_START(void);

//void SetCylinderPowerOn(void);
//u8 X2B_QT1_Commands(u8 *str);

#endif


#endif