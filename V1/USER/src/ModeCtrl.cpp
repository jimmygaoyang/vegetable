// FILE: 号协议观察者
// VERSION: 1.0  
// PURPOSE:自动控制参数

#include "ModeCtrl.h" 
#include "GlobalCtrlParament.h"
#include <GlobalIOSet.h>
 

CModeCtrl::CModeCtrl()
{
}
CModeCtrl::~CModeCtrl()
{
	
	
}

//解析数据
int CModeCtrl::PackageParse(uint8_t *recv, int length)
{
	

	//取协议号
	if (recv[0] != CMD_MODE_CTRL)
	{
		//协议号不对
		return 0;
	}
	//获取层号
	m_Layer = recv[1];
	CGlobalCtrlParament* g_globalArg = CSingleton<CGlobalCtrlParament>::instance();
	//获取设置的手自动状态
	g_globalArg->m_WorkMode = recv[2];
	return 1;
}

//处理事件
int CModeCtrl::Processing()
{	
	return 1;
}

//组织响应包
int CModeCtrl::ConstructRspPackage(uint8_t *send, int *length)
{
	
	send[0] = CMD_MODE_CTRL;
	send[1] = m_Layer;
	send[2] = 1;
	*length = 3;
	return 1;
}


//  
// END OF FILE  
//  