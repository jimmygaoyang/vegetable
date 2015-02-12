// FILE: 1��Э��۲���
// VERSION: 1.0  
// PURPOSE:���ص�ǰ�¶ȡ�ʪ�ȡ��������� 

#include "CurrentStatue.h" 
#include "DHT.h"
#include "GlobalCtrlParament.h"
#include "GlobalIOSet.h"
#include "BH1750.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"

dht DHT;  

CCurrentStatue::CCurrentStatue()
{
}
CCurrentStatue::~CCurrentStatue()
{
	
	
}

//��������
int CCurrentStatue::PackageParse(uint8_t *recv, int length)
{
	
//	Serial.write(recv[0]);
//	Serial.write(recv[1]);
	//ȡЭ���
	if (recv[0] != CMD_CURRENT_STATUE)
	{
		//Э��Ų���
		return 0;
	}
	//��ȡ���
	m_Layer = recv[1];
	return 1;
}

//�����¼�
int CCurrentStatue::Processing()
{

	CGlobalIOSet* g_globalIOSet = CSingleton<CGlobalIOSet>::instance();
	int chk = DHT.read11(g_globalIOSet->m_IN_dht11);
	DBG_PRN(("chk=%d",chk))
	m_Light	= BH1750_Read();
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
	DBG_PRN(("�¶�=%d",m_Temperature))
	DBG_PRN(("ʪ��=%d",m_Humidity))
	
	CGlobalCtrlParament* g_globalArg = CSingleton<CGlobalCtrlParament>::instance();
 //     	m_Light = g_globalArg->m_LightState;
		g_globalArg->m_LightState = m_Light;
	   DBG_PRN(("����=%d lux",m_Light))
      	m_Statue = g_globalArg->m_WorkMode;	
      	m_DustHumidity = g_globalArg->m_DustHumidity;
      	
	return 1;
}

//��֯��Ӧ��
int CCurrentStatue::ConstructRspPackage(uint8_t *send, int *length)
{
	int i=0;
	 DBG_PRN(("����=%04x lux",m_Light))
	send[i++] = CMD_CURRENT_STATUE;
	send[i++] = m_Layer;
	send[i++] = m_Temperature;
	send[i++] = m_Humidity;
	send[i++] = m_Light>>8;
	send[i++] = m_Light;
	send[i++] = m_Statue;
	send[i++] = m_DustHumidity;

	*length = i;
	return 1;
}


//  
// END OF FILE  
// 

 