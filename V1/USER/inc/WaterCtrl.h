// FILE: 3��Э��۲���
// VERSION: 1.0  
// PURPOSE:��������Ŀ��͹� 

  
#ifndef WATERCTRL_H  
#define WATERCTRL_H  
  

#include "ProtocolOberserver.h" 

class CWaterCtrl: public CProtocolOberserver  
{  
public:
	//Э��������봦��
    int PackageParse(unsigned char *recv, int length);
	//Э���¼�����
	int Processing();
	//��װ�������ݰ�
	int ConstructRspPackage(unsigned char *send, int *length);

	CWaterCtrl();

	~CWaterCtrl();

public: 
	unsigned char m_Statue;//Ҫ�趨�Ŀ���״̬
	unsigned char m_Layer;

};  
#endif  
//  
// END OF FILE  
//  
