#include "stm32f10x.h" 
#include "usart.h" 
#include "delayFun.h"
#include "GlobalIOSet.h"
#include "GlobalCtrlParament.h"
#include "TransDataSubject.h"
#include "I2C1.h"
#include "BH1750.h"



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
	while(1){

		if(transProtocol.GetTransPackage() == 1)
		{ 
			DBG_PRN(("%s","接收到完整包"))
			if(transProtocol.NotifyOberserver() == 1)
			{
				transProtocol.RspTransPackage(); 
				DBG_PRN(("返回包正常"))
			}	   
		}


	 }
}
