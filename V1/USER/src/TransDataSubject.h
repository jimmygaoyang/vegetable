// FILE: ͨ��������������
// VERSION: 1.0  
// PURPOSE:��ȡ�������ݰ���ע��Э�鹦�ܹ۲��ߡ� ֪ͨ�۲��ߴ������� 

  
#ifndef TANSDATASUBJECT_H  
#define TANSDATASUBJECT_H  
  

#include "ProtocolOberserver.h"

#define MAX_OBERSERVER_NUM 10
#define NODATA_MAXTIME 100000 //�������������ʱ���Դ���
  
class CTransDataSubject  
{  
public:
	//��ȡ������ Э���
    int GetTransPackage();
	//���͹۲��ߴ���ķ���Э���
    int RspTransPackage();
	//ע��۲���
    int RegisterObserver(CProtocolOberserver *pOber);
	//֪ͨ�۲��ߴ����¼�
	int NotifyOberserver();

	
	CTransDataSubject();

	~CTransDataSubject();



public: 
	// buffer to receive data
    unsigned char m_recvBuff[256];
	// recvCount;
	int m_recvPos;
	// buffer to send data
	unsigned char m_sendBuff[256]; 
	//fillCount
	int m_fillPos;

private:
	CProtocolOberserver * m_pOberverBuff[MAX_OBERSERVER_NUM];
	//��ǰ�۲�����Ŀ
	int m_curOberserverNum;
	CProtocolOberserver * m_pOberserverHandler;
};  
#endif  
//  
// END OF FILE  
//  
