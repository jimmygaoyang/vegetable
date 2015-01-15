#include "stm32f10x.h" 
#include "usart.h" 
#include "delayFun.h"
#include "GlobalIOSet.h"
#include "GlobalCtrlParament.h"
#include "TransDataSubject.h"



#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"




int main()
{

	char cmd;
	CTransDataSubject transProtocol;
	usart1_open(115200);
	usart3_open(9600);
	
	CGlobalIOSet* g_IOset = CSingleton<CGlobalIOSet>::instance();
	CGlobalCtrlParament* g_globalArg = CSingleton<CGlobalCtrlParament>::instance();
	
	PUT("press Entery key to stop system auto run ...\r\n")



	while(1){
		
		if(transProtocol.GetTransPackage() == 1)
		{ 
			if(transProtocol.NotifyOberserver() == 1)
			{
				transProtocol.RspTransPackage(); 
				DBG_PRN(("%02x",22))
			}	   
		}


	 }
}
