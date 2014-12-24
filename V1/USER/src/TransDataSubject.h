// FILE: 通信数据流主题类
// VERSION: 1.0  
// PURPOSE:获取串口数据包、注册协议功能观察者、 通知观察者处理数据 

  
#ifndef TANSDATASUBJECT_H  
#define TANSDATASUBJECT_H  
  

#include "ProtocolOberserver.h"

#define MAX_OBERSERVER_NUM 10
#define NODATA_MAXTIME 1000 //串口无数据最大超时尝试次数
  
class CTransDataSubject  
{  
public:
	//获取传输来 协议包
    int GetTransPackage();
	//发送观察者处理的返回协议包
    int RspTransPackage();
	//注册观察者
    int RegisterObserver(CProtocolOberserver *pOber);
	//通知观察者处理事件
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
	//当前观察者数目
	int m_curOberserverNum;
	CProtocolOberserver * m_pOberserverHandler;
};  
#endif  
//  
// END OF FILE  
//  
