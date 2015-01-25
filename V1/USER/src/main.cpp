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

	CTransDataSubject transProtocol;
	usart1_open(9600);
	usart3_open(115200);
	Delay_Init(72);
	
	CGlobalIOSet* g_IOset = CSingleton<CGlobalIOSet>::instance();
	CGlobalCtrlParament* g_globalArg = CSingleton<CGlobalCtrlParament>::instance();
	Delay_us(3);
	PUT("press Entery key to stop system auto run ...\r\n")
	usart1_send_str("ok");

	char recbuf;
	while(1){

/*		if(ser_can_read(UART1)>0)
		{
			usart1_read(&recbuf,1);
			DBG_PRN(("%02x",recbuf))
			usart1_send_byte(recbuf);
			
		}
*/		
		if(transProtocol.GetTransPackage() == 1)
		{ 
//			usart1_send_str("Get package\n");
			if(transProtocol.NotifyOberserver() == 1)
			{
				transProtocol.RspTransPackage(); 
				DBG_PRN(("%02x",22))
			}	   
		}


	 }
}
