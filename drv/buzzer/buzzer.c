/**
 * @file    buzzer.c
 * @brief   蜂鸣器
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

#include "buzzer_in.h"


/**
 * @brief   蜂鸣器打开
 */
inline void BUZZER_On(void)
{
	GPIO_SetBits(BUZZER_GPIO, BUZZER_PIN);
}


/**
 * @brief   蜂鸣器关闭
 */
inline void BUZZER_Off(void)
{
	GPIO_ResetBits(BUZZER_GPIO, BUZZER_PIN);
}


/**
 * @brief   蜂鸣器初始化
 */
void BUZZER_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(BUZZER_RCC, ENABLE);
	// 因为是和JTRST复用的
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);

	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	// 这边使用AF_PP，就不能控制蜂鸣器打开和关闭了，
	// AF_PP应该链接的是外设的
//	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_InitStructure.GPIO_Pin   = BUZZER_PIN;
	GPIO_Init(BUZZER_GPIO, &GPIO_InitStructure);

	BUZZER_Off();
}
