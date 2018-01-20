#ifndef _SPI_H_
#define _SPI_H_

#include "lpc17xx_ssp.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_gpio.h"

#define SSP0 1
#define SSP1 1

void SPIInit(void);
uint8_t SPIReadOneByte(LPC_SSP_TypeDef* SSPx);
void SPIWriteOneByte(LPC_SSP_TypeDef* SSPx,uint8_t DataBuffer);

#endif




