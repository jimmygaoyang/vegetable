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
#include "FileExecute.h"
#include <string.h>
#include <stdio.h>
#include "RS485Trans.h"


#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"

typedef enum {
    MACHINE_NUM,
	VEGFILE_LEN,
	INIT_OVER
   
}GLOBAL_INIT_STATUS;

char showInfo[64];
char tempBuf[32];
static char g_dataBuf[1024];

int WaitFor_Enter(unsigned int i)          //��ʱ����
{
	char recChar = 0;
	unsigned int recLen= 0;
	unsigned int i_delay,j_delay;
	for(i_delay=0;i_delay<i;i_delay++)
	{
		for(j_delay=0;j_delay<3000;j_delay++)
		{
			if(ser_can_read(UART3)> 0)
			{
				if(usart3_read(&recChar, 1) == 1)
				{
					if(recChar == 0x0d)
					{
						PUT(("find Enter KEY"))
						return 1;
					}	
				}
			}
		}
	 }
	return 0;
}
//ȫ�ֲ������ú���
void GolobalArgSetProcess()
{
	char tmpBuf[64];
	char recBuf[32];
	char recChar=0;
	int recLen = 0;
	unsigned int curVer = 0;
	unsigned int newVer = 0;
	unsigned int filelen = 0;
	unsigned int blockIndex = 0;
	
	unsigned int VegFileLen;
	GLOBAL_INIT_STATUS status = MACHINE_NUM ;
	memset(recBuf, 0,sizeof(recBuf));
	
	//���û������
	PUT("Enter the machine number...\r\n");


	while(1)
	{
		//�������ݹ���
		while(1)
		{
			if(usart3_read(&recChar, 1) == 1)
			{
				usart3_write(&recChar, 1);

				if(recChar != 0x08)  //������յ������˸�(ASCII��Ϊ0x08)
	   				recBuf[recLen++] = recChar;
			      else
			    		recLen = (recLen -1 >=0 ? recLen -1 : 0);
			      if(recChar == 0x0d)
			      {
					usart3_send_str("\r\n");
					recBuf[recLen-1]=0;
					recLen=0;
					break;
			      }
				
			}
		}

		switch(status)
		{
			case MACHINE_NUM:
				//�жϻ�����ų���
				if(strlen(recBuf) != 10)
				{
					//���û������
					PUT("machine munber must be 10 bytes!Please input again ...\r\n");
				}
				else
				{
					//���û������
					Flash_Write(MACHINE_NUM_ADRESS, (unsigned char*)recBuf, MACHINE_NUM_LEN);
					PUT("Enter the Vegetable file length...\r\n");
					status = VEGFILE_LEN;
				}
				break;
			case VEGFILE_LEN:
				//�жϳ�ʼ��״̬�Ϸ���
				sscanf(recBuf, "%u", &VegFileLen);		

				//���û������	
				Flash_Write(VEG_FILE_LEN, (unsigned char*)&VegFileLen, 4);
				status = INIT_OVER;
				//return;			

				break;

			default:
				break;
		}
		if(status == INIT_OVER)
		break;
		
	}

	
}




int main()
{

	CTransDataSubject transProtocol;
	RS485Trans RS485;
	usart1_open(9600);
	usart2_open(9600);
	usart3_open(115200);
	//I2C1_Init();
	
	Delay_Init(72);	
	CGlobalIOSet* g_IOset = CSingleton<CGlobalIOSet>::instance();
	CGlobalCtrlParament* g_globalArg = CSingleton<CGlobalCtrlParament>::instance();
	Delay_us(3);
	int initSetFlag = 0;
	PUT("press Entery key to stop system auto run ...\r\n")
	

	//�жϻس���ֹ
	for(int i=3; i>0; i--)
	{
		memset(showInfo, 0, sizeof(showInfo));
		sprintf(showInfo,"Delay %d s\r",i);
		PUT((showInfo))
		if (WaitFor_Enter(1000) == 1)	
		{
			initSetFlag = 1;
			break;
		}	
	}
	//���г�ʼ�����û�����ţ���ʼ����־
	if (initSetFlag == 1)
	{
		PUT("start set global arguments...\r\n")
		//��̬�洢�����ù���
		GolobalArgSetProcess();
	}

	
		
	//��ȡ�������
	memset(tempBuf, 0, sizeof(tempBuf));
	Flash_Read(MACHINE_NUM_ADRESS, (unsigned char*)tempBuf, MACHINE_NUM_LEN);
	memset(showInfo, 0, sizeof(showInfo));
	sprintf(showInfo,"�������%s\r\n", tempBuf);
	PUT(showInfo)
	RS485.Init(tempBuf);
	//��ȡ��ֲ�ļ�
	memset(tempBuf, 0, sizeof(tempBuf));
	int fileLen=0;
	Flash_Read(VEG_FILE_LEN, (unsigned char*)&fileLen, 4);
	DBG_PRN(("�����ļ���С%d",fileLen));
	Flash_Read(VEG_FILE, (unsigned char*)tempBuf, fileLen);
	DBG_PRN(("�ļ�����%s",tempBuf));
	FileExecute fe;
	//fe.ExecuteFile((char * )tempBuf);
	fe.ExecuteFile("01 080001 200500\r\n02 25 5\r\n03 22 2\r\n");
		
	usart1_send_str("ok");
   	BH1750_Init();
	char recbuf;
	RTC1302 rtc;
	char time[32];
	AutoExecute AutoExe;
	
	rtc.GetTime(time);
	DBG_PRN(("��ǰʱ��Ϊ%s",time))
	rtc.Rtc_init("2015-05-03 13:57:00");
	//���ͷ���ַ
	char sendAddr[10];
	int reclen;
	int sendLen;
	while(1){

		rtc.GetTime(time);
		DBG_PRN(("��ǰʱ��Ϊ%s",time))
		DBG_PRN(("��ǰ����Ϊ%u",rtc.GetDateInt()))
		DBG_PRN(("��ǰʱ��Ϊ%u",rtc.GetTimeInt()))

		if(RS485.Receive(sendAddr,g_dataBuf,reclen) == 1)
		{
			transProtocol.Get485Package(g_dataBuf,reclen);
			DBG_PRN(("���յ�����%s��485������",sendAddr))
			DBG_NPRINT_HEX(g_dataBuf,reclen)
			if(transProtocol.NotifyOberserver() == 1)
			{
				transProtocol.Rsp485Package(g_dataBuf,sendLen); 
				RS485.Send(sendAddr,g_dataBuf,sendLen);
				DBG_PRN(("����%s����485��",sendAddr))
				DBG_NPRINT_HEX(g_dataBuf,reclen)
			}	   
				
		}


		
		
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
