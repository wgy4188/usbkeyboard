#ifndef _ADC_H_
#define _ADC_H_

#include "lpc17xx_adc.h"
#include "lpc17xx_pinsel.h"

void ADCInit(void);
void StartADC(uint8_t ch);
void StopADC(uint8_t ch);
uint16_t GetADCData(uint8_t ch);

#endif 

