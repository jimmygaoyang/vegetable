#ifndef __RTC_H__
#define __RTC_H__

struct SECONDS{//秒
	Uint16 s:4;
	Uint16 es:4;
	Uint16 rsv:8;
	};
union SECONDSTYPE{
	Uint16 all;	
	struct SECONDS bit;
	};
struct MINUTES{//分
	Uint16 m:4;
	Uint16 em:4;
	Uint16 rsv:8;
	};
union MINUTESTYPE{
	Uint16 all;	
	struct MINUTES bit;
	};	
struct HOUR{//时
	Uint16 h:4;
	Uint16 eh:4;
	Uint16 rsv:8;
	};
union HOURTYPE{
	Uint16 all;	
	struct HOUR bit;
	};
struct DATE{//日
	Uint16 d:4;
	Uint16 ed:4;
	Uint16 rsv:8;
	};
union DATETYPE{
	Uint16 all;	
	struct DATE bit;
	};
struct MONTH{//月
	Uint16 m:4;
	Uint16 em:4;
	Uint16 rsv:8;
	};
union MONTHTYPE{
	Uint16 all;	
	struct MONTH bit;
	};
struct YEAR{//年
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

//长延时函数------------------------
void dela(void);
//短延时函数------------------------
void tdela(void);
//DS1302复位函数--------------------
void Rst1302();
//写数据结束函数--------------------
void EndWrCLK();
//DS1302的写许可--------------------
void EnWrite1302();
//DS1302的写保护--------------------
void DisWrite1302();
//设置为输出状态--------------------
void RTC_init_out();
//设置为输入状态--------------------
void RTC_init_in();
//DS1302读取一个字节----------------
unsigned short RTC_receive();
//向DS1302发送一个字节----------------
void RTC_send(unsigned short data);
//DS1302初始化函数-------------------
void Rtc_init(char *p);
//时钟计时检测函数
void RTC_check();
//获取时间的数组型
void GetTime(char *p);




#endif





