#ifndef DELAY_FUN
#define DELAY_FUN

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f10x.h" 
void delay_ms(u16 time);
void delay_us(u16 time);

#ifdef __cplusplus
}
#endif

#endif




