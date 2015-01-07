// FILE: 协议观察者基类类
// VERSION: 1.0  
// PURPOSE:解析协议数据包、执行事件处理 组装响应数据包 

  
#ifndef PROTOCOLOBERSERVER_H  
#define PROTOCOLOBERSERVER_H  
  

//#include "TransDataSubject.h"

#define CMD_CURRENT_STATUE 1   //1号协议 获取当前状态
#define CMD_AUTO_CTRL 2        //2号协议 获取当前状态
#define CMD_WATER_CTRL 3       //3号协议 设置喷雾装置打开与关闭
#define CMD_HOT_CTRL 4         //4号协议 设置加热装置打开与关闭
#define CMD_LIGHT_CTRL 5       //5号协议 设置灯光装置打开与关闭
#define CMD_MODE_CTRL 6        //6号协议 设置手动与自动模式
#define CMD_WIND_CTRL 7        //7号协议 设置风扇装置打开与关闭


  
class CProtocolOberserver  
{  
public:
	//协议包解析与处理
    virtual int PackageParse(unsigned char *recv, int length) = 0;
	//协议事件处理
	virtual int Processing()= 0;
	//组装返回数据包
	virtual int ConstructRspPackage(unsigned char *send, int *length) = 0;

	CProtocolOberserver();

	~CProtocolOberserver();
 

};  
#endif  
//  
// END OF FILE  
//  
