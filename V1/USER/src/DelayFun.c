#include "DelayFun.h" 

// void delay_us(u16 time) {
//	u16 i=0;      
//	while(time--)    
//	{        
//		i=10;  //自己定义       
//		while(i--)	{}	
//	} 
//}
//
//void delay_ms(u16 time) {
//	u16 i=0;      
//	while(time--)    
//	{        
//		i=10000;  //自己定义       
//		while(i--)	{}	
//	} 
//}

static unsigned char   fac_us=0;//us延时倍乘数 
static unsigned short fac_ms=0;//ms延时倍乘数 
/*定时器初始化函数*/ 
//SYSCLK为系统时钟频率除以1000000后的值，例：如果系统时钟频率为72MHz，则调用该函数时此处的实参为72  
void Delay_Init( unsigned char SYSCLK)
{
	SysTick->CTRL&=0xFFFFFFFB;
	fac_us=SYSCLK/8;
	fac_ms=(unsigned short)(fac_us*1000);		
}

/*1微秒延时函数*/ 
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

/*1毫秒延时函数*/
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
