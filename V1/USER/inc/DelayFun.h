#ifndef DELAY_FUN
#define DELAY_FUN

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f10x.h" 
//void delay_ms(u16 time);
//void delay_us(u16 time);

void Delay_Init( unsigned char SYSCLK);
void Delay_us(unsigned int nus);
void Delay_ms(unsigned short nms);
#ifdef __cplusplus
}
#endif

#endif




