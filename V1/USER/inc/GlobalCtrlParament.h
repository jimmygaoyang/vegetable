#ifndef GLOBALCTRLPAR_H  
#define GLOBALCTRLPAR_H 
 

#include "Singleton.h"
/////////////////SingletonӦ��ʵ��
class CGlobalCtrlParament
{
    
	friend class CSingleton<CGlobalCtrlParament>; //��Ϊ��Ԫ���Է���CSingleton�ı�����Ա
public:
	 unsigned char m_Temperature;
	 unsigned char m_Humidity;
	 unsigned char m_LightTime;
	 unsigned char m_LightState;
	 unsigned char m_DustHumidity;
	 unsigned char m_WorkMode;//����ģʽ
	
private:
    CGlobalCtrlParament(); //������ֱ��ʵ����
};

#endif
