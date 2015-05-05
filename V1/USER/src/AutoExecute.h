#ifndef AUTO_EXECUTE_H
#define AUTO_EXECUTE_H
/***********************************************************************
 * Module:  AutoExecute.h
 * Author:  Thinkpad
 * Modified: 2015-04-30 22:38:45
 * Purpose: Implementation of the class AutoExecute
 * Comment: 自动控制实现部分
 ***********************************************************************/
 #include "GlobalCtrlParament.h"
#include "GlobalIOSet.h"
#include "rtc.h"

class AutoExecute
{
public:
	AutoExecute();
	~AutoExecute();
////////////////////////////////////////////////////////////////////////
// Name:       AirHumidityEx::run()
// Purpose:    Implementation of AirHumidityEx::run()
// Comment:    执行key和value的操作
// Parameters:
// Return:     int 1-成功 0-失败
////////////////////////////////////////////////////////////////////////
	int run();
private:
	RTC1302 rtc;
	CGlobalCtrlParament* g_globalArg;
	CGlobalIOSet* g_globalIOSet;
	
};

#endif
