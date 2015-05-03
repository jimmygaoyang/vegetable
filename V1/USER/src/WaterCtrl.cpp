// FILE: 3号协议观察者
// VERSION: 1.0  
// PURPOSE:设置喷雾的状态

#include "WaterCtrl.h" 
#include "GlobalCtrlParament.h"
#include <GlobalIOSet.h>
 

CWaterCtrl::CWaterCtrl()
{
}
CWaterCtrl::~CWaterCtrl()
{
	
	
}

//解析数据
int CWaterCtrl::PackageParse(uint8_t *recv, int length)
{
	
//	Serial.write(recv[0]);
//	Serial.write(recv[1]);
	//取协议号
	if (recv[0] != CMD_WATER_CTRL)
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
int CWaterCtrl::Processing()
{

	CGlobalIOSet* g_globalIOSet = CSingleton<CGlobalIOSet>::instance();
  	if(m_Statue == 1)
		g_globalIOSet->m_OUT_Water->SetDigitalOut(HIGH);
	else
		g_globalIOSet->m_OUT_Water->SetDigitalOut(LOW);

	
	return 1;
}

//组织响应包
int CWaterCtrl::ConstructRspPackage(uint8_t *send, int *length)
{
	
	send[0] = CMD_WATER_CTRL;
	send[1] = m_Layer;
	send[2] = 1;
	*length = 3;
	return 1;
}


//  
// END OF FILE  
//  