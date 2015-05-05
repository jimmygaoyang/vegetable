// FILE: 5号协议观察者
// VERSION: 1.0  
// PURPOSE:自动控制参数

#include "AutoCtrl.h" 
#include "GlobalCtrlParament.h"
#include <GlobalIOSet.h>
#include "dataFlash.h"
#include <string.h>
#include "FileExecute.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"
 

CAutoCtrl::CAutoCtrl()
{
}
CAutoCtrl::~CAutoCtrl()
{
	
	
}

//解析数据
int CAutoCtrl::PackageParse(uint8_t *recv, int length)
{
	

	//取协议号
	if (recv[0] != CMD_AUTO_CTRL)
	{
		//协议号不对
		return 0;
	}
	//获取层号
	m_Layer = recv[1];
	CGlobalCtrlParament* g_globalArg = CSingleton<CGlobalCtrlParament>::instance();
/*	//获取设置的温度状态
	g_globalArg->m_Temperature = recv[2];
	//获取设置的湿度状态
	g_globalArg->m_Humidity = recv[3];
	//获取设置的光照状态
	g_globalArg->m_LightTime= recv[4];*/
	int fileLen = 0;
	memcpy((char *)&fileLen,recv+2,4);
	DBG_PRN(("接收文件大小%d",fileLen))
	Flash_Write(VEG_FILE_LEN, recv+2, 4);
	Flash_Write(VEG_FILE, recv+6, fileLen);
	DBG_PRN(("文件内容%s",recv+6));

	
	return 1;
}

//处理事件
int CAutoCtrl::Processing()
{	
	//解析种植文件
	unsigned char tmpBuf[256];
	
	memset(tmpBuf, 0, sizeof(tmpBuf));
	int fileLen=0;
	Flash_Read(VEG_FILE_LEN, (unsigned char*)&fileLen, 4);
	DBG_PRN(("读出文件大小%d",fileLen));
	Flash_Read(VEG_FILE, tmpBuf, fileLen);
	DBG_PRN(("文件内容%s",tmpBuf));
	FileExecute fe;
	fe.ExecuteFile((char * )tmpBuf);
	return 1;
}

//组织响应包
int CAutoCtrl::ConstructRspPackage(uint8_t *send, int *length)
{
	
	send[0] = CMD_AUTO_CTRL;
	send[1] = m_Layer;
	send[2] = 1;
	*length = 3;
	return 1;
}


//  
// END OF FILE  
//  

