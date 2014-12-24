#include "GlobalIOSet.h"


CGlobalIOSet::CGlobalIOSet()
{
	m_IN_dht11 = 2;         //put the sensor in the digital pin 2
	m_OUT_Hot = 3;		//set the hot run or close
	m_OUT_Water = 4;	//set the pump run or close
	m_OUT_Wind = 5;		//set the Wind module run or close     
	m_OUT_Light= 6;		//set the Light module run or close 
	m_IN_LightAnalog = 0;	//read the input from the light sensor analog input
	m_In_DustAnalog = 1;	//read the input from the dust humidity analog input
}


