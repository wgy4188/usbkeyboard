#include "gpio.h"

/*
*��    �ܣ�����gpio����
*���������	1�������� GPIO_INTPUT (gpio����)/GPIO_OUTPUT	(gpio���)
						2���˿ںţ�0,1,2...
						3�����źţ�0~32������ͼֽ���ã�
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
*��    �ܣ�����gpio�����ƽ
*���������
		   1���˿ںţ�0,1,2...
		   2�����źţ�0~32������ͼֽ���ã�
		   3����ƽֵ:0/1
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
*��    �ܣ���ȡ����˿���������ֵ
*���������
		   1���˿ںţ�0,1,2...
*�� �� ֵ��32bit����ֵ����ʾ�˿���������״̬
*/
int32_t GetAllPinValue(uint8_t GrpNum)
{
	int32_t PinValue = 0;

	PinValue = FIO_ReadValue(GrpNum);

	return PinValue;
}

/*
*��    �ܣ���ȡ�������ŵ�ƽֵ
*���������
		   1���˿ںţ�0,1,2...
		   2�����źţ�0~32
*�� �� ֵ��32bit����ֵ��0�ͣ� 1�ߣ� -1����
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
*��    �ܣ���ʼ���õ�GPIO
*/
void GPIOInit(void)
{ 
   //input
   

   //output
   

	return;
}


