#include "BH1750.h"


unsigned char buff[2];

void BH1750_Init(){
	I2C_start(I2C1,BH1750Address<<1,I2C_Direction_Transmitter);
	I2C_write(I2C1,0x10);
	I2C_stop(I2C1);
}

unsigned short BH1750_Read(){
	unsigned short val=0;
	I2C_start(I2C1,BH1750Address<<1,I2C_Direction_Receiver);
	buff[0]=I2C_read_ack(I2C1);
	buff[1]=I2C_read_nack(I2C1);
	I2C_stop(I2C1);
	val=((buff[0]<<8)|buff[1])/1.2;
	return val;
}


