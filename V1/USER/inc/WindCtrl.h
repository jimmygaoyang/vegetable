// FILE: 6��Э��۲���
// VERSION: 1.0  
// PURPOSE:���Ʒ��ȵĿ��͹� 

  
#ifndef WINDCTRL_H  
#define WINDCTRL_H  
  

#include "ProtocolOberserver.h" 

class CWindCtrl: public CProtocolOberserver  
{  
public:
	//Э��������봦��
    int PackageParse(unsigned char *recv, int length);
	//Э���¼�����
	int Processing();
	//��װ�������ݰ�
	int ConstructRspPackage(unsigned char *send, int *length);

	CWindCtrl();

	~CWindCtrl();

public: 
	unsigned char m_Statue;//Ҫ�趨�Ŀ���״̬
	unsigned char m_Layer;

};  
#endif  
//  
// END OF FILE  
//  
