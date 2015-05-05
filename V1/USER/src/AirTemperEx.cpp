/***********************************************************************
 * Module:  AirTemperEx.cpp
 * Author:  Thinkpad
 * Modified: 2015-04-30 22:37:56
 * Purpose: Implementation of the class AirTemperEx
 * Comment: 空气温度解析
 ***********************************************************************/

#include "AirTemperEx.h"
#include "GlobalCtrlParament.h"
#include <string.h>
#include <stdlib.h>

////////////////////////////////////////////////////////////////////////
// Name:       AirTemperEx::excute(int key, std::string value)
// Purpose:    Implementation of AirTemperEx::excute()
// Comment:    执行key和value的操作
// Parameters:
// - key
// - value
// Return:     int
////////////////////////////////////////////////////////////////////////

int AirTemperEx::excute(int key, char* value)
{
   // TODO : implement
    char *tmp;
    char buf[32];
	tmp = strstr(value," ");
	memset(buf,0,sizeof(buf));
	memcpy(buf,value,tmp-value);
	CGlobalCtrlParament* g_globalArg = CSingleton<CGlobalCtrlParament>::instance();
	g_globalArg->m_Temperature = atoi(buf);
	value = tmp+1;
	g_globalArg->m_TemperRate = atoi(value);
}