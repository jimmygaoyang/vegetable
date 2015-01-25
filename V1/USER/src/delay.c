

#include "stm32f10x_systick.h"
static u8   fac_us=0;//us��ʱ������ 
static u16 fac_ms=0;//ms��ʱ������ 
/*��ʱ����ʼ������*/ 
//SYSCLKΪϵͳʱ��Ƶ�ʳ���1000000���ֵ���������ϵͳʱ��Ƶ��Ϊ72MHz������øú���ʱ�˴���ʵ��Ϊ72  
void Delay_Init(u8t SYSCLK)
{
	SysTick->CTRL&=0xFFFFFFFB;
	fac_us=SYSCLK/8;
	fac_ms=(u16t)(fac_us*1000);		
}

/*1΢����ʱ����*/ 
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

/*1������ʱ����*/
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