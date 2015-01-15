// FILE: 3��Э��۲���
// VERSION: 1.0  
// PURPOSE:���������״̬

#include "WaterCtrl.h" 
#include "GlobalCtrlParament.h"
#include <GlobalIOSet.h>
 

CWaterCtrl::CWaterCtrl()
{
}
CWaterCtrl::~CWaterCtrl()
{
	
	
}

//��������
int CWaterCtrl::PackageParse(uint8_t *recv, int length)
{
	
//	Serial.write(recv[0]);
//	Serial.write(recv[1]);
	//ȡЭ���
	if (recv[0] != CMD_WATER_CTRL)
	{
		//Э��Ų���
		return 0;
	}
	//��ȡ���
	m_Layer = recv[1];
	//��ȡ���õ�״̬
	m_Statue = recv[2];
	return 1;
}

//�����¼�
int CWaterCtrl::Processing()
{

	CGlobalIOSet* g_globalIOSet = CSingleton<CGlobalIOSet>::instance();
  	if(m_Statue == 1)
		g_globalIOSet->m_OUT_Water->SetDigitalOut(HIGH);
	else
		g_globalIOSet->m_OUT_Water->SetDigitalOut(LOW);

//	CGlobalCtrlParament* g_globalArg = CSingleton<CGlobalCtrlParament>::instance();
	
	return 1;
}

//��֯��Ӧ��
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