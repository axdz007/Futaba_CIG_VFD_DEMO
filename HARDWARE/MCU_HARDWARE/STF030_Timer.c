#include "stm32f0xx.h"
#include "stm32f0xx_tim.h"
#include "STF030_Timer.h"

void Tim3_Init(void)
{
	
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef                NVIC_InitStructure;
	
	
	TIM_DeInit(TIM3);//ʹ��ȱʡֵ��ʼ��TIM����Ĵ���
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	TIM_TimeBaseStructure.TIM_Prescaler=10-1;//ʱ��Ԥ��Ƶ��Ϊ48000
	TIM_TimeBaseStructure.TIM_Period=375-1;//�Զ���װ�ؼĴ���ֵΪ375
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
	
	TIM_ClearFlag(TIM3,TIM_FLAG_Update);
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	
	TIM_Cmd(TIM3,ENABLE);
	
	
	 NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn; //��ʱ��3�ж�
   NVIC_InitStructure.NVIC_IRQChannelPriority = 0; //���ȼ�0
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);
	
	
	
}


void Tim14_Init(void)
{
	
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef                NVIC_InitStructure;
	
	
	TIM_DeInit(TIM14);//1KHZ��ʱ��
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);
	
	TIM_TimeBaseStructure.TIM_Prescaler=4800-1;//ʱ��Ԥ��Ƶ��Ϊ48000
	TIM_TimeBaseStructure.TIM_Period=10-1;//�Զ���װ�ؼĴ���ֵΪ1
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM14,&TIM_TimeBaseStructure);
	
	TIM_ClearFlag(TIM14,TIM_FLAG_Update);
	
	TIM_ITConfig(TIM14,TIM_IT_Update,ENABLE);
	
	TIM_Cmd(TIM14,ENABLE);
	
	
	 NVIC_InitStructure.NVIC_IRQChannel = TIM14_IRQn; //��ʱ��3�ж�
   NVIC_InitStructure.NVIC_IRQChannelPriority = 1; //���ȼ�0
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);
	
	
	
}



void Tim1_Init(void)
{
				TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
				
				
				TIM_OCInitTypeDef        TIM_OCInitStructure;
				TIM_BDTRInitTypeDef TIM_BDTRInitStructure; 
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
				TIM_DeInit(TIM1);

				TIM_TimeBaseStructure.TIM_Prescaler =4-1; 
				TIM_TimeBaseStructure.TIM_Period =256;     
				TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
				TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
				TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); 
				
				

				TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
				TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable ;//TIM_OutputState_Enable; //PWM���ʹ��λ
				TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable ;//TIM_OutputNState_Enable; //����PWM���ʹ��λ
				TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  
				TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
				TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
				TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
				
				
				TIM_OCInitStructure.TIM_Pulse = 0; //��ռ�ձ�ֵ
				TIM_OC1Init(TIM1, &TIM_OCInitStructure);//ʹ��Ƶ��1����
 
				TIM_OCInitStructure.TIM_Pulse = 0; //��ռ�ձ�ֵ
				TIM_OC2Init(TIM1, &TIM_OCInitStructure);//ʹ��Ƶ��2����
 
				TIM_OCInitStructure.TIM_Pulse = 0; //��ռ�ձ�ֵ
				TIM_OC3Init(TIM1, &TIM_OCInitStructure);//ʹ��Ƶ��3����
				TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
				TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
				TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable); 
				
				
				TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;
				TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;
				TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_OFF;
				TIM_BDTRInitStructure.TIM_DeadTime = 5;
				TIM_BDTRInitStructure.TIM_Break = TIM_Break_Disable;
				TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_High;
				TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Disable;
				TIM_BDTRConfig(TIM1, &TIM_BDTRInitStructure);

				
				TIM_CtrlPWMOutputs(TIM1, ENABLE); 

     TIM_Cmd(TIM1, ENABLE);  //ʹ��TIM1
	

}

