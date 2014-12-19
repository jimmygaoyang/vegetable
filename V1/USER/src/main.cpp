#include "stm32f10x.h" 
#include "usart.h" 
#include "delayFun.h"


#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"




int main()
{

	char cmd;
	usart1_open(115200);
	usart3_open(115200);
	
	PUT("press Entery key to stop system auto run ...\r\n")
	while(1){
//		   if(ser_can_read(UART1) > 0)
//		   
//		   {
//				usart1_read(&cmd, 1);
//				usart1_send_byte(cmd);
//		   }


		   if(usart1_read(&cmd, 1) == 1)		   
		   {
//				delay_us(1);
				usart1_send_byte(cmd);
		   }

	 }
}
