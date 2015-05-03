// FILE: 5号协议观察者
// VERSION: 1.0  
// PURPOSE:设置光照的状态

#include "LightCtrl.h" 
#include "GlobalCtrlParament.h"
#include <GlobalIOSet.h>
 

CLightCtrl::CLightCtrl()
{
}
CLightCtrl::~CLightCtrl()
{
	
	
}

//解析数据
int CLightCtrl::PackageParse(uint8_t *recv, int length)
{
	

	//取协议号
	if (recv[0] != CMD_LIGHT_CTRL)
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
int CLightCtrl::Processing()
{

	CGlobalIOSet* g_globalIOSet = CSingleton<CGlobalIOSet>::instance();
  	if(m_Statue == 1)
		g_globalIOSet->m_OUT_Light->SetDigitalOut(HIGH);
	else
		g_globalIOSet->m_OUT_Light->SetDigitalOut(LOW);

	return 1;
}

//组织响应包
int CLightCtrl::ConstructRspPackage(uint8_t *send, int *length)
{
	
	send[0] = CMD_LIGHT_CTRL;
	send[1] = m_Layer;
	send[2] = 1;
	*length = 3;
	return 1;
}


//  
// END OF FILE  
//  