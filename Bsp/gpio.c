#include "gpio.h"

/*
*功    能：设置gpio方向
*输入参数：	1、可以是 GPIO_INTPUT (gpio输入)/GPIO_OUTPUT	(gpio输出)
						2、端口号：0,1,2...
						3、引脚号：0~32（根据图纸设置）
*/
void SetGpioDirect(enum GPIO_DIR Direct, uint8_t GrpNum, uint8_t PinNum)
{
	if(GPIO_INTPUT == Direct)
	{
		FIO_SetDir(GrpNum, 1<<PinNum, 0);
	}
	else if(GPIO_OUTPUT == Direct)
	{
		FIO_SetDir(GrpNum, 1<<PinNum, 1); 
	}
	
	return;	
}


/*
*功    能：设置gpio输出电平
*输入参数：
		   1、端口号：0,1,2...
		   2、引脚号：0~32（根据图纸设置）
		   3、电平值:0/1
*/
void SetPinValue(uint8_t GrpNum, uint8_t PinNum, uint8_t Value)
{
	if(1 == Value)
	{
		FIO_SetValue(GrpNum,1<<PinNum);
	}
	else if(0 == Value)
	{
		FIO_ClearValue(GrpNum,1<<PinNum);
	}
	
	return;
}

/*
*功    能：获取输入端口所有引脚值
*输入参数：
		   1、端口号：0,1,2...
*返 回 值：32bit长度值，表示端口所有引脚状态
*/
int32_t GetAllPinValue(uint8_t GrpNum)
{
	int32_t PinValue = 0;

	PinValue = FIO_ReadValue(GrpNum);

	return PinValue;
}

/*
*功    能：获取输入引脚电平值
*输入参数：
		   1、端口号：0,1,2...
		   2、引脚号：0~32
*返 回 值：32bit长度值，0低， 1高， -1错误
*/
int32_t GetPinValue(uint8_t GrpNum, uint8_t PinNum)
{
	uint32_t PinMask;

	PinMask = 1<<PinNum;

	switch(GrpNum)
	{
		case 0:
			if((LPC_GPIO0->FIOPIN & PinMask) == PinMask)
			{
				return 1;
			}
			else
			{
				return 0;
			}

		case 1:
			if((LPC_GPIO1->FIOPIN & PinMask) == PinMask)
			{
				return 1;
			}
			else
			{
				return 0;
			}
			
		case 2:
			if((LPC_GPIO2->FIOPIN & PinMask) == PinMask)
			{
				return 1;
			}
			else
			{
				return 0;
			}

		case 3:
			if((LPC_GPIO3->FIOPIN & PinMask) == PinMask)
			{
				return 1;
			}
			else
			{
				return 0;
			}

		case 4:
			if((LPC_GPIO4->FIOPIN & PinMask) == PinMask)
			{
				return 1;
			}
			else
			{
				return 0;
			}

		default:
			break;
	}

	return -1;	
}

/*
*功    能：初始化用到GPIO
*/
void GPIOInit(void)
{ 
   //input
   

   //output
   

	return;
}


