/**
 * @file    charge.c
 * @brief   充电
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

#include "charge_in.h"


/**
 * @brief   充电打开
 */
inline void CHARGE_On(void)
{
#ifdef CONFIG_USING_CHARGE_PIN_500MA
	GPIO_SetBits(CHARGE_GPIO, CHARGE_PIN);
#endif
}


/**
 * @brief   充电关闭
 */
inline void CHARGE_Off(void)
{
#ifdef CONFIG_USING_CHARGE_PIN_500MA
	GPIO_ResetBits(CHARGE_GPIO, CHARGE_PIN);
#endif
}


/**
 * @brief   充电检测
 */
E_TrueState CHARGE_Scan(void)
{
	if (GPIO_ReadInputDataBit(CHARGE_IN_GPIO, CHARGE_IN_PIN))
	{
		return E_TRUE;
	}
	else
	{
		return E_FALSE;
	}
}


/**
 * @brief   充电初始化
 */
void CHARGE_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

#ifdef CONFIG_USING_CHARGE_PIN_500MA
	// 充电500ma控制的引脚
	RCC_APB2PeriphClockCmd(CHARGE_RCC, ENABLE);

	// 因为是和JTRST复用的
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);

	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_InitStructure.GPIO_Pin   = CHARGE_PIN;
	GPIO_Init(CHARGE_GPIO, &GPIO_InitStructure);

	CHARGE_Off();
#endif

	// 充电检测的引脚
	RCC_APB2PeriphClockCmd(CHARGE_IN_RCC, ENABLE);

	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_InitStructure.GPIO_Pin   = CHARGE_IN_PIN;
	GPIO_Init(CHARGE_IN_GPIO, &GPIO_InitStructure);
}
