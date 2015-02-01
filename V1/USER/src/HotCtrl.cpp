// FILE: 4号协议观察者
// VERSION: 1.0  
// PURPOSE:设置加热的状态

#include "HotCtrl.h" 
#include "GlobalCtrlParament.h"
#include <GlobalIOSet.h>

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"
 

CHotCtrl::CHotCtrl()
{
}
CHotCtrl::~CHotCtrl()
{
	
	
}

//解析数据
int CHotCtrl::PackageParse(uint8_t *recv, int length)
{

	DBG_PRN(("协议号%d", recv[0]))
	//取协议号
	if (recv[0] != CMD_HOT_CTRL)
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
int CHotCtrl::Processing()
{

	CGlobalIOSet* g_globalIOSet = CSingleton<CGlobalIOSet>::instance();
  	if(m_Statue == 1)
		g_globalIOSet->m_OUT_Hot->SetDigitalOut(HIGH);
	else
		g_globalIOSet->m_OUT_Hot->SetDigitalOut(LOW);

//	CGlobalCtrlParament* g_globalArg = CSingleton<CGlobalCtrlParament>::instance();
	
	return 1;
}

//组织响应包
int CHotCtrl::ConstructRspPackage(uint8_t *send, int *length)
{
	
	send[0] = CMD_HOT_CTRL;
	send[1] = m_Layer;
	send[2] = 1;
	*length = 3;
	return 1;
}


//  
// END OF FILE  
//  