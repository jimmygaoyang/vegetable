// FILE: 6号协议观察者
// VERSION: 1.0  
// PURPOSE:控制风扇的开和关 

  
#ifndef WINDCTRL_H  
#define WINDCTRL_H  
  

#include "ProtocolOberserver.h" 

class CWindCtrl: public CProtocolOberserver  
{  
public:
	//协议包解析与处理
    int PackageParse(unsigned char *recv, int length);
	//协议事件处理
	int Processing();
	//组装返回数据包
	int ConstructRspPackage(unsigned char *send, int *length);

	CWindCtrl();

	~CWindCtrl();

public: 
	unsigned char m_Statue;//要设定的开关状态
	unsigned char m_Layer;

};  
#endif  
//  
// END OF FILE  
//  
