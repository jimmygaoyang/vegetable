// FILE: 5��Э��۲���
// VERSION: 1.0  
// PURPOSE:���ƹ��յĿ��͹� 

  
#ifndef LIGHTCTRL_H  
#define LIGHTCTRL_H  
  

#include "ProtocolOberserver.h" 

class CLightCtrl: public CProtocolOberserver  
{  
public:
	//Э��������봦��
    int PackageParse(unsigned char *recv, int length);
	//Э���¼�����
	int Processing();
	//��װ�������ݰ�
	int ConstructRspPackage(unsigned char *send, int *length);

	CLightCtrl();

	~CLightCtrl();

public: 
	unsigned char m_Statue;//Ҫ�趨�Ŀ���״̬
	unsigned char m_Layer;

};  
#endif  
//  
// END OF FILE  
//  
