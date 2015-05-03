#ifndef __RTC_H__
#define __RTC_H__


#include "GlobalIOSet.h"

struct SECONDS{//��
	unsigned short s:4;
	unsigned short es:4;
	unsigned short rsv:8;
	};
union SECONDSTYPE{
	unsigned short all;	
	struct SECONDS bit;
	};
struct MINUTES{//��
	unsigned short m:4;
	unsigned short em:4;
	unsigned short rsv:8;
	};
union MINUTESTYPE{
	unsigned short all;	
	struct MINUTES bit;
	};	
struct HOUR{//ʱ
	unsigned short h:4;
	unsigned short eh:4;
	unsigned short rsv:8;
	};
union HOURTYPE{
	unsigned short all;	
	struct HOUR bit;
	};
struct DATE{//��
	unsigned short d:4;
	unsigned short ed:4;
	unsigned short rsv:8;
	};
union DATETYPE{
	unsigned short all;	
	struct DATE bit;
	};
struct MONTH{//��
	unsigned short m:4;
	unsigned short em:4;
	unsigned short rsv:8;
	};
union MONTHTYPE{
	unsigned short all;	
	struct MONTH bit;
	};
struct YEAR{//��
	unsigned short y:4;
	unsigned short ey:4;
	unsigned short eey:4;
	unsigned short eeey:4;
	};
union YEARTYPE{
	unsigned int all;	
	struct YEAR bit;
	};

typedef struct TIMETYPE{
	union SECONDSTYPE second;
	union MINUTESTYPE minutes;
	union HOURTYPE    hour;
	union DATETYPE    date;
	union MONTHTYPE   month;
	union YEARTYPE    year;
	}timestruct;

class RTC1302
	{
	public:	
		RTC1302();
		~RTC1302();
		
		//��ȡʱ���������
	public:
		 void GetTime(char *p);
		//DS1302��ʼ������-------------------
		 void Rtc_init(char *p);
		//��ȡ���ڵ�����ֵ
		unsigned int RTC1302::GetDateInt();
		//��ȡʱ�������ֵ
		unsigned int RTC1302::GetTimeInt();
   private:
		//����ʱ����------------------------
		void dela(void);
		//����ʱ����------------------------
		void tdela(void);
		//DS1302��λ����--------------------
		void Rst1302();
		//д���ݽ�������--------------------
		void EndWrCLK();
		//DS1302��д���--------------------
		void EnWrite1302();
		//DS1302��д����--------------------
		void DisWrite1302();
		//����Ϊ���״̬--------------------
		void RTC_init_out();
		//����Ϊ����״̬--------------------
		void RTC_init_in();
		//DS1302��ȡһ���ֽ�----------------
		unsigned short RTC_receive();
		//��DS1302����һ���ֽ�----------------
		void RTC_send(unsigned short data);

		//ʱ�Ӽ�ʱ��⺯��
		void RTC_check();

		private:
		CGlobalIOSet* g_globalIOSet;
		

	};






#endif





