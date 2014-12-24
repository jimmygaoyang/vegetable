// FILE: 6号协议观察者
// VERSION: 1.0  
// PURPOSE:设置手动和自动模式 

  
#ifndef MODECTRL_H  
#define MODECTRL_H  
   

#include "ProtocolOberserver.h" 

class CModeCtrl: public CProtocolOberserver  
{  
public:
	//协议包解析与处理
    int PackageParse(unsigned char *recv, int length);
	//协议事件处理
	int Processing();
	//组装返回数据包
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
