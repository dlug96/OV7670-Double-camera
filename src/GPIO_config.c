#include "GPIO_config.h"


void SignalConfig1(void){
	GPIO_InitTypeDef VsyncHref;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	VsyncHref.GPIO_Mode = GPIO_Mode_IN;
	VsyncHref.GPIO_OType = GPIO_OType_OD;
	VsyncHref.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;		//PB0 - HREF, PB1 - VSYNC
	VsyncHref.GPIO_PuPd = GPIO_PuPd_NOPULL;
	VsyncHref.GPIO_Speed = GPIO_High_Speed;

	GPIO_Init(GPIOB, &VsyncHref);

	EXTI_InitTypeDef extiVsync;
	EXTI_InitTypeDef extiHref;

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource0);
	EXTI_StructInit(&extiHref);
	extiHref.EXTI_Line = EXTI_Line0;
	extiHref.EXTI_LineCmd = ENABLE;
	extiHref.EXTI_Mode = EXTI_Mode_Interrupt;
	extiHref.EXTI_Trigger = EXTI_Trigger_Rising;

	EXTI_Init(&extiHref);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource1);
	EXTI_StructInit(&extiVsync);
	extiVsync.EXTI_Line = EXTI_Line1;
	extiVsync.EXTI_LineCmd = ENABLE;
	extiVsync.EXTI_Mode = EXTI_Mode_Interrupt;
	extiVsync.EXTI_Trigger = EXTI_Trigger_Falling;

	EXTI_Init(&extiVsync);



	NVIC_InitTypeDef nvicHref;

	nvicHref.NVIC_IRQChannel = EXTI0_IRQn;
	nvicHref.NVIC_IRQChannelPreemptionPriority = 0x01;
	nvicHref.NVIC_IRQChannelSubPriority = 0x01;
	nvicHref.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvicHref);

	NVIC_InitTypeDef nvicVsync;

	nvicVsync.NVIC_IRQChannel = EXTI1_IRQn;
	nvicVsync.NVIC_IRQChannelPreemptionPriority = 0x00;
	nvicVsync.NVIC_IRQChannelSubPriority = 0x00;
	nvicVsync.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvicVsync);

}

void SignalConfig2(void){
	GPIO_InitTypeDef VsyncHref;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	VsyncHref.GPIO_Mode = GPIO_Mode_IN;
	VsyncHref.GPIO_OType = GPIO_OType_OD;
	VsyncHref.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3;		//PB2 - HREF, PB3 - VSYNC
	VsyncHref.GPIO_PuPd = GPIO_PuPd_NOPULL;
	VsyncHref.GPIO_Speed = GPIO_High_Speed;

	GPIO_Init(GPIOB, &VsyncHref);

	EXTI_InitTypeDef extiVsync;
	EXTI_InitTypeDef extiHref;

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource2);
	EXTI_StructInit(&extiHref);
	extiHref.EXTI_Line = EXTI_Line2;
	extiHref.EXTI_LineCmd = ENABLE;
	extiHref.EXTI_Mode = EXTI_Mode_Interrupt;
	extiHref.EXTI_Trigger = EXTI_Trigger_Rising;

	EXTI_Init(&extiHref);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource3);
	EXTI_StructInit(&extiVsync);
	extiVsync.EXTI_Line = EXTI_Line3;
	extiVsync.EXTI_LineCmd = ENABLE;
	extiVsync.EXTI_Mode = EXTI_Mode_Interrupt;
	extiVsync.EXTI_Trigger = EXTI_Trigger_Falling;

	EXTI_Init(&extiVsync);



	NVIC_InitTypeDef nvicHref;

	nvicHref.NVIC_IRQChannel = EXTI2_IRQn;
	nvicHref.NVIC_IRQChannelPreemptionPriority = 0x01;
	nvicHref.NVIC_IRQChannelSubPriority = 0x01;
	nvicHref.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvicHref);

	NVIC_InitTypeDef nvicVsync;

	nvicVsync.NVIC_IRQChannel = EXTI3_IRQn;
	nvicVsync.NVIC_IRQChannelPreemptionPriority = 0x00;
	nvicVsync.NVIC_IRQChannelSubPriority = 0x00;
	nvicVsync.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvicVsync);

}

void DataConfig1(void){
	GPIO_InitTypeDef dataPins;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);

	dataPins.GPIO_Mode = GPIO_Mode_IN;
	dataPins.GPIO_OType = GPIO_OType_OD;
	dataPins.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	dataPins.GPIO_PuPd = GPIO_PuPd_NOPULL;
	dataPins.GPIO_Speed = GPIO_High_Speed;

	GPIO_Init(GPIOC, &dataPins);
}

void DataConfig2(void){
	GPIO_InitTypeDef dataPins;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);

	dataPins.GPIO_Mode = GPIO_Mode_IN;
	dataPins.GPIO_OType = GPIO_OType_OD;
	dataPins.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	dataPins.GPIO_PuPd = GPIO_PuPd_NOPULL;
	dataPins.GPIO_Speed = GPIO_High_Speed;

	GPIO_Init(GPIOD, &dataPins);
}
