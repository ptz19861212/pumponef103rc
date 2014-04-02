/**
 * @file    state_detect.c
 * @brief   检测状态
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-12-22 07:48:53 星期日 
 * @history (1).2013-12-22 07:48:53 星期日 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#include "state_detect_in.h"

/****************************** 开关泵提示 *****************************/
#ifdef CONFIG_USING_PUMP
// 提示字符串 英文
const char sPumpOnInfoEn[] = "Pump On";

// 提示字符串 中文
const char sPumpOnInfoCn[] = "吸气泵打开";

// 提示字符串 指针数组
const char *sPumpOnInfoTxt[] =
{
		sPumpOnInfoEn,
		sPumpOnInfoCn,
};

const char sPumpOffInfoEn[] = "Pump Off";

// 提示字符串 中文
const char sPumpOffInfoCn[] = "吸气泵关闭";

// 提示字符串 指针数组
const char *sPumpOffInfoTxt[] =
{
		sPumpOffInfoEn,
		sPumpOffInfoCn,
};


/**
 * @brief   打开泵的提示
 */
void StateDetectPumpInfo(S_Device* lpDev)
{
	E_Language lLang;

	lLang = Lcd__LangGet();

	S_Info* lpInfo;
	lpInfo = StateInfoPointGet();

	if (lpDev->pTemp->Fan.State == TURN_ON)
	{
		lpInfo->Info = sPumpOffInfoTxt[lLang];
		PumpOff();
		lpDev->pTemp->Fan.State = TURN_OFF;
	}
	else
	{
		lpInfo->Info = sPumpOnInfoTxt[lLang];
		PumpOn();
		lpDev->pTemp->Fan.State = TURN_ON;
	}

	lpInfo->Time = 2;

	StateInfoInit();
	StateDetectToInfo();
}
#endif


/****************************** 充电提示 *****************************/
// 提示字符串 英文
const char *sChargeInfoEn[] =
{
		"Charging",
		"Full",
};

// 提示字符串 中文
const char *sChargeInfoCn[] =
{
		"正在充电",
		"充电完成",
};

// 提示字符串 指针数组
const char **sChargeInfoTxt[] =
{
		sChargeInfoEn,
		sChargeInfoCn,
};


/**
 * @brief   充电的提示
 */
void StateDetectChargeInfo(S_Device* lpDev)
{
	E_Language lLang;

	lLang = Lcd__LangGet();

	S_Info* lpInfo;
	lpInfo = StateInfoPointGet();

	if (lpDev->pTemp->Charge.State == DEVICE_CHARGE_ON)
	{
		lpInfo->Info = *(sChargeInfoTxt[lLang]);
	}
	else if (lpDev->pTemp->Charge.State == DEVICE_CHARGE_FULL)
	{
		lpInfo->Info = *(sChargeInfoTxt[lLang] + 1);
	}

	lpInfo->Time = 2;

	StateInfoInit();
	StateDetectToCharge();
}

/**
 * @brief   充电状态的改变
 */
void StateDetectChargeInfoChange(S_Device* lpDev)
{
	E_Language lLang;

	lLang = Lcd__LangGet();

	S_Info* lpInfo;
	lpInfo = StateInfoPointGet();

	if (lpDev->pTemp->Charge.State == DEVICE_CHARGE_ON)
	{
		lpInfo->Info = *(sChargeInfoTxt[lLang]);
	}
	else if (lpDev->pTemp->Charge.State == DEVICE_CHARGE_FULL)
	{
		lpInfo->Info = *(sChargeInfoTxt[lLang] + 1);
	}

	lpInfo->Time = 2;

	StateInfoInit();
}


/**
 * @brief   气体浓度求数值
 *
 * @param   lpGas 气体结构体
 */
