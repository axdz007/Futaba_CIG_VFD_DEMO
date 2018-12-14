/*			FUTABA VFD测试程序				*/
/*				2018-12-15						*/
/*					GTXYJ								*/
/*				SW:beta 0.4						*/

/*屏幕初始化函数位于FUTABA_VFD.c	*/
/*	Last Build:2018/12/15 00:17	*/



#include "Runtime.h"
#include "delay.h"
#include "STF030_Gpio.h"
#include "STF030_Timer.h"
#include "STF030_Rcc.h"
#include "LED.h"
#include "FUTABA_VFD.h"


void Runtime_Init(void)//初始化部分
{
	Rcc_Init_Hsi();
	delay_init();
	Gpio_Init();
	//Tim3_Init();
	Tim14_Init();
	//Tim1_Init();
	Futaba_VFD_Init();
	LED_Init();
	
}

void Runtime_Running(void)//主循环
{

while(1);
}


