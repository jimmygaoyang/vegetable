// FILE: 2��Э��۲���
// VERSION: 1.0  
// PURPOSE:�����Զ����Ƶ��¶�ʪ�Ⱥ͹���ʱ�� 

  
#ifndef AUTOCTRL_H  
#define AUTOCTRL_H  

#include "ProtocolOberserver.h" 

class CAutoCtrl: public CProtocolOberserver  
{  
public:
	//Э��������봦��
    int PackageParse(unsigned char *recv, int length);
	//Э���¼�����
	int Processing();
	//��װ�������ݰ�
	int ConstructRspPackage(unsigned char *send, int *length);

	CAutoCtrl();

	~CAutoCtrl();

public: 
	unsigned char m_Layer;

};  
#endif  
//  
// END OF FILE  
//  
