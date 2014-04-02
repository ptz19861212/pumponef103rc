/**
 * @file    bsp_buzzer.c
 * @brief   
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2014-01-17 09:44:01 星期五 
 * @history (1).2014-01-17 09:44:01 星期五 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#include "bsp_buzzer_in.h"

static my_buzzer_t sBuzzer;
// 倒计时
static S_Buzzer sBuzzerCountdown[BUZZER_SOURCE_NUM];


/**
 * @brief   蜂鸣器打开
 */
void BuzzerOn(S_Buzzer* lpBz)
{
	sBuzzer |= BIT(lpBz->Src);

	if (lpBz->Time > sBuzzerCountdown[lpBz->Src].Time)
	{
		sBuzzerCountdown[lpBz->Src].Time = lpBz->Time;
	}

	BUZZER_On();
}


/**
 * @brief   蜂鸣器关闭
 */
void BuzzerOff(S_Buzzer* lpBz)
{
	sBuzzer &= ~(BIT(lpBz->Src));
	sBuzzerCountdown[lpBz->Src].Time = 0;

	if (sBuzzer == 0)
	{
		BUZZER_Off();
	}
}


/**
 * @brief   蜂鸣器倒计时
 */
void BuzzerCountdown(void)
{
	uint8_t lI;

	for (lI = 0; lI < BUZZER_SOURCE_NUM; lI++)
	{
		if (sBuzzerCountdown[lI].Time > 0)
		{
			sBuzzerCountdown[lI].Time--;
		}
		else
		{
			sBuzzer &= ~(BIT(lI));
		}
	}

	if (sBuzzer == 0)
	{
		BUZZER_Off();
	}
}



/**
 * @brief   蜂鸣器初始化
 */
void BuzzerInit(void)
{
	BUZZER_Init();
}
