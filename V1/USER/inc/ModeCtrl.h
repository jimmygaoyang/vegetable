// FILE: 6��Э��۲���
// VERSION: 1.0  
// PURPOSE:�����ֶ����Զ�ģʽ 

  
#ifndef MODECTRL_H  
#define MODECTRL_H  
   

#include "ProtocolOberserver.h" 

class CModeCtrl: public CProtocolOberserver  
{  
public:
	//Э��������봦��
    int PackageParse(unsigned char *recv, int length);
	//Э���¼�����
	int Processing();
	//��װ�������ݰ�
	int ConstructRspPackage(unsigned char *send, int *length);

	CModeCtrl();

	~CModeCtrl();

public: 
	unsigned char m_Layer;

};  
#endif  
//  
// END OF FILE  
//  
