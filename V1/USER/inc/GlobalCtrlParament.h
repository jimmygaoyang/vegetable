#ifndef GLOBALCTRLPAR_H  
#define GLOBALCTRLPAR_H 
 

#include "Singleton.h"
/////////////////Singleton应用实例
class CGlobalCtrlParament
{
    
	friend class CSingleton<CGlobalCtrlParament>; //作为友元可以访问CSingleton的保护成员
public:
	 unsigned char m_Temperature;//规定温度
	 unsigned char m_TemperRate;//温度波动范围
	 unsigned char m_Humidity;//规定湿度
	 unsigned char m_HumidityRate;//湿度波动范围
	 unsigned char m_LightTime;
	 unsigned short m_LightState;	//数字光传感器 两个字节长度
	 unsigned char m_DustHumidity;
	 unsigned char m_WorkMode;//工作模式
	 int m_OpenLightTime;//开灯时间
	 int m_CloseLightTime;//关灯时间

	
private:
    CGlobalCtrlParament(); //不允许直接实例化
};

#endif
