#include "STF030_Rcc.h"

void Rcc_Init_Hsi(void)
{
	__IO uint32_t StartUpCounter = 0, HSIStatus = 0;
  
  /* SYSCLK, HCLK, PCLK configuration ----------------------------------------*/
/* Enable HSI*/ //使能内部时钟
  RCC->CR |= ((uint32_t)RCC_CR_HSION);

  /* Wait till HSI is ready and if Time out is reached exit */ //等待内部时钟起振
  do
  {
   HSIStatus = RCC->CR & RCC_CR_HSIRDY;
    StartUpCounter++;  
  } while((HSIStatus== 0) && (StartUpCounter != HSI_STARTUP_TIMEOUT));

  if ((RCC->CR & RCC_CR_HSIRDY) != RESET)
  {
  HSIStatus = (uint32_t)0x01;
  }
  else  
  {
  HSIStatus = (uint32_t)0x00;
  }  

  if (HSIStatus == (uint32_t)0x01)
  {
/* Enable Prefetch Buffer and set Flash Latency */ //flash总线时钟使能
    FLASH->ACR = FLASH_ACR_PRFTBE | FLASH_ACR_LATENCY;

/* HCLK = SYSCLK *///外设AHB总线时钟等于系统时钟
    RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;
      
/* PCLK = HCLK *///外设APB总线时钟等于系统时钟
    RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE_DIV1;

   /* PLL configuration = HSI/2 * 12= 48 MHz */
    RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLSRC | RCC_CFGR_PLLMULL));
    RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSI_Div2 | RCC_CFGR_PLLMULL12); //RC时钟2分频后 进行12倍频
            
/* Enable PLL *///使能锁相环倍频开关 
    RCC->CR |= RCC_CR_PLLON;

/* Wait till PLL is ready *///等待锁相环就绪 
    while((RCC->CR & RCC_CR_PLLRDY) == 0)
    {
    }

/* Select PLL as system clock source *///选择锁相环输出时钟作为系统时钟 
    RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
    RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;    

/* Wait till PLL is used as system clock source *///等待锁相环输出时钟已经成为系统时钟 
    while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)RCC_CFGR_SWS_PLL)
    {
    }
  }
  else
  { /* If HSI fails to start-up, the application will have wrong clock 
         configuration. User can add here some code to deal with this error */
                
  }  
}

