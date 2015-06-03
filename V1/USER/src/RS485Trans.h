/***********************************************************************
 * Module:  RS485Operater.h
 * Author:  Thinkpad
 * Modified: 2015-04-29 14:40:23
 * Purpose: Declaration of the class RS485Operater
 * Comment: RS485������
 ***********************************************************************/

#if !defined(__Veg_RS485Operater_h)
#define __Veg_RS485Operater_h
#define MAC_NUM_LEN 10

class RS485Trans
{
public:
   /* ��ָ����ַ�������� */
   int Send(char* Addr, char* buf, int len);
   /* ��ʼ�� */
   int Init(char* Addr);
   /* �������� */
   int Receive(char* Addr, char *buf, int &len);
   /* �ر�485 */
   int Close();

   int TransWith(char* Addr, char* inputBuf, int len, char* outputBuf, int &outlen,int timeout);

   RS485Trans();
   ~RS485Trans();

protected:
private:
	char m_addr[MAC_NUM_LEN];
	// buffer to receive data
    unsigned char m_recvBuff[256];
	// recvCount;
	int m_recvPos;
	// buffer to send data
	unsigned char m_sendBuff[256]; 
	//fillCount
	int m_fillPos;

};

#endif



