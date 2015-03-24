#ifndef __RTC_H__
#define __RTC_H__

struct SECONDS{//��
	Uint16 s:4;
	Uint16 es:4;
	Uint16 rsv:8;
	};
union SECONDSTYPE{
	Uint16 all;	
	struct SECONDS bit;
	};
struct MINUTES{//��
	Uint16 m:4;
	Uint16 em:4;
	Uint16 rsv:8;
	};
union MINUTESTYPE{
	Uint16 all;	
	struct MINUTES bit;
	};	
struct HOUR{//ʱ
	Uint16 h:4;
	Uint16 eh:4;
	Uint16 rsv:8;
	};
union HOURTYPE{
	Uint16 all;	
	struct HOUR bit;
	};
struct DATE{//��
	Uint16 d:4;
	Uint16 ed:4;
	Uint16 rsv:8;
	};
union DATETYPE{
	Uint16 all;	
	struct DATE bit;
	};
struct MONTH{//��
	Uint16 m:4;
	Uint16 em:4;
	Uint16 rsv:8;
	};
union MONTHTYPE{
	Uint16 all;	
	struct MONTH bit;
	};
struct YEAR{//��
	Uint16 y:4;
	Uint16 ey:4;
	Uint16 eey:4;
	Uint16 eeey:4;
	};
union YEARTYPE{
	Uint32 all;	
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
//DS1302��ʼ������-------------------
void Rtc_init(char *p);
//ʱ�Ӽ�ʱ��⺯��
void RTC_check();
//��ȡʱ���������
void GetTime(char *p);




#endif





