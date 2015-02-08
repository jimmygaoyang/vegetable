#include "I2C1.h"

void I2C1_Init(void){

	GPIO_InitTypeDef GPIO_InitStruct;
	I2C_InitTypeDef I2C_InitStruct;

	/* Enable Peripheral Clock for I2C1 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);

	/* Enable Peripheral Clock for SDA SCL Pins(GPIOB) */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStruct);

	// /* Connect I2C1 pins to AF */
	// GPIO_PinAFConfig(GPIOB, GPIO_Pin_6, GPIO_AF_I2C1);
	// GPIO_PinAFConfig(GPIOB, GPIO_Pin_7, GPIO_AF_I2C1);

	/* configure I2C1 */
	
	I2C_InitStruct.I2C_ClockSpeed = 200000;
	I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStruct.I2C_OwnAddress1 = 0x00;
	I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_Init(I2C1, &I2C_InitStruct);

	/* enable I2C1 */
	I2C_Cmd(I2C1, ENABLE);
}

/* This function issues a start condition and
 * transmits the slave address + R/W bit
 *
 * Parameters:
 * 		I2Cx --> the I2C peripheral e.g. I2C1
 * 		address --> the 7 bit slave address
 * 		direction --> the transmission direction can be:
 * 						I2C_Direction_Tranmitter for Master transmitter mode
 * 						I2C_Direction_Receiver for Master receiver
 */

void I2C_start(I2C_TypeDef* I2Cx, unsigned char address, unsigned char direction){
	// wait until I2C1 is not busy any more
	do{
	;
	}while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));
//	while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));

	// Send I2C1 START condition
	I2C_GenerateSTART(I2Cx, ENABLE);

	// wait for I2C1 EV5 --> Slave has acknowledged start condition
	do{
	;
	}while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT));
//	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT));

	// Send slave Address for write
	I2C_Send7bitAddress(I2Cx, address, direction);

	/* wait for I2Cx EV6, check if
	 * either Slave has acknowledged Master transmitter or
	 * Master receiver mode, depending on the transmission
	 * direction
	 */
	if(direction == I2C_Direction_Transmitter){
	do{
	;
	}while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));	
//		while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	}
	else if(direction == I2C_Direction_Receiver){
	do{

	}  while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
//		while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
	}
}

/* This function transmits one byte to the slave device
 * Parameters:
 *		I2Cx --> the I2C peripheral e.g. I2C1
 *		data --> the data byte to be transmitted
 */
void I2C_write(I2C_TypeDef* I2Cx, uint8_t data)
{
	// wait for I2C1 EV8 --> last byte is still being transmitted (last byte in SR, buffer empty), next byte can already be written
	do{
		;
	}while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTING));
//	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTING));
	I2C_SendData(I2Cx, data);
}

/* This function reads one byte from the slave device
 * and acknowledges the byte (requests another byte)
 */
unsigned char I2C_read_ack(I2C_TypeDef* I2Cx){
	unsigned char data;
	// enable acknowledge of received data
	I2C_AcknowledgeConfig(I2Cx, ENABLE);
	// wait until one byte has been received
	do{
	;
	}while( !I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED) );
//	while( !I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED) );
	// read data from I2C data register and return data byte
	data = I2C_ReceiveData(I2Cx);
	return data;
}

/* This function reads one byte from the slave device
 * and doesn't acknowledge the received data
 * after that a STOP condition is transmitted
 */
unsigned char I2C_read_nack(I2C_TypeDef* I2Cx){
	// disable acknowledge of received data
	// nack also generates stop condition after last byte received
	// see reference manual for more info
	unsigned char data;
	I2C_AcknowledgeConfig(I2Cx, DISABLE);
	I2C_GenerateSTOP(I2Cx, ENABLE);
	// wait until one byte has been received
	do{
		;
	}while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED));
//	while( !I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED) );
	// read data from I2C data register and return data byte
	data = I2C_ReceiveData(I2Cx);
	return data;
}

/* This function issues a stop condition and therefore
 * releases the bus
 */
void I2C_stop(I2C_TypeDef* I2Cx){

	// Send I2C1 STOP Condition after last byte has been transmitted
	I2C_GenerateSTOP(I2Cx, ENABLE);
	// wait for I2C1 EV8_2 --> byte has been transmitted
//	do{
//	;
//	}while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
//	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
}
