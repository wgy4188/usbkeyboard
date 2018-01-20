#ifndef _IIC_H_
#define _IIC_H_

#include "lpc17xx_pinsel.h"
#include "lpc17xx_i2c.h"

void IICInit(void);
void WriteData(uint8_t slave, uint8_t *s, uint32_t num);
void ReadData(uint8_t slave, uint8_t *s, uint32_t num);

#endif

