/**
 * @file    source.c
 * @brief   电源
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

#include "source_in.h"


/**
 * @brief   电源打开
 */
inline void SOURCE_On(void)
{
	GPIO_SetBits(SOURCE_GPIO, SOURCE_PIN);
}


/**
 * @brief   电源关闭
 */
inline void SOURCE_Off(void)
{
	GPIO_ResetBits(SOURCE_GPIO, SOURCE_PIN);
}


/**
 * @brief   电源初始化
 */
void SOURCE_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(SOURCE_RCC, ENABLE);

	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_InitStructure.GPIO_Pin   = SOURCE_PIN;
	GPIO_Init(SOURCE_GPIO, &GPIO_InitStructure);

	SOURCE_Off();
}
