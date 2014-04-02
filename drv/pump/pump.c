/**
 * @file    pump.c
 * @brief   泵
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

#include "pump_in.h"


/**
 * @brief   泵打开
 */
inline void PUMP_On(void)
{
#ifdef CONFIG_USING_PUMP_PIN
	GPIO_SetBits(PUMP_GPIO, PUMP_PIN);
#endif
}


/**
 * @brief   泵关闭
 */
inline void PUMP_Off(void)
{
#ifdef CONFIG_USING_PUMP_PIN
	GPIO_ResetBits(PUMP_GPIO, PUMP_PIN);
#endif
}


/**
 * @brief   泵初始化
 */
void PUMP_Init(void)
{
#ifdef CONFIG_USING_PUMP_PIN
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(PUMP_RCC, ENABLE);

	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_InitStructure.GPIO_Pin   = PUMP_PIN;
	GPIO_Init(PUMP_GPIO, &GPIO_InitStructure);

	PUMP_Off();
#endif
}
