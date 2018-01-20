#ifndef __UART_H__
#define	__UART_H__

#include "lpc17xx_pinsel.h"  
#include "lpc17xx_uart.h" 

#define FIFO_SIZE 256

#define IER_RBR		0x01
#define IER_THRE	0x02
#define IER_RLS		0x04

#define IIR_PEND	0x01
#define IIR_RLS		0x03
#define IIR_RDA		0x02
#define IIR_CTI		0x06
#define IIR_THRE	0x01

#define LSR_RDR		0x01
#define LSR_OE		0x02
#define LSR_PE		0x04
#define LSR_FE		0x08
#define LSR_BI		0x10
#define LSR_THRE	0x20
#define LSR_TEMT	0x40
#define LSR_RXFE	0x80 

extern volatile int8_t  FifoHead;
extern volatile int8_t  FifoTail;
extern volatile uint8_t FifoBuff[FIFO_SIZE];

void UartInit(void);
void UART3SendData(uint8_t byte); 
void UART1SendData(uint8_t byte); 
int32_t FifoWriteOneByte(uint8_t InputChar);



#endif

