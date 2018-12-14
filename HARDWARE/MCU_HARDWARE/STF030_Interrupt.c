#include "stm32f0xx.h"
#include "STF030_Interrupt.h"
#include "stm32f0xx_tim.h"
#include "LED.h"
#include "FUTABA_VFD.h"
uint16_t Second_Base,Second_Trig;

uint16_t Ms_Base,Ms_Trig;


void TIM3_IRQHandler(void)
{
        
        if(TIM_GetITStatus(TIM3,TIM_IT_Update) != RESET) //溢出中断
        {
            
        }
        TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //清除中断标志位
}

void TIM14_IRQHandler(void)
{
        
        if(TIM_GetITStatus(TIM14,TIM_IT_Update) != RESET) //溢出中断
        {
					

						
					Futaba_VFD_TICK();
	
        }
        TIM_ClearITPendingBit(TIM14,TIM_IT_Update);  //清除中断标志位
}


