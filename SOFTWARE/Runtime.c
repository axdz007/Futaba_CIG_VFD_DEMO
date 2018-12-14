/*			FUTABA VFD���Գ���				*/
/*				2018-12-15						*/
/*					GTXYJ								*/
/*				SW:beta 0.4						*/

/*��Ļ��ʼ������λ��FUTABA_VFD.c	*/
/*	Last Build:2018/12/15 00:17	*/



#include "Runtime.h"
#include "delay.h"
#include "STF030_Gpio.h"
#include "STF030_Timer.h"
#include "STF030_Rcc.h"
#include "LED.h"
#include "FUTABA_VFD.h"


void Runtime_Init(void)//��ʼ������
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

void Runtime_Running(void)//��ѭ��
{

while(1);
}


