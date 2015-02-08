//--------------------------------------------------------------
// File     : I2C1.h
//--------------------------------------------------------------
#ifndef I2C1_H
#define I2C1_H

//--------------------------------------------------------------
// Includes
//--------------------------------------------------------------
#include "stm32f10x.h"

#ifdef __cplusplus
 extern "C" {
#endif
//--------------------------------------------------------------
// Global Functions
//--------------------------------------------------------------
void I2C1_Init(void);
void I2C_start(I2C_TypeDef* I2Cx, unsigned char address, unsigned char direction);
void I2C_stop(I2C_TypeDef* I2Cx);
unsigned char I2C_read_nack(I2C_TypeDef* I2Cx);
unsigned char I2C_read_ack(I2C_TypeDef* I2Cx);
void I2C_write(I2C_TypeDef* I2Cx, unsigned char data);

#ifdef __cplusplus
}
#endif

//--------------------------------------------------------------
#endif // I2C1_H
