#include "stm32f10x.h" 
#include "usart.h" 
#include "delayFun.h"
#include "GlobalIOSet.h"
#include "GlobalCtrlParament.h"
#include "TransDataSubject.h"
#include "I2C1.h"
#include "BH1750.h"
#include "rtc.h"
#include "AutoExecute.h"
#include "dataFlash.h"
#include <string.h>
#include <stdio.h>


#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"









char showInfo[64];
char tempBuf[32];



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
		
	//读取机器编号
	memset(tempBuf, 0, sizeof(tempBuf));
	Flash_Read(MACHINE_NUM_ADRESS, (unsigned char*)tempBuf, MACHINE_NUM_LEN);
	memset(showInfo, 0, sizeof(showInfo));
	sprintf(showInfo,"机器编号%02X %02X %02X %02X\r\n", tempBuf[0] ,tempBuf[1], tempBuf[2], tempBuf[3]);
	PUT(showInfo)
	//读取种植文件
/*	memset(tempBuf, 0, sizeof(tempBuf));
	int fileLen=0;
	Flash_Read(VEG_FILE_LEN, (unsigned char*)&fileLen, 4);
	DBG_PRN(("读出文件大小%d",fileLen));
	Flash_Read(VEG_FILE, tempBuf, fileLen);
	DBG_PRN(("文件内容%s",tempBuf));
	FileExecute fe;
	fe.ExecuteFile((char * )tempBuf);*/
		
	usart1_send_str("ok");
   	BH1750_Init();
	char recbuf;
	RTC1302 rtc;
	char time[32];
	AutoExecute AutoExe;
	
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
		AutoExe.run();
	

	 }
}
