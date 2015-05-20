/***********************************************************************
 * Module:  RS485Operater.cpp
 * Author:  Thinkpad
 * Modified: 2015-04-29 14:40:23
 * Purpose: Implementation of the class RS485Operater
 * Comment: RS485������
 ***********************************************************************/

#include "RS485Trans.h"
#include <string.h>
#include "usart.h" 
#include "crc.h"
#include "DelayFun.h"
#include "GlobalIOSet.h"



#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"

////////////////////////////////////////////////////////////////////////
// Name:       RS485Operater::Send(int Addr, int buf, int len, int errStr)
// Purpose:    Implementation of RS485Operater::Send()
// Comment:    ��ָ����ַ��������
// Parameters:
// - Addr
// - buf
// - len
// - errStr
// Return:     int
////////////////////////////////////////////////////////////////////////

int RS485Trans::Send(char* Addr, char* buf, int len)
{
   // TODO : implement
   unsigned short crc=0;
   m_fillPos = 0;
   //��ͷ
   m_sendBuff[0] = 0x32;
   m_fillPos++;
   //�Է��ĵ�ַ
   memcpy(m_sendBuff+m_fillPos,Addr,MAC_NUM_LEN);
   m_fillPos += 10;
   //�Լ��ĵ�ַ
   memcpy(m_sendBuff+m_fillPos,m_addr,MAC_NUM_LEN);
   m_fillPos += 10;
   //��Ϣ���ݳ���
   memcpy(m_sendBuff + m_fillPos,(char *)&len,4);
   m_fillPos += 4;
   //��Ϣ����
   memcpy(m_sendBuff + m_fillPos,buf,len);
   m_fillPos += len;

   	//crcУ��
	crc = cal_crc(m_sendBuff, m_fillPos);
	DBG_PRN(("crc = %04x",crc))
	*(m_sendBuff + m_fillPos++) =  ((unsigned char*)&crc)[1];
	*(m_sendBuff + m_fillPos++) =  ((unsigned char*)&crc)[0];
	//����Ϊ���
	CGlobalIOSet* g_globalIOSet = CSingleton<CGlobalIOSet>::instance();
	g_globalIOSet->m_485Direct->SetDigitalOut(HIGH);

	usart2_write((char *)m_sendBuff,m_fillPos);
   
   
}

////////////////////////////////////////////////////////////////////////
// Name:       RS485Operater::Init(int Addr, std::string errStr)
// Purpose:    Implementation of RS485Operater::Init()
// Comment:    ��ʼ��
// Parameters:
// - Addr
// - errStr
// Return:     int
////////////////////////////////////////////////////////////////////////

int RS485Trans::Init(char* Addr)
{
	
   // TODO : implement
	memcpy(m_addr,Addr,MAC_NUM_LEN);
   
   
}

////////////////////////////////////////////////////////////////////////
// Name:       RS485Operater::Receive(int Addr, int buf, int len, std::string errStr)
// Purpose:    Implementation of RS485Operater::Receive()
// Comment:    ��������
// Parameters:
// [in/out] Addr ���ط��ͷ���ַ	
// [out] buf	 ���ؽ��������׵�ַ
// [in/out] len  ���ؽ��յ������ݳ���
// - errStr
// Return:     int
////////////////////////////////////////////////////////////////////////

int RS485Trans::Receive(char* Addr, char *buf, int &len)
{
   // TODO : implement
   	int overtime = 0;
	int packageLen = 0; //������
	int tmpLen;
	unsigned short crc=0;
	m_recvPos = 0;
	//����Ϊ����
	CGlobalIOSet* g_globalIOSet = CSingleton<CGlobalIOSet>::instance();
	g_globalIOSet->m_485Direct->SetDigitalOut(LOW);
	
	while (overtime < 1000)
	{
		if (ser_can_read(UART2)> 0)
		{
			//�жϰ�ͷ
			usart2_read((char*)m_recvBuff, 1);
			DBG_PRN(("%02X",m_recvBuff[0]))
			if(m_recvBuff[0] != '2')//��ͷ���ԣ�����
			{
				return 0;
			}
			m_recvPos++;
			//���е�ַƥ��
			usart2_read((char *)m_recvBuff+m_recvPos, MAC_NUM_LEN);
			if(strncmp((const char *)m_recvBuff+m_recvPos, m_addr,MAC_NUM_LEN )!=0)//��ַ���� ����
			{
				m_recvPos = 0;
				return 0;
			}
			m_recvPos = m_recvPos+10;
			
			//�����ͷ���ַ���뵽ADDR
			usart2_read((char *)m_recvBuff+m_recvPos, MAC_NUM_LEN);
			memcpy(Addr,m_recvBuff+m_recvPos,MAC_NUM_LEN);
			m_recvPos = m_recvPos+10;
		
			//�����ܳ���
			usart2_read((char *)m_recvBuff+m_recvPos, 4);
			memcpy((char*)&packageLen,m_recvBuff+m_recvPos,4);
			DBG_PRN(("%s len= %d","get packge",packageLen))
			m_recvPos = m_recvPos+4;
			len = packageLen;
						
			if (packageLen > 0)
			{
				while(m_recvPos < packageLen)
				{
					tmpLen =  usart2_read((char*)(m_recvBuff+m_recvPos), packageLen-m_recvPos);
					m_recvPos += tmpLen;
					if (tmpLen ==0)//��ʱ������ղ�����������
					{
						overtime++;
						Delay_ms(3);
						if (overtime > 1000)
						{
							return -1;
						}
					}
				}
				//�ɹ�������һ������ ��ʼcrcУ��
				crc = cal_crc(m_recvBuff, m_recvPos);
				DBG_PRN(("crc = %04x",crc))
				//crc = (crc&0x00FF)*256 + (crc&0xFF00)/256;
				DBG_NPRINT_HEX(((char *)&crc),2)
				DBG_NPRINT_HEX((m_recvBuff+m_recvPos),2)
				if(strncmp((const char*)m_recvBuff+m_recvPos,(char *)&crc, 2))
				{
					DBG_PRN(("����У�����"))
					return 0;
				}
				memcpy(buf,m_recvBuff+1+MAC_NUM_LEN+MAC_NUM_LEN+4,packageLen);
				len = packageLen;
				return 1;
			}
		}
		overtime++;
		Delay_ms(3);
	}
}

////////////////////////////////////////////////////////////////////////
// Name:       RS485Operater::Close(std::string errStr)
// Purpose:    Implementation of RS485Operater::Close()
// Comment:    �ر�485
// Parameters:
// - errStr
// Return:     int
////////////////////////////////////////////////////////////////////////

int RS485Trans::Close()
{
   // TODO : implement
}



RS485Trans::RS485Trans()
{
	memset(m_addr,'0',sizeof(m_addr));
}
