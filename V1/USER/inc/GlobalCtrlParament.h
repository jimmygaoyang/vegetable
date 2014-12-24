#ifndef GLOBALCTRLPAR_H  
#define GLOBALCTRLPAR_H 
 

#include "Singleton.h"
/////////////////Singleton应用实例
class CGlobalCtrlParament
{
    
	friend class CSingleton<CGlobalCtrlParament>; //作为友元可以访问CSingleton的保护成员
public:
	 unsigned char m_Temperature;
	 unsigned char m_Humidity;
	 unsigned char m_LightTime;
	 unsigned char m_LightState;
	 unsigned char m_DustHumidity;
	 unsigned char m_WorkMode;//工作模式
	
private:
    CGlobalCtrlParament(); //不允许直接实例化
};

#endif
