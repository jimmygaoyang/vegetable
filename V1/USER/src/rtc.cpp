//#include "string.h"
#include "DelayFun.h"
#include "rtc.h"
//#define DI0		*(int *)0x80000//����������1
//#define DI1		*(int *)0x80001//����������2
//#define DO0		*(int *)0x80002 //���������1
char temp[50]={0};
int DOshadow;
timestruct Time;//ʱ��ṹ��
extern int data;//��ˮ��״̬


RTC1302::RTC1302()
	{
		g_globalIOSet = CSingleton<CGlobalIOSet>::instance();
	}

RTC1302::~RTC1302()
	{

	}


//����ʱ����------------------------
void RTC1302::dela(void)
{
	Delay_us(1000);  
}
//����ʱ����------------------------
void RTC1302::tdela(void)
{
	Delay_us(100);  
}
//DS1302��λ����--------------------
void RTC1302::Rst1302()
{
	
	g_globalIOSet->m_OUT_RTCCLK->SetDigitalOut(LOW);//RTCCLK=0
	tdela();
	g_globalIOSet->m_OUT_RTCRST->SetDigitalOut(LOW);//RTCRESET=0
	tdela();
	g_globalIOSet->m_OUT_RTCRST->SetDigitalOut(HIGH);//RTCRESET=1
	tdela();
}
//д���ݽ�������--------------------
void RTC1302::EndWrCLK()
{
	g_globalIOSet->m_OUT_RTCRST->SetDigitalOut(LOW);//RTCRESET=0
	tdela();
	g_globalIOSet->m_OUT_RTCCLK->SetDigitalOut(HIGH);//RTCCLK=1
	tdela();
}
//DS1302��д���--------------------
void RTC1302::EnWrite1302()
{
Rst1302();
RTC_send(0x8e);
RTC_send(0x00);
EndWrCLK();
}
//DS1302��д����--------------------
void RTC1302::DisWrite1302()
{
Rst1302();
RTC_send(0x8e);
RTC_send(0x80);
EndWrCLK();
}
//����Ϊ���״̬--------------------
void RTC1302::RTC_init_out()
{

	g_globalIOSet->m_INOUT_RTCDAT->SetMode(OUT);
	tdela();
}
//����Ϊ����״̬--------------------
void RTC1302::RTC_init_in()
{

	g_globalIOSet->m_INOUT_RTCDAT->SetMode(IN);

tdela();
}
//DS1302��ȡһ���ֽ�----------------
unsigned short RTC1302::RTC_receive()
{
	 unsigned short i,buf;
	 buf=0;

	 RTC_init_in();
	 for(i=0;i<8;i++)
	 {
		g_globalIOSet->m_OUT_RTCCLK->SetDigitalOut(LOW);//RTCCLK=0
		tdela();
		buf=buf>>1;
		if(g_globalIOSet->m_INOUT_RTCDAT->ReadDigitalIn()==1)
		buf=buf+0x80;
		tdela();
		g_globalIOSet->m_OUT_RTCCLK->SetDigitalOut(HIGH);//RTCCLK=1
		tdela();	
	 }
	 return buf;
}
//��DS1302����һ���ֽ�----------------
void RTC1302::RTC_send(unsigned short data)
{

	 unsigned short i;

	 RTC_init_out();
	 for(i=0;i<8;i++)
	 {	if((data%2)==0x1)
			g_globalIOSet->m_INOUT_RTCDAT->SetDigitalOut(HIGH);//DAT=1
		else
			g_globalIOSet->m_INOUT_RTCDAT->SetDigitalOut(LOW);//DAT=0		
		tdela();
		g_globalIOSet->m_OUT_RTCCLK->SetDigitalOut(HIGH);//RTCCLK=1
		tdela();
		g_globalIOSet->m_OUT_RTCCLK->SetDigitalOut(LOW);//RTCCLK=0
		data>>=1;
		tdela();	
	 }
}
//DS1302��ʼ������-------------------
void RTC1302::Rtc_init(char *p)
{
	unsigned short i,j;

	EnWrite1302();
	temp[0]=((p[17]-0x30)*16+(p[18]-0x30));
	temp[1]=((p[14]-0x30)*16+(p[15]-0x30));
	temp[2]=((p[11]-0x30)*16+(p[12]-0x30));
	temp[3]=((p[8]-0x30)*16+(p[9]-0x30));
	temp[4]=((p[5]-0x30)*16+(p[6]-0x30));
	temp[5]=0x00;
	temp[6]=((p[2]-0x30)*16+(p[3]-0x30));	
	i=0;
	
	for(j=0;j<7;j++)
	{
		Rst1302();
		g_globalIOSet->m_OUT_RTCCLK->SetDigitalOut(LOW);//RTCCLK=0
		tdela();
		g_globalIOSet->m_OUT_RTCRST->SetDigitalOut(HIGH);//RTCRESET=1
		tdela();
		RTC_send(0x80+i);
		RTC_send(temp[j]);
		EndWrCLK();
		i=i+2;
		EndWrCLK();		
	}
	DisWrite1302();
}
//ʱ�Ӽ�ʱ��⺯��
void RTC1302::RTC_check()
{
	unsigned short i,j;
	for(i=0;i<7;i++)
	temp[i]=0;
	for(i=0,j=0;i<7;i++)
	{
		Rst1302();

		RTC_send(0x81+j);
		Delay_us(1000L);
		temp[i]=RTC_receive();
		j+=2;
		EndWrCLK();
	}
}

void RTC1302::GetTime(char *p)//��ȡʱ���������
{
EnWrite1302();//д���
RTC_send(0x90);
RTC_send(0xb5);
DisWrite1302();//д����
RTC_check();
Time.second.all=temp[0];
Time.minutes.all=temp[1];
Time.hour.all=temp[2];
Time.date.all=temp[3];
Time.month.all=temp[4];
Time.year.all=temp[6];
Time.year.bit.eeey=2;
Time.year.bit.eey=0;
p[0]=Time.year.bit.eeey+0x30;
p[1]=Time.year.bit.eey+0x30;
p[2]=Time.year.bit.ey+0x30;
p[3]=Time.year.bit.y+0x30;
p[4]='-';
p[5]=Time.month.bit.em+0x30;
p[6]=Time.month.bit.m+0x30;
p[7]='-';
p[8]=Time.date.bit.ed+0x30;
p[9]=Time.date.bit.d+0x30;
p[10]=' ';
p[11]=Time.hour.bit.eh+0x30;
p[12]=Time.hour.bit.h+0x30;
p[13]=':';
p[14]=Time.minutes.bit.em+0x30;
p[15]=Time.minutes.bit.m+0x30;
p[16]=':';
p[17]=Time.second.bit.es+0x30;
p[18]=Time.second.bit.s+0x30;
p[19]=0x00;
}

