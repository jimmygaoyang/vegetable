// FILE: 7号协议观察者
// VERSION: 1.0  
// PURPOSE:设置风扇的状态

#include "WindCtrl.h" 
#include "GlobalCtrlParament.h"
#include <GlobalIOSet.h>
 

CWindCtrl::CWindCtrl()
{
}
CWindCtrl::~CWindCtrl()
{
	
	
}

//解析数据
int CWindCtrl::PackageParse(uint8_t *recv, int length)
{
	

	//取协议号
	if (recv[0] != CMD_WIND_CTRL)
	{
		//协议号不对
		return 0;
	}
	//获取层号
	m_Layer = recv[1];
	//获取设置的状态
	m_Statue = recv[2];
	return 1;
}

//处理事件
int CWindCtrl::Processing()
{

	CGlobalIOSet* g_globalIOSet = CSingleton<CGlobalIOSet>::instance();
  	if(m_Statue == 1)
		digitalWrite(g_globalIOSet->m_OUT_Wind, HIGH);
	else
		digitalWrite(g_globalIOSet->m_OUT_Wind, LOW);

//	CGlobalCtrlParament* g_globalArg = CSingleton<CGlobalCtrlParament>::instance();
	
	return 1;
}

//组织响应包
int CWindCtrl::ConstructRspPackage(uint8_t *send, int *length)
{
	
	send[0] = CMD_WIND_CTRL;
	send[1] = m_Layer;
	send[2] = 1;
	*length = 3;
	return 1;
}


//  
// END OF FILE  
//  