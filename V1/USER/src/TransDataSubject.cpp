// FILE: 通信数据流主题类
// VERSION: 1.0  
// PURPOSE:获取串口数据包、注册协议功能观察者、 通知观察者处理数据 

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
	//逐个注册观察者
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

//注册观察者
int CTransDataSubject::RegisterObserver(CProtocolOberserver *pOber)
{
	if (m_curOberserverNum >= MAX_OBERSERVER_NUM)
	{
		//超过最大观察者数量
		return 0;
	}
	//注册
	m_pOberverBuff[m_curOberserverNum] = pOber;
	//数量加1
	m_curOberserverNum++;
	return 1;
}

//收到来包后通知观察者们处理事件
int CTransDataSubject::NotifyOberserver()
{
	DBG_NPRINT_HEX(m_recvBuff,m_recvPos)
	for (int i = 0; i < m_curOberserverNum; i++)
	{
		//解析
		if (m_pOberverBuff[i]->PackageParse(m_recvBuff, m_recvPos) == 1)
		{

		    //处理
		    if (m_pOberverBuff[i]->Processing() == 1)
		   {
			//组织返回包
			if (m_pOberverBuff[i]->ConstructRspPackage(m_sendBuff, &m_fillPos) == 1)
		       {
				return 1;
		        }
		    }

		}
	}
	return 0;		
}

//获取传输来 协议包
int CTransDataSubject::GetTransPackage()
{
	int overtime = 0;
	int packageLen = 0; //包长度
	int tmpLen;
	m_recvPos = 0;
//	usart1_send_str("Enter get package\n");
	while (overtime < NODATA_MAXTIME)
	{
		if (ser_can_read(UART1)> 0)
		{
			//有数据总长度
			usart1_read((char*)&packageLen, 1);
			DBG_PRN(("%s","get packge"))
			
			if (packageLen > 0)
			{
				while(m_recvPos < packageLen)
				{
					tmpLen =  usart1_read((char*)(m_recvBuff+m_recvPos), packageLen-m_recvPos);
//					tmpLen = Serial.readBytes((char*)&(m_recvBuff[m_recvPos]),packageLen-m_recvPos);
					m_recvPos += tmpLen;
					if (tmpLen ==0)//超时过多接收不到包就跳出
					{
						overtime++;
						Delay_ms(3);
						if (overtime < NODATA_MAXTIME)
						{
							return -1;
						}
					}
				}
				//成功接收完一包数据
				return 1;
			}
		}
		overtime++;
		Delay_ms(3);
	}


	return -1;//无数据包超时
}

//发送观察者处理的返回协议包
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