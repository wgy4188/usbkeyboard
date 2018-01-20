#include "timer.h"
#include "uart.h"

/*��ʱֵ*/
volatile uint32_t timer_value=0;

/*
*��  �ܣ�����ʹ�ö�ʱ��
*/
void TimerInit(void)
{
		TIM_TIMERCFG_Type TimerCfgStruct;
		TIM_MATCHCFG_Type TimerMatchCfgStruct;
	
		TimerCfgStruct.PrescaleOption=TIM_PRESCALE_TICKVAL;
		TimerCfgStruct.PrescaleValue=1;
		TIM_Init(LPC_TIM0, TIM_TIMER_MODE, &TimerCfgStruct);
	
		TimerMatchCfgStruct.MatchChannel=0;
		TimerMatchCfgStruct.MatchValue=25000; //1ms
		TimerMatchCfgStruct.IntOnMatch=ENABLE;
		TimerMatchCfgStruct.ResetOnMatch=ENABLE;
		TimerMatchCfgStruct.StopOnMatch=DISABLE;
		TIM_ConfigMatch(LPC_TIM0,&TimerMatchCfgStruct);

 		NVIC_SetPriority(TIMER0_IRQn,2);
		NVIC_EnableIRQ(TIMER0_IRQn);

		TIM_ResetCounter(LPC_TIM0);
		TIM_Cmd(LPC_TIM0,DISABLE);

		return;
}

void TIMER0_IRQHandler()
{
		TIM_ClearIntPending(LPC_TIM0,TIM_MR0_INT); //һ��Ҫ�ǵ�����жϱ�־
		timer_value++;
		UART3SendData('0');
		if(timer_value>600000)//����10min
		{
			 timer_value=0;
		}
		return;
}

/*
*��  �ܣ�������ʼ��ʱ
*/
void StartTimer(void)
{
		TIM_ResetCounter(LPC_TIM0);
		TIM_Cmd(LPC_TIM0,ENABLE);
	
		return;
}

/*
*��  �ܣ�ֹͣ��ʱ
*/
void StopTimer(void)
{
		TIM_Cmd(LPC_TIM0,DISABLE);
	  
	    return;
}

/*
*��  �ܣ���λ��ʱ��
*/
void ResetTimer(void)
{
		timer_value=0;
	 
		return;
}






