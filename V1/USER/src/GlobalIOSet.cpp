#include "GlobalIOSet.h"


CIOObject::CIOObject(GPIO_TypeDef * IOGroup, unsigned short IOnum, unsigned int IOrcc)
{
	IO_Group = IOGroup;
	IO_num = IOnum;
	IO_rcc = IOrcc;
}

void CIOObject::SetMode(int director)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(IO_rcc,ENABLE);
	GPIO_InitStructure.GPIO_Pin = IO_num;
	if(director == IN)
	{
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	
	}
	if(director == OUT)
	{
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	}
	if(director == ANALOG)
	{
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	}
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(IO_Group, &GPIO_InitStructure);	
}

void CIOObject::SetDigitalOut(int Status)
{
	if(Status == HIGH)
	{
		GPIO_SetBits(IO_Group,IO_num);
	}
	if(Status == LOW)
	{
		GPIO_ResetBits(IO_Group,IO_num);
	}	
}

int CIOObject::ReadDigitalIn()
{
	if(GPIO_ReadInputDataBit(IO_Group,IO_num)==Bit_RESET)
	{
		return LOW;	
	}
	else
	{
		return HIGH;
	}
}



CGlobalIOSet::CGlobalIOSet()
{
	//put the dht11 sensor in the digital PC6
	m_IN_dht11 = new CIOObject(GPIOB,GPIO_Pin_12,RCC_APB2Periph_GPIOB); 
	m_IN_dht11->SetMode(IN);
	//put the DS1302 CLK 
	m_OUT_RTCCLK = new CIOObject(GPIOB,GPIO_Pin_14,RCC_APB2Periph_GPIOB); 
	m_OUT_RTCCLK->SetMode(OUT);
	//put the DS1302 DAT 
	m_INOUT_RTCDAT = new CIOObject(GPIOB,GPIO_Pin_13,RCC_APB2Periph_GPIOB); 
	m_INOUT_RTCDAT->SetMode(OUT);
	//put the DS1302 RST 
	m_OUT_RTCRST = new CIOObject(GPIOB,GPIO_Pin_15,RCC_APB2Periph_GPIOB); 
	m_OUT_RTCRST->SetMode(OUT);
	//set the hot run or close
	m_OUT_Hot = new CIOObject(GPIOC,GPIO_Pin_6,RCC_APB2Periph_GPIOC);
	m_OUT_Hot->SetMode(OUT);
	//set the pump run or close
	m_OUT_Water =  new CIOObject(GPIOC,GPIO_Pin_7,RCC_APB2Periph_GPIOC);
	m_OUT_Water->SetMode(OUT);
	//set the Wind module run or close  
	m_OUT_Wind = new CIOObject(GPIOC,GPIO_Pin_8,RCC_APB2Periph_GPIOC);	
	m_OUT_Wind->SetMode(OUT);
	//set the Light module run or close
	m_OUT_Light= new CIOObject(GPIOC,GPIO_Pin_9,RCC_APB2Periph_GPIOC);
	m_OUT_Light->SetMode(OUT);
	//read the input from the light sensor analog input
	m_IN_LightAnalog = new CIOObject(GPIOB,GPIO_Pin_0,RCC_APB2Periph_GPIOB);
	m_IN_LightAnalog->SetMode(ANALOG);
	//read the input from the dust humidity analog input
	m_In_DustAnalog = new CIOObject(GPIOB,GPIO_Pin_1,RCC_APB2Periph_GPIOB);	
	m_IN_LightAnalog->SetMode(ANALOG);
	//set the direct of rs485
	m_485Direct = new CIOObject(GPIOC,GPIO_Pin_12,RCC_APB2Periph_GPIOC);
	m_485Direct->SetMode(OUT);
}


