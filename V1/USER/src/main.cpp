#include "stm32f10x.h" 
#include "usart.h" 
#include "delayFun.h"
#include "GlobalIOSet.h"
#include "GlobalCtrlParament.h"
#include "TransDataSubject.h"
#include "I2C1.h"
#include "BH1750.h"
#include "rtc.h"



#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"


unsigned short x=0;

int main()
{

	CTransDataSubject transProtocol;
	usart1_open(9600);
	usart3_open(115200);
	I2C1_Init();
	
	Delay_Init(72);	
	CGlobalIOSet* g_IOset = CSingleton<CGlobalIOSet>::instance();
	CGlobalCtrlParament* g_globalArg = CSingleton<CGlobalCtrlParament>::instance();
	Delay_us(3);
	PUT("press Entery key to stop system auto run ...\r\n")
	usart1_send_str("ok");
   	BH1750_Init();
	char recbuf;
	RTC1302 rtc;
	char time[32];
	
	rtc.GetTime(time);
	DBG_PRN(("当前时间为%s",time))
	rtc.Rtc_init("2015-05-03 13:57:00");
	while(1){

		rtc.GetTime(time);
		DBG_PRN(("当前时间为%s",time))
		DBG_PRN(("当前日期为%u",rtc.GetDateInt()))
		DBG_PRN(("当前时间为%u",rtc.GetTimeInt()))
		
		
		if(transProtocol.GetTransPackage() == 1)
		{ 
			DBG_PRN(("%s","接收到完整包"))
			if(transProtocol.NotifyOberserver() == 1)
			{
				transProtocol.RspTransPackage(); 
				DBG_PRN(("返回包正常"))
			}	   
		}

		//自动控制设置

	

	 }
}
