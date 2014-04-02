/**
 * @file    bsp_led.c
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

#include "bsp_led_in.h"

// 显示来源状态
static my_led_t sLed[CONFIG_LED_NUM];
// 显示引脚状态
static uint8_t sLedPin;
// LED 倒计时
// 倒计时
static S_Led sLedCountdown[CONFIG_LED_NUM][LED_SOURCE_NUM];


/**
 * @brief   灯打开
 */
void LedOn(S_Led* lpLed)
{
	sLed[lpLed->Pin] |= BIT(lpLed->Src);

	sLedPin |= BIT(lpLed->Pin);

	if (lpLed->Time >
				sLedCountdown[lpLed->Pin][lpLed->Src].Time)
	{
		sLedCountdown[lpLed->Pin][lpLed->Src].Time = lpLed->Time;
	}

	LED_On(lpLed->Pin);
}


/**
 * @brief   灯关闭
 */
void LedOff(S_Led* lpLed)
{
	sLed[lpLed->Pin] &= ~(BIT(lpLed->Src));
	sLedPin &= ~(BIT(lpLed->Pin));
	sLedCountdown[lpLed->Pin][lpLed->Src].Time = 0;

	if (sLed[lpLed->Pin] == 0)
	{
		LED_Off(lpLed->Pin);
	}
}


/**
 * @brief   灯倒计时
 */
void LedCountdown(void)
{
	uint8_t lSrc, lPin;

	for (lPin = 0; lPin < CONFIG_LED_NUM; lPin++)
	{
		for (lSrc = 0; lSrc < LED_SOURCE_NUM; lSrc++)
		{
			if (sLedCountdown[lPin][lSrc].Time > 0)
			{
				sLedCountdown[lPin][lSrc].Time--;
			}
			else
			{
				sLed[lPin] &= ~(BIT(lSrc));
			}
		}

		if (sLed[lPin] == 0)
		{
			LED_Off(lPin);
		}
	}
}



/**
 * @brief   灯初始化
 */
void LedInit(void)
{
	LED_Init();
}
