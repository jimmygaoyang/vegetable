#include "CmdExecutor.h"
#include "usart.h"
#include "spi.h"
#include "DelayFun.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"




char CmdCheck(void){
	char recChar = 0;
	int retry  = 0;
	while(1)
	{
		if(usart3_read(&recChar, 1) == 1) {

			break;
		}
			
		else
		{
			if(retry++ > 10000)
				break;
		}
	}
	return recChar;
}
char Cmd1Executor(void)
{
	unsigned char recChar = 0;//返回数据
	unsigned char cmd = 0;
	//接收1个字节数据
	int retry  = 0;
	int tmp;
	do
	{
		tmp = 0;
		tmp = usart1_read(&cmd, 1);
//		delay_us(2);
		if(retry++ > 1000)
			return 0;

	}while(tmp < 1);
//	DBG_PRN(("接收数据 %02x",cmd))
	//发送并获取返回
	SetSpiDataLen(MODE_8_BITS_);
	SPI1Enable();
	recChar = SPI1WriteReadByte(cmd);
	SPI1Disable();
//	DBG_PRN(("rexChar = %02x",recChar))
//	delay_us(2000);
//  recChar = 0;
//	SPI1Enable();
//	recChar = SPI1WriteReadByte(cmd);
//	SPI1Disable();
	
//	DBG_PRN(("rexChar = %02x",recChar))

	//返回数据
	usart1_send_byte(recChar);
	return 1;
	
}
int Cmd2Executor(void)
{
	int recChar;//返回数据
	char buf[3];
	int cmd;
	
	//接收2个字节数据
	int retry  = 0;
	int len = 0;
	int tmp;
	do
	{
		tmp = 0;
		tmp = usart1_read(buf+len, 2-len);
		len+=tmp;
//		delay_us(2);

	}while(len < 2);
//	DBG_PRN(("接收数据 %02x",buf[0]))
//	DBG_PRN(("接收数据 %02x",buf[1]))
	cmd = buf[0]<<8+buf[1];
	
	//发送并获取返回
	SetSpiDataLen(MODE_16_BITS_);
	SPI1Enable();
	recChar = SPI1WriteRead2Byte(cmd);
	SPI1Disable();
//	delay_us(2000);
//   	recChar = 0;
//	SPI1Enable();
//	recChar = SPI1WriteRead2Byte(cmd);
//	SPI1Disable();
//	DBG_PRN(("rexChar = %04x",recChar))

	//返回数据
	usart1_send_byte((recChar&0xFF00)>>8);
	usart1_send_byte((recChar&0x00FF));
	return 1;

}
void ExecutorRun(void){
	char recChar = 0;
	int tmp = 0;
	do
	{
		tmp	= 0;
		tmp = usart1_read(&recChar, 1);
//		delay_us(2);

	}while(tmp < 1 );
//	DBG_PRN(("接收到命令rexChar = %02x",recChar))

	switch(recChar){
		case 0x01:
		{
			Cmd1Executor();
			break;	
		}
		case 0x02:
		{
			Cmd2Executor();
			break;
		}
		default:
			break;			
		}
		return ;
		
	}

