#ifndef GLOBALIOSET_H  
#define GLOBALIOSET_H 
 

#include "Singleton.h"
//Singleton应用实例
class CGlobalIOSet
{
    
	friend class CSingleton<CGlobalIOSet>; //作为友元可以访问CSingleton的保护成员
public:
	int m_IN_dht11;         //put the sensor in the digital pin 2
	int m_OUT_Wind;		//set the Wind module run or close   
	int m_OUT_Water;	//set the pump run or close
	int m_OUT_Hot;		//set the hot module run or close     
	int m_OUT_Light;		//set the Light module run or close 
	int m_IN_LightAnalog;	//read the input from the light sensor analog input
	int m_In_DustAnalog;	//read the input from the dust humidity analog input
	
private:
    CGlobalIOSet(); //不允许直接实例化
};

#endif
