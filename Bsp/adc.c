#include "adc.h"

void ADCInit(void)
{
	PINSEL_CFG_Type 	 PinCfg_GPIO;				 
	
	PinCfg_GPIO.Portnum 	= 0;
	PinCfg_GPIO.Funcnum		= 2;
	PinCfg_GPIO.Pinmode		= PINSEL_PINMODE_PULLUP;
	PinCfg_GPIO.OpenDrain	= PINSEL_PINMODE_NORMAL;
	PinCfg_GPIO.Pinnum		= 2; //AD0.7
	PINSEL_ConfigPin(&PinCfg_GPIO);
	PinCfg_GPIO.Pinnum		= 3; //AD0.6
	PINSEL_ConfigPin(&PinCfg_GPIO);

	ADC_Init(LPC_ADC, 5000);
	ADC_StartCmd(LPC_ADC, ADC_START_NOW);
	ADC_ChannelCmd(LPC_ADC, 6 , DISABLE);
	ADC_ChannelCmd(LPC_ADC, 7 , DISABLE);

	return;
}

void StartADC(uint8_t ch)
{
	ADC_ChannelCmd(LPC_ADC, ch , DISABLE);
	
	return;	
}

void StopADC(uint8_t ch)
{
	ADC_ChannelCmd(LPC_ADC, ch , DISABLE);
	
	return;	
}

uint16_t GetADCData(uint8_t ch)
{
	return(ADC_ChannelGetData(LPC_ADC, ch));
}