void StateDetectValueGet(S_Gas* lpGas)
{
//	if (lpGas->pConst->Direct != GAS_DIRECT_BOTH)
//	{
//	}
//	else
//	{
//
//	}

	(*(FUNC_GAS_VALUE_GET)lpGas->pConst->vFunc.ValueGet)
					(lpGas);

	// 气体数值满量程
	if (lpGas->pTemp->Point.Value == lpGas->pConst->Range)
	{
		lpGas->pTemp->FullBlink = TURN_ON;
	}
	else
	{
		lpGas->pTemp->FullBlink = TURN_OFF;
	}
}


/**
 * @brief   正常检测状态显示气体数值第一次显示
 *
 * @param   lpGas 气体结构体
 */
void StateDetectValueDispInit(S_Gas* lpGas)
{
	S_Value_U16 lValue;

#if (DEBUG_TEST_BAT == DEBUG_OFF)
	// 查看气体浓度
	lValue.Num = lpGas->pTemp->Point.Value;
//	lValue.Num = lpGas->pTemp->Point.Adc;
#elif (DEBUG_TEST_BAT == DEBUG_ON)
	// 查看电池电量ADC
	S_Device* lpDev;
	StateDevicePointGet(&lpDev);
	lValue.Num = lpDev->pTemp->Bat.Point.Adc;
#endif

	lValue.Point = lpGas->pConst->Point;

	Lcd__GasValueDisp(&lValue);
}


/**
 * @brief   正常检测状态显示气体数值
 *
 * @param   lpGas 气体结构体
 * @param   lpDev 设备结构体
 */
void StateDetectValueDisp(S_Gas* lpGas, S_Device* lpDev)
{
	static my_gas_t sStateGasValueLast;

	// 数值改变才再次刷新显示
	if (lpGas->pTemp->Point.Value != sStateGasValueLast)
	{
		StateDetectValueDispInit(lpGas);
	}
	// 数值相等的时候有一种特殊情况，满量程，这个时候闪烁显示
	else
	{
		if (lpGas->pTemp->FullBlink == TURN_ON)
		{
			if (lpDev->pTemp->Blink == BLINK_ON)
			{
				StateDetectValueDispInit(lpGas);
			}
			else
			{
				Lcd__GasValueClr();
			}
		}
	}
	sStateGasValueLast = lpGas->pTemp->Point.Value;
}


/**
 * @brief   获得报警状态
 *
 * @param   lpGas 气体结构体
 */
void StateDetectAlarmGet(S_Gas* lpGas)
{
	(*(FUNC_GAS_ALARM_GET)lpGas->pConst->vFunc.AlarmGet)(lpGas);

//	S_Device* lpDev;
//	StateDevicePointGet(&lpDev);
//
//	if (lpGas->pTemp->Alarm != GAS_ALARM_NORMAL)
//	{
//		if (lpDev->pTemp->Blink == BLINK_ON)
//		{
////			BuzzerOn(BUZZER_ALARM_LOWER);
////			VibrationOn(VIBRATION_ALARM_LOWER);
//		}
//		else
//		{
////			BuzzerOff(BUZZER_ALARM_LOWER);
////			VibrationOff(VIBRATION_ALARM_LOWER);
//		}
//	}
//	else
//	{
////		BuzzerOff(BUZZER_ALARM_LOWER);
////		VibrationOff(VIBRATION_ALARM_LOWER);
//	}
}


/**
 * @brief   显示当前状态，初次显示
 *
 * @param   lpGas 气体结构体
 * @param   lpDev 设备结构体
 */
void StateDetectStateDispInit(S_Gas* lpGas, S_Device* lpDev)
{
	if (lpGas->pTemp->Alarm == GAS_ALARM_NORMAL)
	{
		Lcd__StatDisp(*(lpDev->pConst->State.Detect + lpDev->pSave->Language));
	}
	// 右下的报警状态
	else if (lpGas->pTemp->Alarm == GAS_ALARM_LOWER)
	{
		Lcd__StatDisp(*(lpDev->pConst->Alarm.Lower + lpDev->pSave->Language));
	}
	else if (lpGas->pTemp->Alarm == GAS_ALARM_UPPER)
	{
		Lcd__StatDisp(*(lpDev->pConst->Alarm.Upper + lpDev->pSave->Language));
	}
}


