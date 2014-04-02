/**
 * @file    led.c
 * @brief   灯
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-08-05 10:27:56 星期一
 * @history (1).2013-08-05 10:27:56 星期一 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#include "led_in.h"


/**
 * @brief   灯打开
 */
inline void LED_On(E_LedPin lPin)
{
	GPIO_SetBits(LED_GPIO, LED_PIN);
}


/**
 * @brief   灯关闭
 */
inline void LED_Off(E_LedPin lPin)
{
	GPIO_ResetBits(LED_GPIO, LED_PIN);
}


/**
 * @brief   灯初始化
 */
void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(LED_RCC, ENABLE);

	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_InitStructure.GPIO_Pin   = LED_PIN;
	GPIO_Init(LED_GPIO, &GPIO_InitStructure);

	LED_Off(LED_PIN_1);
}
