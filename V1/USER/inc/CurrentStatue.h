// FILE: 1号协议观察者
// VERSION: 1.0  
// PURPOSE:返回当前温度、湿度、光照条件 

  
#ifndef CURRENTSTATUE_H  
#define CURRENTSTATUE_H  

#include "ProtocolOberserver.h" 

class CCurrentStatue : public CProtocolOberserver  
{  
public:
	//协议包解析与处理
    int PackageParse(unsigned char *recv, int length);
	//协议事件处理
	int Processing();
	//组装返回数据包
	int ConstructRspPackage(unsigned char *send, int *length);

	CCurrentStatue();

	~CCurrentStatue();

public: 
	unsigned char m_Temperature;
	unsigned char m_Humidity;
	unsigned char m_Light;
	unsigned char m_Statue;
	unsigned char m_DustHumidity;
	unsigned char m_Layer;

};  
#endif  
//  
// END OF FILE  
//  
