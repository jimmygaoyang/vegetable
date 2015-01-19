
#include "usart.h"
#include "BuffType.h"


static UART_BUFFER_T volatile UART_DEV[UART_NUM]; 

 
static unsigned int UARTRXBUFSIZE[UART_NUM] = {UART1_RX_BUFFER_SIZE, UART2_RX_BUFFER_SIZE, UART3_RX_BUFFER_SIZE};

static char Uart1RxBuffer[UART1_RX_BUFFER_SIZE];
static char Uart2RxBuffer[UART2_RX_BUFFER_SIZE];
static char Uart3RxBuffer[UART3_RX_BUFFER_SIZE];
//extern circle_buffer_t ringFilterBuf;
//extern int ringFlag;

static void uartBufferInit(char nNum)
{
//	int i;
	UART_BUFFER_T *dev;
	
	dev = (UART_BUFFER_T *) &UART_DEV[nNum];
	
	/* initial memory */
//	for(i=0; i<UARTRXBUFSIZE[nNum]; i++)
//		dev->pucUartRxBuf[i] = 0;

	memset(dev->pucUartRxBuf, 0, UARTRXBUFSIZE[nNum]);

	
	/* inital struct UART_BUFFER_STRUCT, uUartTxHead, uUartTxTail, uUartRxHead, uUartRxTail */	
	dev->uUartRxHead = dev->uUartRxTail = NULL;
	dev->uRecCnt = 0;
}

static unsigned int uartRxBufGetNextOne(char nNum, unsigned int uPointer)    
{
	if((uPointer + 1) == UARTRXBUFSIZE[nNum])
		return NULL;
	else
		return (uPointer + 1);	
}


void uartReceiveChars(char nNum)
{
	unsigned int volatile uBuf = 0;
	unsigned short receiveChar;
//	char ringBuf[6];
//	int res;
	USART_TypeDef* USARTx;
	UART_BUFFER_T *dev;	
	dev = (UART_BUFFER_T *) &UART_DEV[nNum];
	
	if(nNum == UART1)
		USARTx = USART1;
	else if(nNum == UART2)
		USARTx = USART2;
	else if(nNum == UART3)
		USARTx = USART3;	
	while(1)
	{
		uBuf = uartRxBufGetNextOne(nNum, dev->uUartRxTail);
			/* Read one byte from the receive data register */
		if(USART_GetITStatus(USARTx, USART_IT_RXNE) != RESET)			
			receiveChar = USART_ReceiveData(USARTx);
		if(uBuf == dev->uUartRxHead)  
			break;  // 03.08
		dev->pucUartRxBuf[dev->uUartRxTail] = (char)receiveChar;	
		dev->uUartRxTail = uartRxBufGetNextOne(nNum, dev->uUartRxTail);
		dev->uRecCnt++;	
		break;
	}
	//SendBack
	// if(nNum == UART1){
	// 	USART_SendData(USART1, receiveChar);
	// 	}
		
	//过滤ring字符
//	memset(ringBuf,0,6);
//	ringFilterBuf.AddNew((void *)(&ringFilterBuf),(char *)&receiveChar);
//	ringFilterBuf.ReadAll((void *)(&ringFilterBuf),ringBuf,(unsigned int *)&res);
//	if(!strncmp(ringBuf, "RING",4))
//		ringFlag = 1;
	
}


	


unsigned int ser_can_read(char nNum)
{
	UART_BUFFER_T *dev;	
	dev = (UART_BUFFER_T *) &UART_DEV[nNum];
	return (dev->uRecCnt);
}

static unsigned int uartReadRxBuf(char nNum, char * pucBuf, unsigned int uLen)
{
	int i;		
	UART_BUFFER_T *dev;	
	dev = (UART_BUFFER_T *) &UART_DEV[nNum];
	
	// disable Rx interrupt .....
	if(dev->uRecCnt == 0)  // no data in Rx buffer
		return 0;

	if(uLen > dev->uRecCnt)	
		uLen = dev->uRecCnt;

	for(i = uLen ; i > 0 ; i--)
	{
		*pucBuf++ = dev->pucUartRxBuf[dev->uUartRxHead];
		dev->uUartRxHead = uartRxBufGetNextOne(nNum, dev->uUartRxHead);
	}		
	dev->uRecCnt -= uLen;  // maintain uRecCnt value	
			
	return (uLen);
}




