/**
  \file 		SysControl.h
  \author 	Xcping2016
  \version 	1.00

  \brief 	

  This file contains the definitions of the functions from the SysControl.c
  module.
*/
#ifndef __SYSCONTROL_H
#define	__SYSCONTROL_H

void SetUpMcu(void);
void CylinderCoolDown(void);
void CommandCheckAndExe(void);
void HandleTaskPerMS(unsigned short ms);
void HandleDebugTaskPerMS(void);

void ResetMpuIntoISP(void);
void ResetMcuToMain(void);

#endif
