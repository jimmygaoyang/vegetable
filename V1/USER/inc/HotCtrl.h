// FILE: 4��Э��۲���
// VERSION: 1.0  
// PURPOSE:���Ƽ��ȵĿ��͹� 

  
#ifndef HOTCTRL_H  
#define HOTCTRL_H  
  

#include "ProtocolOberserver.h" 

class CHotCtrl: public CProtocolOberserver  
{  
public:
	//Э��������봦��
    int PackageParse(unsigned char *recv, int length);
	//Э���¼�����
	int Processing();
	//��װ�������ݰ�
	int ConstructRspPackage(unsigned char *send, int *length);

	CHotCtrl();

	~CHotCtrl();

public: 
	unsigned char m_Statue;//Ҫ�趨�Ŀ���״̬
	unsigned char m_Layer;

};  
#endif  
//  
// END OF FILE  
//  