void usart1_open(unsigned int baudRate)
{	
	GPIO_InitTypeDef GPIO_InitStructure;	
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//初始化接收缓冲区
	UART_DEV[UART1].pucUartRxBuf = Uart1RxBuffer;
	uartBufferInit(UART1);

		
	//使能串口、串口所用的I/O口以及端口复用时钟	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1|RCC_APB2Periph_AFIO, ENABLE);

    //串口1设置
	/* A9 USART1_Tx */	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 	 //推挽输出-TX	
	GPIO_Init(GPIOA,&GPIO_InitStructure);		
	/* A10 USART1_Rx */	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入-RX	
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//串口属性
	USART_InitStructure.USART_BaudRate = baudRate;	
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	
	USART_InitStructure.USART_StopBits = USART_StopBits_1;	
	USART_InitStructure.USART_Parity = USART_Parity_No;	
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	
	USART_Init(USART1, &USART_InitStructure);

	//使能中断

	/* Configure the NVIC Preemption Priority Bits */  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	/* Enable the USART1 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//使能USART1接收中断

	//使能串口1
	USART_Cmd(USART1, ENABLE);
	
}




unsigned int  usart1_write(char *buff, unsigned int length)
{
	int i; 
	for(i=0; i<length; i++)
	{	
		USART_SendData(USART1, *(buff+i));	

		/* Loop until the end of transmission */		
		while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
	}
	return length;
}

void  usart1_send_str(char *buff)
{
    while(*buff)
    {
        usart1_write(buff++, 1);
    }

}

void  usart1_send_byte(char buff)
{
	  usart1_write(&buff, 1);

}



unsigned int  usart1_read(char *buff, unsigned int length)
{
	unsigned int number = 0;

	if((number = ser_can_read(UART1)) > 0){
		number = (number>length) ? length:number;
		
		uartReadRxBuf(UART1, buff, number);
	}
	return number;

}


void usart2_open(unsigned int baudRate)
{

 	GPIO_InitTypeDef GPIO_InitStructure;	
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	//初始化接收缓冲区
	UART_DEV[UART2].pucUartRxBuf = Uart2RxBuffer;
	uartBufferInit(UART2);

		
	//使能串口、串口所用的I/O口以及端口复用时钟	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	
	//串口2设置
	/* A2 USART2_Tx */	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //推挽输出-TX	
	GPIO_Init(GPIOA,&GPIO_InitStructure);		
	/* A3 USART2_Rx */	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入-RX	
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//串口属性
	USART_InitStructure.USART_BaudRate = baudRate;	
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	
	USART_InitStructure.USART_StopBits = USART_StopBits_1;	
	USART_InitStructure.USART_Parity = USART_Parity_No;	
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	
	USART_Init(USART2, &USART_InitStructure);

	//使能中断
	
	/* Configure the NVIC Preemption Priority Bits */  
	/* Enable the USART2 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//使能USART2接收中断


	//使能串口2
	USART_Cmd(USART2, ENABLE);


	
}




unsigned int  usart2_write(char *buff, unsigned int length)
{
	int i; 
	for(i=0; i<length; i++)
	{	
		USART_SendData(USART2, *(buff+i));	

		/* Loop until the end of transmission */		
		while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
	}
	return length;
}

void  usart2_send_str(char *buff)
{
    while(*buff)
    {
        usart2_write(buff++, 1);
    }

}

void  usart2_send_byte(char buff)
{

        usart2_write(&buff, 1);

}




unsigned int  usart2_read(char *buff, unsigned int length)
{
	unsigned int number = 0;

	if((number = ser_can_read(UART2)) > 0){
		number = (number>length) ? length:number;
		
		uartReadRxBuf(UART2, buff, number);
	}
	return number;

}


void usart3_open(unsigned int baudRate)
{
  	GPIO_InitTypeDef GPIO_InitStructure;	
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	//初始化接收缓冲区
	UART_DEV[UART3].pucUartRxBuf = Uart3RxBuffer;
	uartBufferInit(UART3);
		
	//使能串口、串口所用的I/O口以及端口复用时钟	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	
	//串口3设置
	/* B10 USART3_Tx */	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //推挽输出-TX	
	GPIO_Init(GPIOB,&GPIO_InitStructure);		
	/* B11 USART3_Rx */	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入-RX	
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	//串口属性
	USART_InitStructure.USART_BaudRate = baudRate;	
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	
	USART_InitStructure.USART_StopBits = USART_StopBits_1;	
	USART_InitStructure.USART_Parity = USART_Parity_No;	
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	
	USART_Init(USART3, &USART_InitStructure);

	//使能中断
	/* Configure the NVIC Preemption Priority Bits */  
	/* Enable the USART3 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);


	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//使能USART3接收中断


	//使能串口3
	USART_Cmd(USART3, ENABLE);


	
}




unsigned int  usart3_write(char *buff, unsigned int length)
{
	int i; 
	for(i=0; i<length; i++)
	{	
		USART_SendData(USART3, *(buff+i));	

		/* Loop until the end of transmission */		
		while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
	}
	return length;
}

void  usart3_send_str(char *buff)
{
    while(*buff)
    {
        usart3_write(buff++, 1);
    }

}

void  usart3_send_byte(char buff)
{
        usart3_write(&buff, 1);

}




unsigned int  usart3_read(char *buff, unsigned int length)
{
	unsigned int number = 0;
	number = ser_can_read(UART3);
	if(number > 0){
		number = (number>length) ? length:number;
		
		uartReadRxBuf(UART3, buff, number);
	}
	return number;

}







