// FILE: ��Э��۲���
// VERSION: 1.0  
// PURPOSE:�Զ����Ʋ���

#include "ModeCtrl.h" 
#include "GlobalCtrlParament.h"
#include <GlobalIOSet.h>
 

CModeCtrl::CModeCtrl()
{
}
CModeCtrl::~CModeCtrl()
{
	
	
}

//��������
int CModeCtrl::PackageParse(uint8_t *recv, int length)
{
	

	//ȡЭ���
	if (recv[0] != CMD_MODE_CTRL)
	{
		//Э��Ų���
		return 0;
	}
	//��ȡ���
	m_Layer = recv[1];
	CGlobalCtrlParament* g_globalArg = CSingleton<CGlobalCtrlParament>::instance();
	//��ȡ���õ����Զ�״̬
	g_globalArg->m_WorkMode = recv[2];
	return 1;
}

//�����¼�
int CModeCtrl::Processing()
{	
	return 1;
}

//��֯��Ӧ��
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