/**
 * @file    alarm_operate.c
 * @brief   
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2014-01-23 14:46:23 星期四 
 * @history (1).2014-01-23 14:46:23 星期四 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#include "alarm_operate_in.h"


/**
 * @brief   获得报警状态
 *
 * @param   lpGas 气体结构体
 * @param   lpDev 设备结构体
 */
void AlarmOperate(S_Gas* lpGas, S_Device* lpDev)
{
	S_Led lLed;
	S_Buzzer lBz;
	S_Vibration lVbr;

	static GasAlarmState sAlarmLast;

	if (lpGas->pTemp->Alarm == GAS_ALARM_NORMAL)
	{
		if (sAlarmLast != lpGas->pTemp->Alarm)
		{
			lLed.Pin = LED_PIN_1;
			lLed.Src = LED_ALARM_LOWER;
			LedOff(&lLed);
			lLed.Src = LED_ALARM_UPPER;
			LedOff(&lLed);

			lBz.Src = BUZZER_ALARM_LOWER;
			BuzzerOff(&lBz);
			lBz.Src = BUZZER_ALARM_UPPER;
			BuzzerOff(&lBz);

			lVbr.Src = VIBRATION_ALARM_LOWER;
			VibrationOff(&lVbr);
			lVbr.Src = VIBRATION_ALARM_UPPER;
			VibrationOff(&lVbr);

			sAlarmLast = lpGas->pTemp->Alarm;
		}
	}
	else if (lpGas->pTemp->Alarm == GAS_ALARM_LOWER)
	{
		PowerSaveBglFresh();

		if (lpDev->pTemp->Time.Count == 0)
		{
			lLed.Pin = LED_PIN_1;
			lLed.Src = LED_ALARM_LOWER;
			lLed.Time = LED_ALARM_TIME_LOWER;
			LedOn(&lLed);

			lBz.Src = BUZZER_ALARM_LOWER;
			lBz.Time = BUZZER_ALARM_TIME_LOWER;
			if (lpDev->pSave->Sound == TURN_ON)
			{
				BuzzerOn(&lBz);
			}

			lVbr.Src = VIBRATION_ALARM_LOWER;
			lVbr.Time = VIBRATION_ALARM_TIME_LOWER;
			if (lpDev->pSave->Vibration == TURN_ON)
			{
				VibrationOn(&lVbr);
			}
		}
	}
	else
	{
		PowerSaveBglFresh();

		if ((lpDev->pTemp->Time.Count == 0) ||
				(lpDev->pTemp->Time.Count ==
						(lpDev->pConst->DispMax >> 1)))
		{
			lLed.Pin = LED_PIN_1;
			lLed.Src = LED_ALARM_UPPER;
			lLed.Time = LED_ALARM_TIME_UPPER;
			LedOn(&lLed);

			lBz.Src = BUZZER_ALARM_UPPER;
			lBz.Time = BUZZER_ALARM_TIME_UPPER;
			if (lpDev->pSave->Sound == TURN_ON)
			{
				BuzzerOn(&lBz);
			}

			lVbr.Src = VIBRATION_ALARM_UPPER;
			lVbr.Time = VIBRATION_ALARM_TIME_UPPER;
			if (lpDev->pSave->Vibration == TURN_ON)
			{
				VibrationOn(&lVbr);
			}
		}
	}
}
