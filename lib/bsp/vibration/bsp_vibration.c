/**
 * @file    bsp_vibration.c
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

#include "bsp_vibration_in.h"

static my_vibration_t sVibration;
// 倒计时
static S_Vibration sVibrationCountdown[VIBRATION_SOURCE_NUM];


/**
 * @brief   振动泵打开
 */
void VibrationOn(S_Vibration* lpVbr)
{
	sVibration |= BIT(lpVbr->Src);

	if (lpVbr->Time > sVibrationCountdown[lpVbr->Src].Time)
	{
		sVibrationCountdown[lpVbr->Src].Time = lpVbr->Time;
	}

	VIBRATION_On();
}


/**
 * @brief   振动泵关闭
 */
void VibrationOff(S_Vibration* lpVbr)
{
	sVibration &= ~(BIT(lpVbr->Src));
	sVibrationCountdown[lpVbr->Src].Time = 0;

	if (sVibration == 0)
	{
		VIBRATION_Off();
	}
}


/**
 * @brief   振动泵倒计时
 */
void VibrationCountdown(void)
{
	uint8_t lI;

	for (lI = 0; lI < VIBRATION_SOURCE_NUM; lI++)
	{
		if (sVibrationCountdown[lI].Time > 0)
		{
			sVibrationCountdown[lI].Time--;
		}
		else
		{
			sVibration &= ~(BIT(lI));
		}
	}

	if (sVibration == 0)
	{
		VIBRATION_Off();
	}
}



/**
 * @brief   振动泵初始化
 */
void VibrationInit(void)
{
	VIBRATION_Init();
}
