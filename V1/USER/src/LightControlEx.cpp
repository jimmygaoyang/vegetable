/***********************************************************************
 * Module:  LightControlEx.cpp
 * Author:  Thinkpad
 * Modified: 2015-04-30 22:42:44
 * Purpose: Implementation of the class LightControlEx
 * Comment: 灯光开闭控制
 ***********************************************************************/

#include "LightControlEx.h"
#include "GlobalCtrlParament.h"
#include <string.h>
#include <stdlib.h>

////////////////////////////////////////////////////////////////////////
// Name:       LightControlEx::excute(int key, std::string value)
// Purpose:    Implementation of LightControlEx::excute()
// Comment:    执行key和value的操作
// Parameters:
// - key
// - value
// Return:     int
////////////////////////////////////////////////////////////////////////

int LightControlEx::excute(int key, char* value)
{
   // TODO : implement
	char *tmp;
  char buf[32];
	tmp = strstr(value," ");
	memset(buf,0,sizeof(buf));
	memcpy(buf,value,tmp-value);
	CGlobalCtrlParament* g_globalArg = CSingleton<CGlobalCtrlParament>::instance();
	g_globalArg->m_OpenLightTime = atoi(buf);
	value = tmp+1;
	g_globalArg->m_CloseLightTime = atoi(value);
	return 1;
}