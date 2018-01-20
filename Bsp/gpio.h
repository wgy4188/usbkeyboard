#ifndef __GPIO_H__
#define	__GPIO_H__

#include <stdint.h>
#include "lpc17xx_gpio.h"
#include "lpc17xx_pinsel.h"

enum GPIO_DIR
{
	GPIO_INTPUT,
	GPIO_OUTPUT
};

/*IO操作函数*/
void SetGpioDirect(enum GPIO_DIR Direct, uint8_t GrpNum, uint8_t PinNum);
void SetPinValue(uint8_t GrpNum, uint8_t PinNum, uint8_t Value);
int  GetPinValue(uint8_t GrpNum, uint8_t PinNum);

/*IO应用初始化*/
void GPIOInit(void);


#endif /**End File**/
