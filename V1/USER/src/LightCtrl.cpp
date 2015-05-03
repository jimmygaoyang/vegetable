// FILE: 5��Э��۲���
// VERSION: 1.0  
// PURPOSE:���ù��յ�״̬

#include "LightCtrl.h" 
#include "GlobalCtrlParament.h"
#include <GlobalIOSet.h>
 

CLightCtrl::CLightCtrl()
{
}
CLightCtrl::~CLightCtrl()
{
	
	
}

//��������
int CLightCtrl::PackageParse(uint8_t *recv, int length)
{
	

	//ȡЭ���
	if (recv[0] != CMD_LIGHT_CTRL)
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
int CLightCtrl::Processing()
{

	CGlobalIOSet* g_globalIOSet = CSingleton<CGlobalIOSet>::instance();
  	if(m_Statue == 1)
		g_globalIOSet->m_OUT_Light->SetDigitalOut(HIGH);
	else
		g_globalIOSet->m_OUT_Light->SetDigitalOut(LOW);

	return 1;
}

//��֯��Ӧ��
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