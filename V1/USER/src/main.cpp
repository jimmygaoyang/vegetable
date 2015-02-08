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
	Delay_ms(200);
	x = BH1750_Read();
	DBG_PRN(("%04X",x))
//	I2C_GenerateSTART(I2C1, ENABLE);
	
//	I2C_Send7bitAddress(I2C1, 0x23<<1, 0);
//	I2C_GenerateSTOP(I2C1, ENABLE);

//		
		//DBG_PRN(("%04X",x))
//		Delay_ms(200);

/*		if(ser_can_read(UART1)>0)
		{
			usart1_read(&recbuf,1);
			DBG_PRN(("%02x",recbuf))
			usart1_send_byte(recbuf);
			
		}
*/		
/*		if(transProtocol.GetTransPackage() == 1)
		{ 
			DBG_PRN(("%s","接收到完整包"))
			if(transProtocol.NotifyOberserver() == 1)
			{
				transProtocol.RspTransPackage(); 
				DBG_PRN(("返回包正常"))
			}	   
		}
*/

	 }
}
