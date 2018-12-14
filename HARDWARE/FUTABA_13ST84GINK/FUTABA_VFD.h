#ifndef __FUTABA_VFD_H
#define __FUTABA_VFD_H

#include "stm32f0xx.h"

#define VFD_RST_RCC RCC_AHBPeriph_GPIOF
#define VFD_RST_SPEED GPIO_Speed_2MHz
#define VFD_RST_PORT GPIOF
#define VFD_RST_PIN GPIO_Pin_0

#define VFD_CS_RCC RCC_AHBPeriph_GPIOF
#define VFD_CS_SPEED GPIO_Speed_2MHz
#define VFD_CS_PORT GPIOF
#define VFD_CS_PIN GPIO_Pin_1

#define VFD_CLK_RCC RCC_AHBPeriph_GPIOA
#define VFD_CLK_SPEED GPIO_Speed_50MHz
#define VFD_CLK_PORT GPIOA
#define VFD_CLK_PIN GPIO_Pin_9

#define VFD_DIN_RCC RCC_AHBPeriph_GPIOA
#define VFD_DIN_SPEED GPIO_Speed_50MHz
#define VFD_DIN_PORT GPIOA
#define VFD_DIN_PIN GPIO_Pin_10


void Futaba_VFD_TICK(void);
void Futaba_VFD_Init(void);
void vfd_tst(void);


#endif
