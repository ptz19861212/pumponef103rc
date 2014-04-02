/**
 * @file    vibration.c
 * @brief   振动泵
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

#include "vibration_in.h"


/**
 * @brief   蜂鸣器打开
 */
inline void VIBRATION_On(void)
{
	GPIO_SetBits(VIBRATION_GPIO, VIBRATION_PIN);
}


/**
 * @brief   蜂鸣器关闭
 */
inline void VIBRATION_Off(void)
{
	GPIO_ResetBits(VIBRATION_GPIO, VIBRATION_PIN);
}


/**
 * @brief   蜂鸣器初始化
 */
void VIBRATION_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(VIBRATION_RCC, ENABLE);

	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_InitStructure.GPIO_Pin   = VIBRATION_PIN;
	GPIO_Init(VIBRATION_GPIO, &GPIO_InitStructure);

	VIBRATION_Off();
}
