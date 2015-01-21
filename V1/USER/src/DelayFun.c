#include "DelayFun.h" 

// void delay_us(u16 time) {
//	u16 i=0;      
//	while(time--)    
//	{        
//		i=10;  //�Լ�����       
//		while(i--)	{}	
//	} 
//}
//
//void delay_ms(u16 time) {
//	u16 i=0;      
//	while(time--)    
//	{        
//		i=10000;  //�Լ�����       
//		while(i--)	{}	
//	} 
//}

static unsigned char   fac_us=0;//us��ʱ������ 
static unsigned short fac_ms=0;//ms��ʱ������ 
/*��ʱ����ʼ������*/ 
//SYSCLKΪϵͳʱ��Ƶ�ʳ���1000000���ֵ���������ϵͳʱ��Ƶ��Ϊ72MHz������øú���ʱ�˴���ʵ��Ϊ72  
void Delay_Init( unsigned char SYSCLK)
{
	SysTick->CTRL&=0xFFFFFFFB;
	fac_us=SYSCLK/8;
	fac_ms=(unsigned short)(fac_us*1000);		
}

/*1΢����ʱ����*/ 
void Delay_us(unsigned int nus)
{
	unsigned int temp;
	SysTick->LOAD=nus*fac_us;
	SysTick->VAL=0x00;
	SysTick->CTRL=0x01;
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&0x10000));
	SysTick->CTRL=0x00;
	SysTick->VAL=0x00;	
}

/*1������ʱ����*/
void Delay_ms(unsigned short nms)
{
	unsigned int temp;
	SysTick->LOAD=(unsigned int)(nms*fac_ms);
	SysTick->VAL=0x00;
	SysTick->CTRL=0x01;
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&0x10000));
	SysTick->CTRL=0x00;
	SysTick->VAL=0x00;	
}
