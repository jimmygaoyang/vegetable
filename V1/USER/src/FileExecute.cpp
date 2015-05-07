/***********************************************************************
 * Module:  FileExecute.cpp
 * Author:  Thinkpad
 * Modified: 2015-04-30 22:19:06
 * Purpose: Implementation of the class FileExecute
 * Comment: 文件执行类
 ***********************************************************************/

#include "Expression.h"
#include "FileExecute.h"
#include "AirHumidityEx.h"
#include "AirTemperEx.h"
#include "LightControlEx.h"
#include <stdlib.h>

////////////////////////////////////////////////////////////////////////
// Name:       FileExecute::ExecuteFile(std::string content)
// Purpose:    Implementation of FileExecute::ExecuteFile()
// Comment:    执行方案文件
// Parameters:
// - content
// Return:     int
////////////////////////////////////////////////////////////////////////

int FileExecute::ExecuteFile(char* content)
{
   // TODO : implement
	int res = 1; 
   pStar = content;
   pCurrent = content;
   length = strlen(content);
   char cmd[128];
   int cmdLen;
   
	while(GetNextCmd(cmd,cmdLen)!= 0)
	{
		if(ExecuteCmd(cmd,cmdLen)!= 1)
		{
			res = 0;
			break;
		}
	}
	return res;
}

int FileExecute::GetNextCmd(char *cmd, int &cmdLen)
{
	char *tmp;
	tmp = strstr(pCurrent,"\r\n");
	if(tmp !=NULL)
	{
		cmdLen = tmp - pCurrent;
		memset(cmd,0,cmdLen+1);
		memcpy((void*)cmd, pCurrent,tmp - pCurrent);
		pCurrent = tmp+2;
		return 1;
	}
	else
		return 0;
		
	
}

int FileExecute::ExecuteCmd(char *cmd, int cmdLen)
{
	char cmdNo[3];
	memset(cmdNo, 0,sizeof(cmdNo));
	memcpy(cmdNo,cmd,2);
	int CmdNum = atoi(cmdNo);
	switch(CmdNum)
	{
		case CONTRL_LIGHT_TIME:
			expression = new LightControlEx();
			break;
		case AIR_TEMPRATURE:
			expression = new AirTemperEx();
			break;
		case AIR_HUMIDITY:
			expression = new AirHumidityEx();
			break;
	}
	char *value = cmd+3;

	return expression->excute(CmdNum,value);
	
		
}











