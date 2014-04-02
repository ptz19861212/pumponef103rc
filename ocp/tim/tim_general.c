/**
 * @file    tim_general.c
 * @brief   general purpose timers tim2-tim5 tim9-tim14
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-11-28 10:34:29 星期四 
 * @history (1).2013-11-28 10:34:29 星期四 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#include "tim_general_in.h"

/**
 * @brief   rcc config
 */
static void RCC_Configuration(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 | RCC_APB1Periph_TIM3, ENABLE);
}

//#include "stm32f10x_gpio.h"
/**
 * @brief   gpio config
 */
static void GPIO_Configuration(void)
{

}


/**
 * @brief   nvic config
 */
static void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&NVIC_InitStructure);
}


/**
 * @brief   TIM3 中断
 */
void TIM3_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
		StateHandler();
	}
}


/**
 * @brief   general timer config
 */
void TIM_General_Configuration(void)
{
	// rcc config
	RCC_Configuration();
	//DEBUG_Printf("tim_general-rcc-config done \n");

	// gpio config
	GPIO_Configuration();
	//DEBUG_Printf("tim_general-gpio-config done \n");

	// nvic config
	NVIC_Configuration();
	//DEBUG_Printf("tim_general-nvic-config done \n");

	// tim basic config pwm
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCStructure;

	TIM_DeInit(TIM2);

	/* TIM1 configuration ------------------------------------------------------*/
	/* Time Base configuration */
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Period = CONFIG_TIM2_PERIOD;
	TIM_TimeBaseStructure.TIM_Prescaler = CONFIG_TIM2_PRESCALE;
	TIM_TimeBaseStructure.TIM_ClockDivision = CONFIG_TIM2_CLK;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	/* TIM2 channel2 configuration in PWM mode */
	TIM_OCStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCStructure.TIM_Pulse = CONFIG_TIM2_PULSE;
	TIM_OCStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OC2Init(TIM2, &TIM_OCStructure);
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);
	// auto reloaded
	TIM_ARRPreloadConfig(TIM2, ENABLE);
	// internal clock
	TIM_InternalClockConfig(TIM2);
	/* TIM1 counter enable */
	TIM_Cmd(TIM2, ENABLE);

	// tim3 basic config
	TIM_DeInit(TIM3);

	/* TIM1 configuration ------------------------------------------------------*/
	/* Time Base configuration */
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Period = CONFIG_TIM3_PERIOD;
	TIM_TimeBaseStructure.TIM_Prescaler = CONFIG_TIM3_PRESCALE;
	TIM_TimeBaseStructure.TIM_ClockDivision = CONFIG_TIM3_CLK;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	// 清中断标志
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	// 使能中断
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	// auto reloaded
	TIM_ARRPreloadConfig(TIM3, ENABLE);
	// internal clock
	TIM_InternalClockConfig(TIM3);
	/* TIM1 counter enable */
	TIM_Cmd(TIM3, ENABLE);

}
