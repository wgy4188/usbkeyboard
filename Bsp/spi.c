
#include "spi.h"

void SPIInit(void)
{
	PINSEL_CFG_Type PinCfg_GPIO;   
	SSP_CFG_Type SSPConfigStruct;

#if SSP0  //LED SSP

	PinCfg_GPIO.Portnum 	= PINSEL_PORT_0;
	PinCfg_GPIO.Funcnum		= PINSEL_FUNC_2;
	PinCfg_GPIO.Pinmode		= PINSEL_PINMODE_PULLUP;
	PinCfg_GPIO.OpenDrain	= PINSEL_PINMODE_NORMAL;
	PinCfg_GPIO.Pinnum		= PINSEL_PIN_15; //SCK 
	PINSEL_ConfigPin(&PinCfg_GPIO);
	PinCfg_GPIO.Pinmode		= PINSEL_PINMODE_TRISTATE;
	PinCfg_GPIO.OpenDrain	= PINSEL_PINMODE_OPENDRAIN;
	PinCfg_GPIO.Pinnum		= PINSEL_PIN_17; //MISO
	PINSEL_ConfigPin(&PinCfg_GPIO);
	PinCfg_GPIO.Pinmode		= PINSEL_PINMODE_PULLUP;
	PinCfg_GPIO.OpenDrain	= PINSEL_PINMODE_NORMAL;
	PinCfg_GPIO.Pinnum		= PINSEL_PIN_18; //MOSI 
	PINSEL_ConfigPin(&PinCfg_GPIO);

	PinCfg_GPIO.Portnum 	= PINSEL_PORT_0;
	PinCfg_GPIO.Funcnum		= PINSEL_FUNC_0;
	PinCfg_GPIO.Pinmode		= PINSEL_PINMODE_PULLUP;
	PinCfg_GPIO.OpenDrain	= PINSEL_PINMODE_NORMAL;
	PinCfg_GPIO.Pinnum		= PINSEL_PIN_4;	//CS 
	PINSEL_ConfigPin(&PinCfg_GPIO);

	GPIO_SetDir(PINSEL_PORT_0, 1<<PINSEL_PIN_4, 1);	 
	GPIO_ClearValue(PINSEL_PORT_0,1<<PINSEL_PIN_4);	

	SSPConfigStruct.Databit     = SSP_DATABIT_8;
	SSPConfigStruct.CPHA        = SSP_CPHA_FIRST;
	SSPConfigStruct.CPOL        = SSP_CPOL_HI;
	SSPConfigStruct.Mode        = SSP_MASTER_MODE;
	SSPConfigStruct.FrameFormat = SSP_FRAME_SPI;
	SSPConfigStruct.ClockRate   = 1000000;

	SSP_Init(LPC_SSP0, &SSPConfigStruct);
	SSP_Cmd(LPC_SSP0, ENABLE); 

#endif

#if SSP1 //Encode SSP
	
	PinCfg_GPIO.Portnum 	= PINSEL_PORT_0;
	PinCfg_GPIO.Funcnum		= PINSEL_FUNC_2;
	PinCfg_GPIO.Pinmode		= PINSEL_PINMODE_PULLUP;
	PinCfg_GPIO.OpenDrain	= PINSEL_PINMODE_NORMAL;
	PinCfg_GPIO.Pinnum		= PINSEL_PIN_7;//SCK	
	PINSEL_ConfigPin(&PinCfg_GPIO);
	PinCfg_GPIO.Pinmode		= PINSEL_PINMODE_TRISTATE;
	PinCfg_GPIO.OpenDrain	= PINSEL_PINMODE_OPENDRAIN;
	PinCfg_GPIO.Pinnum		= PINSEL_PIN_8;//MISO	
	PINSEL_ConfigPin(&PinCfg_GPIO);
	PinCfg_GPIO.Pinmode		= PINSEL_PINMODE_PULLUP;
	PinCfg_GPIO.OpenDrain	= PINSEL_PINMODE_NORMAL;
	PinCfg_GPIO.Pinnum		= PINSEL_PIN_9;//MOSI 
	PINSEL_ConfigPin(&PinCfg_GPIO);	 
		
	PinCfg_GPIO.Portnum 	= PINSEL_PORT_0;
	PinCfg_GPIO.Funcnum		= PINSEL_FUNC_0;
	PinCfg_GPIO.Pinmode		= PINSEL_PINMODE_PULLUP;
	PinCfg_GPIO.OpenDrain	= PINSEL_PINMODE_NORMAL;
	PinCfg_GPIO.Pinnum		= PINSEL_PIN_5;	//CS
	PINSEL_ConfigPin(&PinCfg_GPIO);

	
	GPIO_SetDir(PINSEL_PORT_0, 1<<PINSEL_PIN_5, 1);			
	GPIO_ClearValue(PINSEL_PORT_0, 0<<PINSEL_PIN_5);	

	SSPConfigStruct.Databit     = SSP_DATABIT_8;
	SSPConfigStruct.CPHA        = SSP_CPHA_FIRST;
	SSPConfigStruct.CPOL        = SSP_CPOL_HI;
	SSPConfigStruct.Mode        = SSP_MASTER_MODE;
	SSPConfigStruct.FrameFormat = SSP_FRAME_SPI;
	SSPConfigStruct.ClockRate   = 1000000;
	
	SSP_Init(LPC_SSP1, &SSPConfigStruct);
	SSP_Cmd(LPC_SSP1, ENABLE);

#endif
}


uint8_t SPIReadOneByte(LPC_SSP_TypeDef* SSPx)
{
	uint8_t retValue = 0;
	
	SSP_SendData(SSPx, 0x00);
	while ( !(SSPx->SR & SSP_STAT_RXFIFO_NOTEMPTY) );
	retValue = SSP_ReceiveData(SSPx);

	return (retValue);
}


void SPIWriteOneByte(LPC_SSP_TypeDef* SSPx,uint8_t DataBuffer)
{
	SSP_SendData(SSPx, DataBuffer);
	while (!( (SSPx)->SR & SSP_STAT_RXFIFO_NOTEMPTY ));
	SSP_ReceiveData(SSPx);
}
























