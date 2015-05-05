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
		
	//��ȡ�������
	memset(tempBuf, 0, sizeof(tempBuf));
	Flash_Read(MACHINE_NUM_ADRESS, (unsigned char*)tempBuf, MACHINE_NUM_LEN);
	memset(showInfo, 0, sizeof(showInfo));
	sprintf(showInfo,"�������%02X %02X %02X %02X\r\n", tempBuf[0] ,tempBuf[1], tempBuf[2], tempBuf[3]);
	PUT(showInfo)
	//��ȡ��ֲ�ļ�
/*	memset(tempBuf, 0, sizeof(tempBuf));
	int fileLen=0;
	Flash_Read(VEG_FILE_LEN, (unsigned char*)&fileLen, 4);
	DBG_PRN(("�����ļ���С%d",fileLen));
	Flash_Read(VEG_FILE, tempBuf, fileLen);
	DBG_PRN(("�ļ�����%s",tempBuf));
	FileExecute fe;
	fe.ExecuteFile((char * )tempBuf);*/
		
	usart1_send_str("ok");
   	BH1750_Init();
	char recbuf;
	RTC1302 rtc;
	char time[32];
	AutoExecute AutoExe;
	
	rtc.GetTime(time);
	DBG_PRN(("��ǰʱ��Ϊ%s",time))
	rtc.Rtc_init("2015-05-03 13:57:00");
	while(1){

		rtc.GetTime(time);
		DBG_PRN(("��ǰʱ��Ϊ%s",time))
		DBG_PRN(("��ǰ����Ϊ%u",rtc.GetDateInt()))
		DBG_PRN(("��ǰʱ��Ϊ%u",rtc.GetTimeInt()))
		
		
		if(transProtocol.GetTransPackage() == 1)
		{ 
			DBG_PRN(("%s","���յ�������"))
			if(transProtocol.NotifyOberserver() == 1)
			{
				transProtocol.RspTransPackage(); 
				DBG_PRN(("���ذ�����"))
			}	   
		}

		//�Զ���������
		AutoExe.run();
	

	 }
}
