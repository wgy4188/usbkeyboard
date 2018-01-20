#include "iic.h"

void IICInit(void)
{
	PINSEL_CFG_Type 	 PinCfg_GPIO;		
	
	PinCfg_GPIO.Portnum 	= 0;
	PinCfg_GPIO.Funcnum		= 1;
	PinCfg_GPIO.Pinmode		= PINSEL_PINMODE_PULLUP;
	PinCfg_GPIO.OpenDrain	= PINSEL_PINMODE_NORMAL;
	PinCfg_GPIO.Pinnum		= 27; //SDA
	PINSEL_ConfigPin(&PinCfg_GPIO);
	PinCfg_GPIO.Pinnum		= 28; //SCL
	PINSEL_ConfigPin(&PinCfg_GPIO);

	I2C_Init(I2C_0, 100000);
	I2C_Cmd(I2C_0, I2C_MASTER_MODE, ENABLE);
	
	return;		
}

void WriteData(uint8_t slave, uint8_t *s, uint32_t num)
{
	I2C_M_SETUP_Type WriteCfg;

	WriteCfg.sl_addr7bit = slave;
	WriteCfg.tx_data = s;
	WriteCfg.tx_length = num;
	WriteCfg.rx_data = NULL;
	WriteCfg.rx_length = 0;
	WriteCfg.retransmissions_max = 3;
	WriteCfg.tx_count = 0;
	WriteCfg.rx_count = 0;
	WriteCfg.retransmissions_count = 0;	
	
	I2C_MasterTransferData(I2C_0, &WriteCfg, I2C_TRANSFER_POLLING);	
	
	return;	
}

void ReadData(uint8_t slave, uint8_t *s, uint32_t num)
{
	I2C_M_SETUP_Type WriteCfg;

	WriteCfg.sl_addr7bit = slave;
	WriteCfg.tx_data = NULL;
	WriteCfg.tx_length = 0;
	WriteCfg.rx_data = s;
	WriteCfg.rx_length = num;
	WriteCfg.retransmissions_max = 3;
	WriteCfg.tx_count = 0;
	WriteCfg.rx_count = 0;
	WriteCfg.retransmissions_count = 0;	
	
	I2C_MasterTransferData(I2C_0, &WriteCfg, I2C_TRANSFER_POLLING);	
	
	return;	
}




