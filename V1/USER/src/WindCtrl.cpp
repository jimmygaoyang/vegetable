// FILE: 7��Э��۲���
// VERSION: 1.0  
// PURPOSE:���÷��ȵ�״̬

#include "WindCtrl.h" 
#include "GlobalCtrlParament.h"
#include <GlobalIOSet.h>
 

CWindCtrl::CWindCtrl()
{
}
CWindCtrl::~CWindCtrl()
{
	
	
}

//��������
int CWindCtrl::PackageParse(uint8_t *recv, int length)
{
	

	//ȡЭ���
	if (recv[0] != CMD_WIND_CTRL)
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

//��֯��Ӧ��
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