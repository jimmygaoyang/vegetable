#ifndef _USART_H
#define _USART_H 

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f10x.h"
#include <string.h>


/* UART common define */
#define UART1	0
#define UART2	1
#define UART3	2

#define UART_NUM     3

#define UART1_RX_BUFFER_SIZE 255			
#define UART2_RX_BUFFER_SIZE 512
#define UART3_RX_BUFFER_SIZE 255




typedef struct UART_BUFFER_STRUCT
{
	unsigned int volatile  uUartRxHead, uUartRxTail;  
	char *    pucUartRxBuf;
	unsigned int volatile uRecCnt; 
    
} UART_BUFFER_T;


unsigned int ser_can_read(char nNum);
void uartReceiveChars(char nNum);


void usart1_open(unsigned int baudRate);

unsigned int  usart1_write(char *buff, unsigned int length);

void  usart1_send_str(char *buff);

void  usart1_send_byte(char buff);


unsigned int  usart1_read(char *buff, unsigned int length);

//void  usart1_close();


void usart2_open(unsigned int baudRate);

unsigned int  usart2_write(char *buff, unsigned int length);

void  usart2_send_str(char *buff);

void  usart2_send_byte(char buff);

unsigned int  usart2_read(char *buff, unsigned int length);

//void  usart2_close();


void usart3_open(unsigned int baudRate);

unsigned int  usart3_write(char *buff, unsigned int length);

void  usart3_send_str(char *buff);

void  usart3_send_byte(char buff);


unsigned int  usart3_read(char *buff, unsigned int length);

//void  usart3_close();

#ifdef __cplusplus
}
#endif

#endif


