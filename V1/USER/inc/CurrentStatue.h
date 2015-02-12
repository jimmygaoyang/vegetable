// FILE: 1��Э��۲���
// VERSION: 1.0  
// PURPOSE:���ص�ǰ�¶ȡ�ʪ�ȡ��������� 

  
#ifndef CURRENTSTATUE_H  
#define CURRENTSTATUE_H  

#include "ProtocolOberserver.h" 

class CCurrentStatue : public CProtocolOberserver  
{  
public:
	//Э��������봦��
    int PackageParse(unsigned char *recv, int length);
	//Э���¼�����
	int Processing();
	//��װ�������ݰ�
	int ConstructRspPackage(unsigned char *send, int *length);

	CCurrentStatue();

	~CCurrentStatue();

public: 
	unsigned char m_Temperature;
	unsigned char m_Humidity;
	unsigned short m_Light;
	unsigned char m_Statue;
	unsigned char m_DustHumidity;
	unsigned char m_Layer;

};  
#endif  
//  
// END OF FILE  
//  
