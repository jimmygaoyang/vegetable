#ifndef _SPI_H
#define _SPI_H 


#ifdef __cplusplus
 extern "C" {
#endif

#define MODE_8_BITS_ 0
#define MODE_16_BITS_ 1


#include "stm32f10x.h"
int SPI1Init(void);
void SetSpiDataLen(int mode);
unsigned char SPI1WriteReadByte(unsigned char TxData);
unsigned int SPI1WriteRead2Byte(int TxData);
void SPI1Enable(void);
void SPI1Disable(void);


#ifdef __cplusplus
}
#endif

#endif






