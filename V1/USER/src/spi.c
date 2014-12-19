#include "spi.h"

static int CurMode = MODE_8_BITS_;
int SPI1Init(void){
	SPI_InitTypeDef  SPI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_SPI1, ENABLE ); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);

	/** SPI1 GPIO Configuration	
		 PA4	 ------> SPI1_NSS
		 PA5	 ------> SPI1_SCK
		 PA6	 ------> SPI1_MISO
		 PA7	 ------> SPI1_MOSI
	*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;//PA5.6.7复用 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

/*	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;  //SPI_CS
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //复用推挽输出
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_3);
	*/
	
	SPI_Cmd( SPI1, DISABLE );
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;	 //双工模式
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;	 //SPI主模式
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b; //8bit数据
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;   //CLK空闲时为高电平			
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;	 //CLK上升沿采样，因为上升沿是第二个边沿动作，所以也可以理解为第二个边沿采样
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		 //片选用软件控制
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;  //SPI频率
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;    //高位在前
	SPI_InitStructure.SPI_CRCPolynomial = 7;	  //crc7，stm32spi带硬件ecc
	SPI_Init(SPI1, &SPI_InitStructure);
	SPI_Cmd(SPI1, ENABLE);

	/*Enable SPI1.NSS as a GPIO*/
//	SPI_SSOutputCmd(SPI1, ENABLE);
	
	/*Configure PA.4(NSS)--------------------------------------------*/
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_15);
	
	return 1;
	
}

void SetSpiDataLen(int mode){
	SPI_InitTypeDef  SPI_InitStructure;

	if(CurMode != mode)
	{
		if(MODE_8_BITS_ == mode){
		SPI_Cmd( SPI1, DISABLE );
		SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;	 //双工模式
		SPI_InitStructure.SPI_Mode = SPI_Mode_Master;	 //SPI主模式
		SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b; //8bit数据
		SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;   //CLK空闲时为电平			
		SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;	 //CLK上升沿采样，因为上升沿是第二个边沿动作，所以也可以理解为第二个边沿采样
		SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		 //片选用软件控制
		SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;  //SPI频率
		SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;    //高位在前
		SPI_InitStructure.SPI_CRCPolynomial = 7;	  //crc7，stm32spi带硬件ecc
		SPI_Init(SPI1, &SPI_InitStructure);
		SPI_Cmd(SPI1, ENABLE);
	}
	if(MODE_16_BITS_ == mode){
		SPI_Cmd( SPI1, DISABLE );
		SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;	 //双工模式
		SPI_InitStructure.SPI_Mode = SPI_Mode_Master;	 //SPI主模式
		SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b; //8bit数据
		SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;   //CLK空闲时为高电平			
		SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;	 //CLK上升沿采样，因为上升沿是第二个边沿动作，所以也可以理解为第二个边沿采样
		SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		 //片选用软件控制
		SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;  //SPI频率
		SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;    //高位在前
		SPI_InitStructure.SPI_CRCPolynomial = 7;	  //crc7，stm32spi带硬件ecc
		SPI_Init(SPI1, &SPI_InitStructure);
		SPI_Cmd(SPI1, ENABLE);
		}

	CurMode = mode;
		
	}

}

//SPI读写一个8位数据
unsigned char SPI1WriteReadByte(unsigned char TxData)
{
	unsigned char recChar = 0;
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET) //检查指定的SPI标志位设置与否:发送缓存空标志位
	{
		;
	} 
	
	SPI_I2S_SendData(SPI1, TxData); //通过外设SPIx发送一个数据
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET)//检查指定的SPI标志位设置与否:接受缓存非空标志位
	{
		;
	}
	recChar = (unsigned char)SPI_I2S_ReceiveData(SPI1);
	return recChar;//返回通过SPIx最近接收的数据 	   
}

//SPI读写一个16位数据
unsigned int SPI1WriteRead2Byte(int TxData)
{
//	unsigned char retry=0;	
	 
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET) //检查指定的SPI标志位设置与否:发送缓存空标志位
	{
		;
	} 
	
	
	SPI_I2S_SendData(SPI1, TxData); //通过外设SPIx发送一个数据
	
	
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET)//检查指定的SPI标志位设置与否:接受缓存非空标志位
	{
		;
	}
		 			
	return SPI_I2S_ReceiveData(SPI1); //返回通过SPIx最近接收的数据 	   
}

void SPI1Enable(void)
	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_15);
	
	}
void SPI1Disable(void)
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_15);
	
	}








