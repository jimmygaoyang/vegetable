

#include "stm32f10x_systick.h"
static u8   fac_us=0;//us延时倍乘数 
static u16 fac_ms=0;//ms延时倍乘数 
/*定时器初始化函数*/ 
//SYSCLK为系统时钟频率除以1000000后的值，例：如果系统时钟频率为72MHz，则调用该函数时此处的实参为72  
void Delay_Init(u8t SYSCLK)
{
	SysTick->CTRL&=0xFFFFFFFB;
	fac_us=SYSCLK/8;
	fac_ms=(u16t)(fac_us*1000);		
}

/*1微秒延时函数*/ 
void Delay_us(u32t nus)
{
	u32t temp;
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
void Delay_ms(u16t nms)
{
	u32t temp;
	SysTick->LOAD=(u32t)(nms*fac_ms);
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