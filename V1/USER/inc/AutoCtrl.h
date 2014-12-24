// FILE: 2号协议观察者
// VERSION: 1.0  
// PURPOSE:设置自动控制的温度湿度和光照时间 

  
#ifndef AUTOCTRL_H  
#define AUTOCTRL_H  

#include "ProtocolOberserver.h" 

class CAutoCtrl: public CProtocolOberserver  
{  
public:
	//协议包解析与处理
    int PackageParse(unsigned char *recv, int length);
	//协议事件处理
	int Processing();
	//组装返回数据包
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