/**
 * @brief   显示当前状态
 *
 * @param   lpGas 气体结构体
 * @param   lpDev 设备结构体
 */
void StateDetectStateDisp(S_Gas* lpGas, S_Device* lpDev)
{
	static uint8_t sStateAlarmLast = GAS_ALARM_NORMAL;

	// 改变报警状态都会刷新显示一下
	if (lpGas->pTemp->Alarm != sStateAlarmLast)
	{
		StateDetectStateDispInit(lpGas, lpDev);
	}

	sStateAlarmLast = lpGas->pTemp->Alarm;
}


/**
 * @brief   显示风扇状态
 *
 * @param   lpDev 设备结构体
 */
void StateDetectFanDisp(S_Device* lpDev)
{
	S_Lcd_Point lPoint;

	lPoint.X = CONFIG_DETECT_FAN_DISP_X;
	lPoint.Y = CONFIG_DETECT_FAN_DISP_Y;

	static E_TurnState sStateDetectFanLast;
	static uint8_t sStateDetectFanCount = 0;

	if (lpDev->pTemp->Fan.State != sStateDetectFanLast)
	{
		if (lpDev->pTemp->Fan.State == TURN_OFF)
		{
			Lcd__FanClr();
		}
	}

	sStateDetectFanCount++;

	if (sStateDetectFanCount < 20)
	{
		return;
	}
	else
	{
		sStateDetectFanCount = 0;
	}

	if (lpDev->pTemp->Fan.State == TURN_ON)
	{
		Lcd__FanDisp();
	}

	sStateDetectFanCount++;

}


/**
 * @brief   获得充电状态
 *
 * @param   lpDev 设备结构体
 */
void StateDetectChargeGet(S_Device* lpDev)
{
	if (ChargeScan() == E_TRUE)
	{
		lpDev->pTemp->Charge.State = DEVICE_CHARGE_ON;
	}
	else
	{
		lpDev->pTemp->Charge.State = DEVICE_CHARGE_OFF;
	}
}


/**
 * @brief   显示充电状态
 *
 * @param   lpDev 设备结构体
 */
void StateDetectChargeDisp(S_Device* lpDev)
{
	if (lpDev->pTemp->Charge.State != DEVICE_CHARGE_OFF)
	{
		Lcd__ChargeDisp();
	}
	else
	{
		Lcd__ChargeClr();
	}
}


/**
 * @brief   显示电池状态初始
 *
 * @param   lpDev 设备结构体
 */
void StateDetectBatDispInit(S_Device* lpDev)
{
	Lcd__BatDisp(lpDev->pTemp->Bat.Point.Value);
}


/**
 * @brief   显示电池状态
 *
 * @param   lpDev 设备结构体
 */
void StateDetectBatDisp(S_Device* lpDev)
{
	static uint8_t sStateBatLast;

	if (lpDev->pTemp->Bat.Point.Value != sStateBatLast)
	{
		StateDetectBatDispInit(lpDev);
	}

	sStateBatLast = lpDev->pTemp->Bat.Point.Value;
}


/**
 * @brief   正常状态初次显示
 *
 * @param   lpGas 气体结构体
 * @param   lpDev 设备结构体
 */
void StateDetectDispInit(S_Gas* lpGas, S_Device* lpDev)
{
	// 清屏
	DisClr();

	// 获得显示数值
	StateDetectValueGet(lpGas);
	StateDetectValueDispInit(lpGas);

	// 获得显示报警
#if (DEBUG_TEST_BAT == DEBUG_OFF)
	// 获取报警
	StateDetectAlarmGet(lpGas);
#elif (DEBUG_TEST_BAT == DEBUG_ON)
	// 为了测电池
#endif

	// 显示单位
	Lcd__UnitDisp(lpGas->pConst->Unit);

	// 显示名称
	Lcd__GasNameDisp(*(lpGas->pConst->Name + lpDev->pSave->Language));

	// 显示当前状态
	StateDetectStateDispInit(lpGas, lpDev);

	// 显示充电状态
	StateDetectChargeDisp(lpDev);

	// 获得并显示电池状态
	StateDetectBatDispInit(lpDev);

	// 显示虚线
//	S_Lcd_Line_Horizon lHor;
//	lHor.XS = gLcdScreen.PS.X;
//	lHor.Y = 15;
//	lHor.XE = gLcdScreen.PE.X;
//	DisHorDotLinSet(&lHor);
//
//	lHor.XS = gLcdScreen.PS.X;
//	lHor.Y = 47;
//	lHor.XE = gLcdScreen.PE.X;
//	DisHorDotLinSet(&lHor);
}



