// FILE: 1号协议观察者
// VERSION: 1.0  
// PURPOSE:返回当前温度、湿度、光照条件 

#include "CurrentStatue.h" 
#include "DHT.h"
#include "GlobalCtrlParament.h"
#include "GlobalIOSet.h"

dht DHT;  

CCurrentStatue::CCurrentStatue()
{
}
CCurrentStatue::~CCurrentStatue()
{
	
	
}

//解析数据
int CCurrentStatue::PackageParse(uint8_t *recv, int length)
{
	
//	Serial.write(recv[0]);
//	Serial.write(recv[1]);
	//取协议号
	if (recv[0] != CMD_CURRENT_STATUE)
	{
		//协议号不对
		return 0;
	}
	//获取层号
	m_Layer = recv[1];
	return 1;
}

//处理事件
int CCurrentStatue::Processing()
{

	CGlobalIOSet* g_globalIOSet = CSingleton<CGlobalIOSet>::instance();
	int chk = DHT.read11(g_globalIOSet->m_IN_dht11);
//	int chk = DHT.read11(DHT11_PIN);  
	switch (chk)  
	{  
		case 0:  
//			Serial.print("OK,\t"); 
			break;  
		case -1: 
//			Serial.print("Checksum error,\t");
			break;  
		case -2: 
//			Serial.print("Time out error,\t\n"); 
			break;  
		default:
//			Serial.print("Unknown error,\t"); 
			break;  
	} 
	m_Temperature = DHT.temperature;
	m_Humidity = DHT.humidity;	
	CGlobalCtrlParament* g_globalArg = CSingleton<CGlobalCtrlParament>::instance();
      	m_Light = g_globalArg->m_LightState;
      	m_Statue = g_globalArg->m_WorkMode;	
      	m_DustHumidity = g_globalArg->m_DustHumidity;
      	
	return 1;
}

//组织响应包
int CCurrentStatue::ConstructRspPackage(uint8_t *send, int *length)
{
	
	send[0] = CMD_CURRENT_STATUE;
	send[1] = m_Layer;
	send[2] = m_Temperature;
	send[3] = m_Humidity;
	send[4] = m_Light;
	send[5] = m_Statue;
	send[6] = m_DustHumidity;


	*length = 7;
	return 1;
}


//  
// END OF FILE  
// 

 