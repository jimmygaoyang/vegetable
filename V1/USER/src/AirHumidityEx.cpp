/***********************************************************************
 * Module:  AirHumidityEx.cpp
 * Author:  Thinkpad
 * Modified: 2015-04-30 22:38:45
 * Purpose: Implementation of the class AirHumidityEx
 * Comment: 空气湿度控制
 ***********************************************************************/

#include "AirHumidityEx.h"
#include "GlobalCtrlParament.h"
#include <string.h>
#include <stdlib.h>

////////////////////////////////////////////////////////////////////////
// Name:       AirHumidityEx::excute(int key, std::string value)
// Purpose:    Implementation of AirHumidityEx::excute()
// Comment:    执行key和value的操作
// Parameters:
// - key
// - value
// Return:     int
////////////////////////////////////////////////////////////////////////

int AirHumidityEx::excute(int key, char* value)
{
   // TODO : implement
    char *tmp;
    char buf[32];
	tmp = strstr(value," ");
	memset(buf,0,sizeof(buf));
	memcpy(buf,value,tmp-value);
	CGlobalCtrlParament* g_globalArg = CSingleton<CGlobalCtrlParament>::instance();
	g_globalArg->m_Humidity = atoi(buf);
	value = tmp+1;
	g_globalArg->m_HumidityRate = atoi(value);
	return 1;
}