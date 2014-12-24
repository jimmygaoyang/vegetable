// FILE: Э��۲��߻�����
// VERSION: 1.0  
// PURPOSE:����Э�����ݰ���ִ���¼����� ��װ��Ӧ���ݰ� 

  
#ifndef PROTOCOLOBERSERVER_H  
#define PROTOCOLOBERSERVER_H  
  

//#include "TransDataSubject.h"

#define CMD_CURRENT_STATUE 1   //1��Э�� ��ȡ��ǰ״̬
#define CMD_AUTO_CTRL 2        //2��Э�� ��ȡ��ǰ״̬
#define CMD_WATER_CTRL 3       //3��Э�� ��������װ�ô���ر�
#define CMD_HOT_CTRL 4         //4��Э�� ���ü���װ�ô���ر�
#define CMD_LIGHT_CTRL 5       //5��Э�� ���õƹ�װ�ô���ر�
#define CMD_MODE_CTRL 6        //6��Э�� �����ֶ����Զ�ģʽ
#define CMD_WIND_CTRL 7        //7��Э�� ���÷���װ�ô���ر�


  
class CProtocolOberserver  
{  
public:
	//Э��������봦��
    virtual int PackageParse(unsigned char *recv, int length) = 0;
	//Э���¼�����
	virtual int Processing() = 0;
	//��װ�������ݰ�
	virtual int ConstructRspPackage(unsigned char *send, int *length) = 0;

	CProtocolOberserver();

	~CProtocolOberserver();
 

};  
#endif  
//  
// END OF FILE  
//  
