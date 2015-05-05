#include "AutoExecute.h"
#include "DHT.h"

int AutoExecute::run()
{	

	//light 开灯时间
	int curTime = rtc.GetTimeInt();
	if (curTime >= g_globalArg->m_OpenLightTime  && curTime <= g_globalArg->m_CloseLightTime)
	{
		g_globalIOSet->m_OUT_Light->SetDigitalOut(HIGH);
	}
	else
	{
		g_globalIOSet->m_OUT_Light->SetDigitalOut(LOW);
	}
	dht DHT;
	int chk = DHT.read11(g_globalIOSet->m_IN_dht11); 
	int Temperature = DHT.temperature;
	int Humidity = DHT.humidity;
	if (Temperature >= g_globalArg->m_Temperature + g_globalArg->m_TemperRate)
	{
		g_globalIOSet->m_OUT_Wind->SetDigitalOut(HIGH);
	}
	else
	{
		g_globalIOSet->m_OUT_Wind->SetDigitalOut(LOW);
	}

	if (Humidity <= g_globalArg->m_Humidity-g_globalArg->m_HumidityRate)
	{
		g_globalIOSet->m_OUT_Water->SetDigitalOut(HIGH);
	}
	else
		g_globalIOSet->m_OUT_Water->SetDigitalOut(LOW);

	return 1;

}

AutoExecute::AutoExecute()
{
	g_globalArg = CSingleton<CGlobalCtrlParament>::instance();
	g_globalIOSet = CSingleton<CGlobalIOSet>::instance();
}

