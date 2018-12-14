#include "LED.h"
#include "stm32f0xx_gpio.h"

#define Led_Val Led3*0x08+Led2*0x10+Led1*0x20

uint8_t Led1,Led2,Led3;
uint8_t Led_Mode;
uint8_t Led_Trig;

void LED_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	 RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE);

  /* ≈‰÷√LEDœ‡”¶“˝Ω≈PB1*/
  GPIO_InitStructure.GPIO_Pin =GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_WriteBit(GPIOA,GPIO_Pin_4,Bit_RESET);
	
	
}



void LED_Set(uint8_t mode)
{
	Led_Mode=mode;
	if(Led_Mode)
	{
		GPIO_WriteBit(GPIOA,GPIO_Pin_3,Bit_SET);
	}
	else
	{
		GPIO_WriteBit(GPIOA,GPIO_Pin_3,Bit_RESET);
	}
}
