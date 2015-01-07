// FILE: 5��Э��۲���
// VERSION: 1.0  
// PURPOSE:�Զ����Ʋ���

#include "AutoCtrl.h" 
#include "GlobalCtrlParament.h"
#include <GlobalIOSet.h>
 

CAutoCtrl::CAutoCtrl()
{
}
CAutoCtrl::~CAutoCtrl()
{
	
	
}

//��������
int CAutoCtrl::PackageParse(uint8_t *recv, int length)
{
	

	//ȡЭ���
	if (recv[0] != CMD_AUTO_CTRL)
	{
		//Э��Ų���
		return 0;
	}
	//��ȡ���
	m_Layer = recv[1];
	CGlobalCtrlParament* g_globalArg = CSingleton<CGlobalCtrlParament>::instance();
	//��ȡ���õ��¶�״̬
	g_globalArg->m_Temperature = recv[2];
	//��ȡ���õ�ʪ��״̬
	g_globalArg->m_Humidity = recv[3];
	//��ȡ���õĹ���״̬
	g_globalArg->m_LightTime= recv[4];
	return 1;
}

//�����¼�
int CAutoCtrl::Processing()
{	
	return 1;
}

//��֯��Ӧ��
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

