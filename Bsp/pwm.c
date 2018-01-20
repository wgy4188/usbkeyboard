#include "pwm.h"

float Frequence[21]= {1, 2.709, 5.419, 13.547, 27.094, 40.640, 54.187, 67.734, 81.281, 94.827, 108.347, 121.921, 135.468, 149.014, 162.561, 176.108, 189.655, 203.201, 216.748, 230.295, 243.841};
uint8_t pwm_flag=0;

void PWMInit(void)
{
	/*ʹ�ù̼���api*/
	PINSEL_CFG_Type 	 PinCfg_GPIO;		
	PWM_MATCHCFG_Type	 PWMMatch_Struct;
	PWM_TIMERCFG_Type	 PWMCfg_Struct;

	PinCfg_GPIO.Portnum 	= 3;
	PinCfg_GPIO.Funcnum		= 3;
	PinCfg_GPIO.Pinmode		= PINSEL_PINMODE_PULLUP;
	PinCfg_GPIO.OpenDrain	= PINSEL_PINMODE_NORMAL;
	PinCfg_GPIO.Pinnum		= 26; //pwm1.3
	PINSEL_ConfigPin(&PinCfg_GPIO);

	PWMCfg_Struct.PrescaleOption = PWM_TIMER_PRESCALE_TICKVAL;
	PWMCfg_Struct.PrescaleValue = 2;
	PWM_Init(LPC_PWM1, PWM_MODE_TIMER, &PWMCfg_Struct);//��ʼ��

	PWMMatch_Struct.MatchChannel = 0;
	PWMMatch_Struct.ResetOnMatch = ENABLE;
	PWMMatch_Struct.IntOnMatch = DISABLE;
	PWMMatch_Struct.StopOnMatch = DISABLE;
	PWM_ConfigMatch(LPC_PWM1,&PWMMatch_Struct);	//����ƥ��Ĵ���0
	PWM_MatchUpdate(LPC_PWM1,0,12500,PWM_MATCH_UPDATE_NOW);

	PWM_ChannelConfig(LPC_PWM1,3,PWM_CHANNEL_SINGLE_EDGE);//ͨ��3������ģʽ
	PWMMatch_Struct.MatchChannel = 3;
	PWMMatch_Struct.ResetOnMatch = DISABLE;
	PWMMatch_Struct.IntOnMatch = DISABLE;
	PWMMatch_Struct.StopOnMatch = DISABLE;
	PWM_ConfigMatch(LPC_PWM1,&PWMMatch_Struct);	//����ƥ��Ĵ���3
	PWM_MatchUpdate(LPC_PWM1,3,6250,PWM_MATCH_UPDATE_NOW);

	PWM_ChannelCmd(LPC_PWM1,3,ENABLE);//ʹ��ͨ��3PWM����
	PWM_ResetCounter(LPC_PWM1);

	PWM_CounterCmd(LPC_PWM1, DISABLE);
	PWM_Cmd(LPC_PWM1, DISABLE);
	
	pwm_flag=0;	//��ʼ��PWM�����������

	return;
}

/*
*��  �ܣ����õ�����Ƶ��
*��  ����1.Ƶ�ʵ�λ 1~20
*/
void SetPMWFreq(uint8_t level)
{
	float value = Frequence[level];//�����ٶȵ�λѡ��Ƶ��
	PWM_MatchUpdate(LPC_PWM1,0,(uint32_t)(12500/value),PWM_MATCH_UPDATE_NOW);//����Ƶ��
	PWM_MatchUpdate(LPC_PWM1,3,(uint32_t)(6250/value),PWM_MATCH_UPDATE_NOW); //����ռ�ձ�

	return;
}

/*
*��  �ܣ�ֹͣ�������
*/
void StopPWM(void)
{
	if(pwm_flag==1)
	{
		PWM_Cmd(LPC_PWM1, DISABLE); 
		PWM_CounterCmd(LPC_PWM1, DISABLE);
	 	PWM_ResetCounter(LPC_PWM1);

		pwm_flag = 0;
	}

	return;
}

/*
*��  �ܣ���ʼ�������
*/
void StartPWM(void)
{
	if(pwm_flag == 0)
	{
		PWM_CounterCmd(LPC_PWM1, ENABLE);	
		PWM_Cmd(LPC_PWM1, ENABLE);

		pwm_flag = 1;
	}

	return;
}


