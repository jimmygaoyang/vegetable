// FILE: 3号协议观察者
// VERSION: 1.0  
// PURPOSE:控制喷雾的开和关 

  
#ifndef WATERCTRL_H  
#define WATERCTRL_H  
  

#include "ProtocolOberserver.h" 

class CWaterCtrl: public CProtocolOberserver  
{  
public:
	//协议包解析与处理
    int PackageParse(unsigned char *recv, int length);
	//协议事件处理
	int Processing();
	//组装返回数据包
	int ConstructRspPackage(unsigned char *send, int *length);

	CWaterCtrl();

	~CWaterCtrl();

public: 
	unsigned char m_Statue;//要设定的开关状态
	unsigned char m_Layer;

};  
#endif  
//  
// END OF FILE  
//  
