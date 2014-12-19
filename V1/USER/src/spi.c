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
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;//PA5.6.7���� 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

/*	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;  //SPI_CS
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //�����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_3);
	*/
	
	SPI_Cmd( SPI1, DISABLE );
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;	 //˫��ģʽ
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;	 //SPI��ģʽ
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b; //8bit����
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;   //CLK����ʱΪ�ߵ�ƽ			
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;	 //CLK�����ز�������Ϊ�������ǵڶ������ض���������Ҳ�������Ϊ�ڶ������ز���
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		 //Ƭѡ���������
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;  //SPIƵ��
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;    //��λ��ǰ
	SPI_InitStructure.SPI_CRCPolynomial = 7;	  //crc7��stm32spi��Ӳ��ecc
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
		SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;	 //˫��ģʽ
		SPI_InitStructure.SPI_Mode = SPI_Mode_Master;	 //SPI��ģʽ
		SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b; //8bit����
		SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;   //CLK����ʱΪ��ƽ			
		SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;	 //CLK�����ز�������Ϊ�������ǵڶ������ض���������Ҳ�������Ϊ�ڶ������ز���
		SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		 //Ƭѡ���������
		SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;  //SPIƵ��
		SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;    //��λ��ǰ
		SPI_InitStructure.SPI_CRCPolynomial = 7;	  //crc7��stm32spi��Ӳ��ecc
		SPI_Init(SPI1, &SPI_InitStructure);
		SPI_Cmd(SPI1, ENABLE);
	}
	if(MODE_16_BITS_ == mode){
		SPI_Cmd( SPI1, DISABLE );
		SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;	 //˫��ģʽ
		SPI_InitStructure.SPI_Mode = SPI_Mode_Master;	 //SPI��ģʽ
		SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b; //8bit����
		SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;   //CLK����ʱΪ�ߵ�ƽ			
		SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;	 //CLK�����ز�������Ϊ�������ǵڶ������ض���������Ҳ�������Ϊ�ڶ������ز���
		SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		 //Ƭѡ���������
		SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;  //SPIƵ��
		SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;    //��λ��ǰ
		SPI_InitStructure.SPI_CRCPolynomial = 7;	  //crc7��stm32spi��Ӳ��ecc
		SPI_Init(SPI1, &SPI_InitStructure);
		SPI_Cmd(SPI1, ENABLE);
		}

	CurMode = mode;
		
	}

}

//SPI��дһ��8λ����
unsigned char SPI1WriteReadByte(unsigned char TxData)
{
	unsigned char recChar = 0;
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET) //���ָ����SPI��־λ�������:���ͻ���ձ�־λ
	{
		;
	} 
	
	SPI_I2S_SendData(SPI1, TxData); //ͨ������SPIx����һ������
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET)//���ָ����SPI��־λ�������:���ܻ���ǿձ�־λ
	{
		;
	}
	recChar = (unsigned char)SPI_I2S_ReceiveData(SPI1);
	return recChar;//����ͨ��SPIx������յ����� 	   
}

//SPI��дһ��16λ����
unsigned int SPI1WriteRead2Byte(int TxData)
{
//	unsigned char retry=0;	
	 
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET) //���ָ����SPI��־λ�������:���ͻ���ձ�־λ
	{
		;
	} 
	
	
	SPI_I2S_SendData(SPI1, TxData); //ͨ������SPIx����һ������
	
	
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET)//���ָ����SPI��־λ�������:���ܻ���ǿձ�־λ
	{
		;
	}
		 			
	return SPI_I2S_ReceiveData(SPI1); //����ͨ��SPIx������յ����� 	   
}

void SPI1Enable(void)
	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_15);
	
	}
void SPI1Disable(void)
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_15);
	
	}








