// FILE: ͨ��������������
// VERSION: 1.0  
// PURPOSE:��ȡ�������ݰ���ע��Э�鹦�ܹ۲��ߡ� ֪ͨ�۲��ߴ������� 

#include "TransDataSubject.h"  
#include "CurrentStatue.h"
#include "ModeCtrl.h" 
#include "AutoCtrl.h"
#include "WaterCtrl.h"
#include "HotCtrl.h"
#include "LightCtrl.h"
#include "WindCtrl.h"
#include "stm32f10x.h"
#include "usart.h"
#include "DelayFun.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"

#define TIMEOUT 10000  



CTransDataSubject::CTransDataSubject()
{
	m_recvPos = 0;
	m_fillPos = 0;
	
	for (int i = 0; i<MAX_OBERSERVER_NUM; i++)
		m_pOberverBuff[i] = NULL;

	m_curOberserverNum = 0;
	//���ע��۲���
	m_pOberserverHandler = new CCurrentStatue();
	RegisterObserver(m_pOberserverHandler);

	m_pOberserverHandler = new CAutoCtrl();
	RegisterObserver(m_pOberserverHandler);

	m_pOberserverHandler = new CWaterCtrl();
	RegisterObserver(m_pOberserverHandler);

	m_pOberserverHandler = new CHotCtrl();
	RegisterObserver(m_pOberserverHandler);

	m_pOberserverHandler = new CLightCtrl();
	RegisterObserver(m_pOberserverHandler);

	m_pOberserverHandler = new CModeCtrl();
	RegisterObserver(m_pOberserverHandler);
	
	m_pOberserverHandler = new CWindCtrl();
	RegisterObserver(m_pOberserverHandler);
}

CTransDataSubject::~CTransDataSubject()
{
	for (int i = 0; i<MAX_OBERSERVER_NUM; i++)
	{
		if(m_pOberverBuff[i] != NULL)
			delete m_pOberverBuff[i];

		m_pOberverBuff[i] = NULL;

	}
	
}

//ע��۲���
int CTransDataSubject::RegisterObserver(CProtocolOberserver *pOber)
{
	if (m_curOberserverNum >= MAX_OBERSERVER_NUM)
	{
		//�������۲�������
		return 0;
	}
	//ע��
	m_pOberverBuff[m_curOberserverNum] = pOber;
	//������1
	m_curOberserverNum++;
	return 1;
}

//�յ�������֪ͨ�۲����Ǵ����¼�
int CTransDataSubject::NotifyOberserver()
{
	for (int i = 0; i < m_curOberserverNum; i++)
	{
		//����
		if (m_pOberverBuff[i]->PackageParse(m_recvBuff, m_recvPos) == 1)
		{

		    //����
		    if (m_pOberverBuff[i]->Processing() == 1)
		   {
			//��֯���ذ�
			if (m_pOberverBuff[i]->ConstructRspPackage(m_sendBuff, &m_fillPos) == 1)
		       {
//				Serial.println("obserID");
//				Serial.println(i);
				return 1;
		        }
		    }

		}
	}
	return 0;		
}

//��ȡ������ Э���
int CTransDataSubject::GetTransPackage()
{
	int overtime = 0;
	int packageLen = 0; //������
	int tmpLen;
	m_recvPos = 0;
//	usart1_send_str("Enter get package\n");
	while (overtime < NODATA_MAXTIME)
	{
		if (ser_can_read(UART1)> 0)
		{
			//�������ܳ���
			usart1_read((char*)&packageLen, 1);
//			usart1_send_str("Enter get package\n")
//			DBG_PRN(("%s","get packge"))
			
			if (packageLen > 0)
			{
				while(m_recvPos < packageLen)
				{
					tmpLen =  usart1_read((char*)(m_recvBuff+m_recvPos), packageLen-m_recvPos);
//					tmpLen = Serial.readBytes((char*)&(m_recvBuff[m_recvPos]),packageLen-m_recvPos);
					m_recvPos += tmpLen;
					if (tmpLen ==0)//��ʱ������ղ�����������
					{
						overtime++;
						Delay_ms(3);
						if (overtime < NODATA_MAXTIME)
						{
							return -1;
						}
					}
				}
				//�ɹ�������һ������
				return 1;
			}
		}
		overtime++;
	}


	return -1;//�����ݰ���ʱ
}

//���͹۲��ߴ���ķ���Э���
int CTransDataSubject::RspTransPackage()
{
	if (m_fillPos > 0)
	{
		usart1_send_byte(m_fillPos);
		usart1_write((char*)m_sendBuff,m_fillPos);
//		Serial.write((byte)m_fillPos);
//		Serial.write(m_sendBuff,m_fillPos);
	}
	m_fillPos = 0;
	return 1;
}


//  
// END OF FILE  
//  