
#include "uart.h"                 

volatile int8_t  FifoHead = 0;
volatile int8_t  FifoTail = 0;
volatile uint8_t FifoBuff[FIFO_SIZE];

/*
*��  �ܣ�����uartģ��,�򿪴���ͨ�Ź���
*/
void UartInit(void)
{
    /*uart3*/	
	PINSEL_CFG_Type 	 PinCfg_GPIO;		
  	UART_CFG_Type 	UARTConfigStruct;		 
	
	PinCfg_GPIO.Portnum 	= 0;
	PinCfg_GPIO.Funcnum		= 2;
	PinCfg_GPIO.Pinmode		= PINSEL_PINMODE_PULLUP;
	PinCfg_GPIO.OpenDrain	= PINSEL_PINMODE_NORMAL;
	PinCfg_GPIO.Pinnum		= 0; //TXD3
	PINSEL_ConfigPin(&PinCfg_GPIO);
	PinCfg_GPIO.Pinnum		= 1; //RXD3
	PINSEL_ConfigPin(&PinCfg_GPIO);

	UARTConfigStruct.Baud_rate = 115200;						    /* Baud rate = 115200  */
	UARTConfigStruct.Databits = UART_DATABIT_8;						/* 8 bit */
	UARTConfigStruct.Parity = UART_PARITY_NONE;						/* EVEN PARITY */
	UARTConfigStruct.Stopbits = UART_STOPBIT_1;						/* 1 stop bit */
	UART_Init(LPC_UART3, &UARTConfigStruct);
	UART_TxCmd(LPC_UART3, ENABLE);									/* Enable transmission on UART TxD pin */
	
	UART_IntConfig(LPC_UART3, UART_INTCFG_RBR, ENABLE);
	NVIC_EnableIRQ(UART3_IRQn);
	NVIC_SetPriority(UART3_IRQn,1);
	
    /*uart1*/
	PinCfg_GPIO.Portnum 	= 2;
	PinCfg_GPIO.Funcnum		= 2;
	PinCfg_GPIO.Pinmode		= PINSEL_PINMODE_PULLUP;
	PinCfg_GPIO.OpenDrain	= PINSEL_PINMODE_NORMAL;
	PinCfg_GPIO.Pinnum		= 0; //TXD1
	PINSEL_ConfigPin(&PinCfg_GPIO);
	PinCfg_GPIO.Pinnum		= 1; //RXD1
	PINSEL_ConfigPin(&PinCfg_GPIO);

	UARTConfigStruct.Baud_rate = 115200;						    /* Baud rate = 115200  */
	UARTConfigStruct.Databits = UART_DATABIT_8;						/* 8 bit */
	UARTConfigStruct.Parity = UART_PARITY_NONE;						/* EVEN PARITY */
	UARTConfigStruct.Stopbits = UART_STOPBIT_1;						/* 1 stop bit */
  	UART_Init((LPC_UART_TypeDef*)LPC_UART1, &UARTConfigStruct);
	UART_TxCmd((LPC_UART_TypeDef*)LPC_UART1, ENABLE);			    /* Enable transmission on UART TxD pin */

	return;
}

/*
��  �ܣ�����3�����жϴ���
*/
void UART3_IRQHandler(void)
{
	uint8_t IIRValue;
	uint8_t Err = Err;
	uint8_t RecByte;

	IIRValue = LPC_UART3->IIR;
 	IIRValue >>= 1;	                       //�����жϱ�־IIR�жϹ���λ
  	IIRValue &= 0x07;                      //����0x07���õ��жϱ�־

	switch(IIRValue)
 	{
		case	IIR_RLS:                   //��״̬�ж�
				break;

		case	IIR_RDA:                   //����������Ч�жϱ�־λ
				RecByte = LPC_UART3->RBR;  //��ȡһ����Ч���ݵ����ջ�����
		 		FifoWriteOneByte(RecByte); //���յ��ֽ�д��fifobuf
				break;

		case	IIR_CTI:                   //�ַ���ʱָʾ�жϱ�־λ	
				break;
				
		case	IIR_THRE:                  //���ͱ��ּĴ����ձ�־λ
				break;

		default: 
				break;
  	}

	return;
}

/*
��  �ܣ�����3����ֽ�
*/
void UART3SendData(uint8_t byte) 
{
    LPC_UART3->THR = byte;	
		while((LPC_UART3->LSR & 0x40)==0); 

	return;
}

/*
��  �ܣ�����1����ֽ�
*/
void UART1SendData(uint8_t byte) 
{
    LPC_UART1->THR = byte; 	
		while((LPC_UART1->LSR & 0x40)==0); 
}

/*
��  �ܣ������յ��ֽ������Ŷӣ����뻺����
*/
int32_t FifoWriteOneByte(uint8_t InputChar)
{
	if((FifoHead + 1)%FIFO_SIZE == FifoTail)
	{
		return -1;
	}
	FifoBuff[FifoHead] = InputChar;
	FifoHead = (FifoHead + 1)%FIFO_SIZE;
	
	return 0;
}