/**
 * @brief   正常状态显示
 *
 * @param   lpGas 气体结构体
 * @param   lpDev 设备结构体
 */
void StateDetectDisp(S_Gas* lpGas, S_Device* lpDev)
{
	// 获得显示数值
	StateDetectValueGet(lpGas);

#if (DEBUG_TEST_BAT == DEBUG_OFF)
	// 显示数值
	StateDetectValueDisp(lpGas, lpDev);
#elif (DEBUG_TEST_BAT == DEBUG_ON)
	// 为了测电池
	StateDetectValueDispInit(lpGas);
#endif

	// 获得显示报警
#if (DEBUG_TEST_BAT == DEBUG_OFF)
	// 获取报警
	StateDetectAlarmGet(lpGas);
#elif (DEBUG_TEST_BAT == DEBUG_ON)
	// 为了测电池
#endif

	// 显示当前状态
	StateDetectStateDisp(lpGas, lpDev);

	StateDetectBatDisp(lpDev);
}


/**
 * @brief   关机
 */
void StateDetectShutdown(void)
{
	SourceOff();
	PumpOff();
	DisPwrDown();
}


/**
 * @brief   正常检测状态
 *
 * @param   lpGas 气体结构体
 * @param   lpDev 设备结构体
 */
void StateDetect(S_Gas* lpGas, S_Device* lpDev)
{
	uint8_t lKeyLong3S, lKeyBit, lKeyLongTmp, lKeyTmp;
	uint8_t lKey[] = {KEY_UP, KEY_DOWN, KEY_ENTER, KEY_SPECIAL};
	uint8_t lI;

	lKeyLong3S = 0;

	// 检测当前有哪几个长按的按键超过3秒了
	for (lI = 0; lI < sizeof(lKey); lI++)
	{
		lKeyLongTmp = KeyLongGet(lKey[lI]);

		// 觉得3秒有些长了，所以改成2秒
		if (lKeyLongTmp >= 2)
		{
			lKeyTmp = lKey[lI];
			BitGet(&lKeyTmp, &lKeyBit, sizeof(my_key_t) << 3);
			lKeyLong3S |= 1 << lKeyBit;
		}
	}

	S_Shutdown* lpShutdown;

	switch (lKeyLong3S & gKeyState)
	{
		case (KEY_UP | KEY_DOWN):
			StateDetectToMenu();
			// 没有return 的话，继续向下面执行，可能造成显示不正常
			return;
			break;

		case (KEY_ENTER):
			lpShutdown = StateShutdownPointGet();

			lpShutdown->Time = 5;
			lpShutdown->BatLow = E_FALSE;
			lpShutdown->Func.Shutdown = StateDetectShutdown;
			StateShutdownInit();
			StateDetectToShutdown();
			return;
			break;

		case (KEY_SPECIAL):
			StateDetectPumpInfo(lpDev);

			return;
			break;


		default:
			break;
	}

	if (lpDev->pTemp->Disp.Fresh == TURN_ON)
	{
		StateDetectDisp(lpGas, lpDev);
//		rt_kprintf("bat detect = %d\n",
//					lpDev->pTemp->Bat.Point.Adc);
	}

	// 显示风扇状态
	StateDetectFanDisp(lpDev);

	AlarmOperate(lpGas, lpDev);
}

