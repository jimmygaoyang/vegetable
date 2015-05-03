#ifndef __RTC_H__
#define __RTC_H__


#include "GlobalIOSet.h"

struct SECONDS{//秒
	unsigned short s:4;
	unsigned short es:4;
	unsigned short rsv:8;
	};
union SECONDSTYPE{
	unsigned short all;	
	struct SECONDS bit;
	};
struct MINUTES{//分
	unsigned short m:4;
	unsigned short em:4;
	unsigned short rsv:8;
	};
union MINUTESTYPE{
	unsigned short all;	
	struct MINUTES bit;
	};	
struct HOUR{//时
	unsigned short h:4;
	unsigned short eh:4;
	unsigned short rsv:8;
	};
union HOURTYPE{
	unsigned short all;	
	struct HOUR bit;
	};
struct DATE{//日
	unsigned short d:4;
	unsigned short ed:4;
	unsigned short rsv:8;
	};
union DATETYPE{
	unsigned short all;	
	struct DATE bit;
	};
struct MONTH{//月
	unsigned short m:4;
	unsigned short em:4;
	unsigned short rsv:8;
	};
union MONTHTYPE{
	unsigned short all;	
	struct MONTH bit;
	};
struct YEAR{//年
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
		
		//获取时间的数组型
	public:
		 void GetTime(char *p);
		//DS1302初始化函数-------------------
		 void Rtc_init(char *p);
   private:
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

		//时钟计时检测函数
		void RTC_check();

		private:
		CGlobalIOSet* g_globalIOSet;
		

	};






#endif





