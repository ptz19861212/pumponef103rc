/**
 * @file    status.c
 * @brief   状态
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-12-03 12:54:42 星期二 
 * @history (1).2013-12-03 12:54:42 星期二 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#include "state_in.h"

// 时间中断
//static uint8_t gStatusFlag = FALSE;
static struct rt_semaphore sSemSystemTime;

// 系统状态机当前状态
static uint8_t sState = STATE_DETECT;

//static const uint8_t sSaveSize =
//				CONFIG_SAVE_GAS_SIZE + CONFIG_SAVE_DEVICE_SIZE;
// 气体数据存储
//uint8_t sSaveGas[CONFIG_SAVE_GAS_SIZE];
// 设备设置存储
//uint8_t sSaveDevice[CONFIG_SAVE_DEVICE_SIZE];
// 气体数据存储 设备设置存储
static uint8_t sSave[CONFIG_SAVE_GAS_SIZE + CONFIG_SAVE_DEVICE_SIZE];
//static uint8_t sSave[sSaveSize];

// 气体名称数组
const char *sGasName[] =
{
		CONFIG_GAS_NAME_EN,
		CONFIG_GAS_NAME_CN,
};
// 设备状态数组
const char *sDeviceStateDetect[] =
{
		DEVICE_STATE_DETECT_EN,
		DEVICE_STATE_DETECT_CN,
};
// 设备标零
const char *sDeviceStateCaliZero[] =
{
		DEVICE_STATE_ZERO_EN,
		DEVICE_STATE_ZERO_CN,
};
// 设备标气
const char *sDeviceStateCaliGas[] =
{
		DEVICE_STATE_GAS_EN,
		DEVICE_STATE_GAS_CN,
};
// 设备一级报警
const char *sDeviceAlarmLower[] =
{
		DEVICE_ALARM_LOWER_EN,
		DEVICE_ALARM_LOWER_CN,
};
// 设备二级报警
const char *sDeviceAlarmUpper[] =
{
		DEVICE_ALARM_UPPER_EN,
		DEVICE_ALARM_UPPER_CN,
};


// 气体的固定部分数据
const struct S_Gas_Const sGasConst =
{
		// name
		CONFIG_GAS_NAME_INDEX,
		sGasName,
		// range
		CONFIG_GAS_RANGE,
		// direct
		CONFIG_GAS_DIRECT,
		// point
		CONFIG_GAS_POINT,
		// unit
		CONFIG_GAS_UNIT_INDEX,
		CONFIG_GAS_UNIT,
		// threshold
		CONFIG_GAS_REF1_THRESHOLD,
		// 零点ADC
		CONFIG_GAS_ZERO_ADC,
		// 零点数值
		CONFIG_GAS_ZERO_VALUE,
		// 标零范围
		CONFIG_GAS_ZERO_RANGE,
		// 标气的时候屏蔽的范围
		CONFIG_GAS_VALUE_THRESHOLD,
		// 求浓度函数
		(MY_FUNC)CONFIG_GAS_FUNC_VALUE_GET,
		// 求报警函数
		(MY_FUNC)CONFIG_GAS_FUNC_ALARM_GET,
		// 求报警上下限函数
		(MY_FUNC)CONFIG_GAS_FUNC_ALARM_LOWER_LIMIT_GET,
		// 求报警上下限函数
		(MY_FUNC)CONFIG_GAS_FUNC_ALARM_UPPER_LIMIT_GET,
#if ((CONFIG_GAS != GAS_O2) && (CONFIG_GAS != GAS_EX))
		// 求报警上下限函数
		(MY_FUNC)CONFIG_GAS_FUNC_ALARM_STEL_LIMIT_GET,
		// 求报警上下限函数
		(MY_FUNC)CONFIG_GAS_FUNC_ALARM_TWA_LIMIT_GET,
#endif
		// 求标气上下限函数
		(MY_FUNC)CONFIG_GAS_FUNC_GAS_VALUE_LIMIT_GET,
		// 气体标零的时候，判断标零是否成功
		(MY_FUNC)CONFIG_GAS_FUNC_GAS_CALI_ZERO_GET,
		// 气体标气的时候，判断标气是否成功
		(MY_FUNC)CONFIG_GAS_FUNC_GAS_CALI_COEFF_GET,
};

// 设备的固定数据
const struct S_Device_Const sDeviceConst =
{
		// time second
		DEVICE_TIME_SECOND,
		// disp fresh
		DEVICE_DISPLAY_FRESH,
		// fan disp max
//		DEVICE_FAN_DISP_MAX,
		// fan max
		DEVICE_FAN_MAX,
		// bat 0%
		DEVICE_BAT_VALUE_0,
		DEVICE_BAT_ADC_0,
		// bat 20%
		DEVICE_BAT_VALUE_20,
		DEVICE_BAT_ADC_20,
		// bat 40%
		DEVICE_BAT_VALUE_40,
		DEVICE_BAT_ADC_40,
		// bat 60%
		DEVICE_BAT_VALUE_60,
		DEVICE_BAT_ADC_60,
		// bat 80%
		DEVICE_BAT_VALUE_80,
		DEVICE_BAT_ADC_80,
		// bat 100%
		DEVICE_BAT_VALUE_100,
		DEVICE_BAT_ADC_100,
		// root
		DEVICE_AUTHORITY_ROOT,
		DEVICE_PWD_ROOT,
		// debug
		DEVICE_AUTHORITY_DEBUG,
		DEVICE_PWD_DEBUG,
		// usr
		DEVICE_AUTHORITY_USR,
		DEVICE_PWD_USR,
		// detect
		sDeviceStateDetect,
		// cali zero
		sDeviceStateCaliZero,
		// cali gas
		sDeviceStateCaliGas,
		// alarm lower
		sDeviceAlarmLower,
		// alarm upper
		sDeviceAlarmUpper,
		// version
		DEVICE_VERSION,
		// date
		__DATE__,
		// time
		__TIME__,
};

// 气体的临时数据
static struct S_Gas_Temp sGasTemp;
// 设备的临时数据
static struct S_Device_Temp sDeviceTemp;

// 气体的全部数据
S_Gas sGas;
// 设备的全部设定的数据
S_Device sDevice;


/**
 * @brief   计数允许显示
 */
void DeviceDispCount(void)
{
	// 计数增加
	sDevice.pTemp->Disp.Count++;

	if (sDevice.pTemp->Disp.Count >= sDevice.pConst->DispMax)
	{
		sDevice.pTemp->Disp.Count = 0x00;
		sDevice.pTemp->Disp.Fresh = TURN_ON;
		// 控制设备显示的闪烁
		if (sDevice.pTemp->Blink == BLINK_ON)
		{
			sDevice.pTemp->Blink = BLINK_OFF;
		}
		else
		{
			sDevice.pTemp->Blink = BLINK_ON;
		}
	}
	else
	{
		sDevice.pTemp->Disp.Fresh = TURN_OFF;
	}
}


/**
 * @brief   计数时间，秒，分，时
 */
void DeviceTimeCount(void)
{
	// 计数增加
	sDevice.pTemp->Time.Count++;

	if (sDevice.pTemp->Time.Count >= sDevice.pConst->SecMax)
	{
		sDevice.pTemp->Time.Count = 0x00;
		sDevice.pTemp->Time.Sec++;

//		if (sDevice.pTemp->Time.Sec >= 60)
//		{
//			sDevice.pTemp->Time.Sec = 0;
//			sDevice.pTemp->Time.Min++;
//
//			if (sDevice.pTemp->Time.Min >= 60)
//			{
//				sDevice.pTemp->Time.Min = 0;
//				sDevice.pTemp->Time.Hour++;
//
//				if (sDevice.pTemp->Time.Hour >= 24)
//				{
//					sDevice.pTemp->Time.Hour = 0;
//					sDevice.pTemp->Time.Day++;
//				}
//			}
//		}
	}

}


/**
 * @brief   计数允许显示控制初始化
 */
void DeviceDispCountInit(void)
{
	sDevice.pTemp->Disp.Count = 0x00;
	sDevice.pTemp->Disp.Fresh = TURN_ON;
	sDevice.pTemp->Blink = BLINK_ON;
}


/**
 * @brief   数据设置写入
 */
void SaveWrite(void)
{
	S_Flash_Write lFlash;

	lFlash.Addr.Start = CONFIG_FLASH_SAVE_ADDR_START;
	lFlash.Addr.End = lFlash.Addr.Start + sizeof(sSave);
	lFlash.Array = (uint16_t*)sSave;

	FlashWrite(&lFlash);
}


/**
 * @brief   数据设置读取
 */
void SaveRead(void)
{
	S_Flash_Read lRead;

	lRead.Addr.Start = CONFIG_FLASH_SAVE_ADDR_START;
	lRead.Addr.End = lRead.Addr.Start + sizeof(sSave);
	lRead.Array = sSave;
	FlashRead(&lRead);
}


/**
 * @brief   数据设置读取
 */
static void SaveReadInit(void)
{
	SaveRead();



	if (sGas.pSave->Save_Bits.Ref1 == FLASH_SAVE_FALSE)
	{
		sGas.pSave->Ref1.Adc = CONFIG_GAS_REF1_ADC;
		sGas.pSave->Ref1.Value = CONFIG_GAS_REF1_VALUE;
	}

	if (sGas.pSave->Save_Bits.Ref2 == FLASH_SAVE_FALSE)
	{
		sGas.pSave->Ref2.Adc = CONFIG_GAS_REF2_ADC;
		sGas.pSave->Ref2.Value = CONFIG_GAS_REF2_VALUE;
	}

	if (sGas.pSave->Save_Bits.Ref3 == FLASH_SAVE_FALSE)
	{
		sGas.pSave->Ref3.Adc = CONFIG_GAS_REF3_ADC;
		sGas.pSave->Ref3.Value = CONFIG_GAS_REF3_VALUE;
	}

	if (sGas.pSave->Save_Bits.Ref4 == FLASH_SAVE_FALSE)
	{
		sGas.pSave->Ref4.Adc = CONFIG_GAS_REF4_ADC;
		sGas.pSave->Ref4.Value = CONFIG_GAS_REF4_VALUE;
	}

	if (sGas.pSave->Save_Bits.Ref5 == FLASH_SAVE_FALSE)
	{
		sGas.pSave->Ref5.Adc = CONFIG_GAS_REF5_ADC;
		sGas.pSave->Ref5.Value = CONFIG_GAS_REF5_VALUE;
	}

	if (sGas.pSave->Save_Bits.Lower == FLASH_SAVE_FALSE)
	{
		sGas.pSave->Alarm.Lower = CONFIG_GAS_ALARM_LOWER;
//		sGas.pSave->Alarm.Lower = 27;
	}

	if (sGas.pSave->Save_Bits.Upper == FLASH_SAVE_FALSE)
	{
		sGas.pSave->Alarm.Upper = CONFIG_GAS_ALARM_UPPER;
//		sGas.pSave->Alarm.Upper = 73;
	}

	if (sGas.pSave->Save_Bits.Stel == FLASH_SAVE_FALSE)
	{
		sGas.pSave->Alarm.Stel = CONFIG_GAS_ALARM_STEL;
	}

	if (sGas.pSave->Save_Bits.Twa == FLASH_SAVE_FALSE)
	{
		sGas.pSave->Alarm.Twa = CONFIG_GAS_ALARM_TWA;
	}

	if (sGas.pSave->Save_Bits.Date == FLASH_SAVE_FALSE)
	{
		sGas.pSave->CaliDate.Mon = CONFIG_GAS_CALI_DATE_MON;
		sGas.pSave->CaliDate.Day = CONFIG_GAS_CALI_DATE_DAY;
		sGas.pSave->CaliDate.Year = CONFIG_GAS_CALI_DATE_YEAR;
	}

	if (sGas.pSave->Save_Bits.Time == FLASH_SAVE_FALSE)
	{
		sGas.pSave->CaliTime.Hour = CONFIG_GAS_CALI_TIME_HOUR;
		sGas.pSave->CaliTime.Min = CONFIG_GAS_CALI_TIME_MIN;
		sGas.pSave->CaliTime.Sec = CONFIG_GAS_CALI_TIME_SEC;
	}

	if (sDevice.pSave->Save_Bits.Addr == FLASH_SAVE_FALSE)
	{
//		sGas.pSave->Alarm.Stel = CONFIG_GAS_ALARM_LOWER;
	}

	if (sDevice.pSave->Save_Bits.Fan == FLASH_SAVE_FALSE)
	{
//		sGas.pSave->Alarm.Twa = CONFIG_GAS_ALARM_UPPER;
	}

	if (sDevice.pSave->Save_Bits.Lang == FLASH_SAVE_FALSE)
	{
		sDevice.pSave->Language = CONFIG_LANGUAGE;
	}

	if (sDevice.pSave->Save_Bits.Snd == FLASH_SAVE_FALSE)
	{
		sDevice.pSave->Sound = CONFIG_ALARM_SOUND;
	}

	if (sDevice.pSave->Save_Bits.Vbr == FLASH_SAVE_FALSE)
	{
		sDevice.pSave->Vibration = CONFIG_ALARM_VIBRATION;
	}

	if (sDevice.pSave->Save_Bits.Manf == FLASH_SAVE_FALSE)
	{
		sDevice.pSave->Manf.Mon = CONFIG_MANF_DATE_MON;
		sDevice.pSave->Manf.Day = CONFIG_MANF_DATE_DAY;
		sDevice.pSave->Manf.Year = CONFIG_MANF_DATE_YEAR;
	}

	if (sDevice.pSave->Save_Bits.Wrnty == FLASH_SAVE_FALSE)
	{
		sDevice.pSave->Warranty.Mon = CONFIG_WARRANTY_DATE_MON;
		sDevice.pSave->Warranty.Day = CONFIG_WARRANTY_DATE_DAY;
		sDevice.pSave->Warranty.Year = CONFIG_WARRANTY_DATE_YEAR;
	}

}


/**
 * @brief   状态转换为自检状态
 */
void StateSelfCheck(void)
{
	sState = STATE_SELF_CHECK;
	SelfCheckRootInit();
}


/**
 * @brief   状态转换为菜单状态
 */
void StateDetectToMenu(void)
{
	sState = STATE_MENU;
//	sGas.pTemp->Alarm = GAS_ALARM_NORMAL;
//	MenuValInit();
//	SaveReadInit();
	MenuRootInit();
}

#include "config_bsp.h"

/**
 * @brief   自检状态转换为检测状态
 */
void StateSelfCheckToDetect(void)
{
	sState = STATE_DETECT;
	StateDetectDispInit(&sGas, &sDevice);
}

/**
 * @brief   状态转换为检测状态
 */
void StateMenuToDetect(void)
{
	sState = STATE_DETECT;
	StateDetectDispInit(&sGas, &sDevice);
}


/**
 * @brief   菜单状态转换为输入状态
 */
void StateMenuToInput(void)
{
	sState = STATE_INPUT;
}


/**
 * @brief   输入状态转换为菜单状态
 */
void StateInputToMenu(void)
{
	sState = STATE_MENU;
//	MenuChildPreInit();
	MenuDisp();
	MenuLoadInit();
}


/**
 * @brief   菜单状态转换为倒计时状态
 */
void StateInputToCountdown(void)
{
	sState = STATE_COUNTDOWN;
}


/**
 * @brief   倒计时状态转换为菜单状态
 */
void StateCountdownToMenu(void)
{
	sState = STATE_MENU;
//	MenuChildPreInit();
	MenuDisp();
	MenuLoadInit();
}


/**
 * @brief   倒计时状态转换为结果状态
 */
void StateCountdownToResult(void)
{
	sState = STATE_RESULT;
}


/**
 * @brief   结果状态转换为菜单状态
 */
void StateResultToMenu(void)
{
	sState = STATE_MENU;
//	MenuChildPreInit();
	MenuDisp();
	MenuLoadInit();
}


/**
 * @brief   结果状态转换为检测状态
 */
void StateResultToDetect(void)
{
	sState = STATE_DETECT;
	StateDetectDispInit(&sGas, &sDevice);
}


/**
 * @brief   检测状态转换为关机状态
 */
void StateDetectToShutdown(void)
{
	sState = STATE_SHUTDOWN;
//	StateDetectDispInit(&sGas, &sDevice);
}


/**
 * @brief   关机状态转换为检测状态
 */
void StateShutdownToDetect(void)
{
	sState = STATE_DETECT;
	StateDetectDispInit(&sGas, &sDevice);
}


/**
 * @brief   关机状态转换为断电状态
 */
void StateShutdownToPowerOff(void)
{
	sState = STATE_POWER_OFF;
}


/**
 * @brief   提示状态转换为检测状态
 */
void StateInfoToDetect(void)
{
	sState = STATE_DETECT;
	StateDetectDispInit(&sGas, &sDevice);
}


/**
 * @brief   检测状态转换为提示状态
 */
void StateDetectToInfo(void)
{
	sState = STATE_INFO;
}


/**
 * @brief   充电状态转换为检测状态
 */
void StateChargeToDetect(void)
{
	sState = STATE_DETECT;
	StateDetectDispInit(&sGas, &sDevice);
}


/**
 * @brief   检测状态转换为充电状态
 */
void StateDetectToCharge(void)
{
	sState = STATE_CHARGE;
}


/**
 * @brief   检查电池电量
 */
void StateBatCheck(void)
{
	if (sDevice.pTemp->Disp.Fresh != TURN_ON)
	{
		return;
	}

	// 不判断的话，就会一直卡在刚进入的5秒倒计时
	if (sState == STATE_SHUTDOWN)
	{
		return;
	}

	// 不判断的话，如果电池电量低，充电的时候就会瞬间显示本函数下面的内容
	if (sState == STATE_CHARGE)
	{
		return;
	}

	//获得电池电量
	BatValueGet(&sDevice);

	if (sDevice.pTemp->Bat.Point.Value ==
			sDevice.pConst->Bat.Lv0.Value)
	{
		S_Shutdown* lpShutdown;

		lpShutdown = StateShutdownPointGet();

		lpShutdown->Time = 5;
		lpShutdown->Func.Shutdown = StateDetectShutdown;
		lpShutdown->BatLow = E_TRUE;
		StateShutdownInit();
		StateDetectToShutdown();
	}
}


/**
 * @brief   开机振动声音灯
 */
void StateLedBzVbrCheck(void)
{

	static uint8_t sLedBzVbrCount = 0;

	if (sDevice.pTemp->Disp.Fresh != TURN_ON)
	{
		return;
	}

	if (sLedBzVbrCount < 2)
	{

		S_Led lLed;

		lLed.Src = LED_POWER_ON;
		lLed.Time = LED_POWER_ON_TIME;
		lLed.Pin = LED_PIN_1,
		LedOn(&lLed);

		S_Buzzer lBz;

		lBz.Src = BUZZER_POWER_ON;
		lBz.Time = BUZZER_POWER_ON_TIME;
		BuzzerOn(&lBz);

		S_Vibration lVbr;

		lVbr.Src = VIBRATION_POWER_ON;
		lVbr.Time = VIBRATION_POWER_ON_TIME;
		VibrationOn(&lVbr);
	}
	else
	{
		// 取固定的值，防止溢出
		sLedBzVbrCount = 3;
	}

	sLedBzVbrCount++;
}

static E_DeviceChargeState sChargeStateLast = DEVICE_CHARGE_OFF;
/**
 * @brief   充电检测
 */
void StateChargeCheck(void)
{
//	if (sDevice.pTemp->Disp.Fresh != ENABLE)
//	{
//		return;
//	}

	if (ChargeScan() == E_TRUE)
	{
		// 是否充满电
		if (sDevice.pTemp->Bat.Point.Adc > DEVICE_BAT_ADC_FULL)
		{
			sDevice.pTemp->Charge.State = DEVICE_CHARGE_FULL;
		}
		else
		{
			sDevice.pTemp->Charge.State = DEVICE_CHARGE_ON;
		}

		// 非充电状态
		if (sState != STATE_CHARGE)
		{
			StateDetectChargeInfo(&sDevice);
			PumpOff();
			sDevice.pTemp->Fan.State = TURN_OFF;
		}
		// 充电状态
		else
		{
			// 是否充电状态产生变化
			if (sChargeStateLast != sDevice.pTemp->Charge.State)
			{
				StateDetectChargeInfoChange(&sDevice);
			}
		}

		sChargeStateLast = sDevice.pTemp->Charge.State;
	}
	else
	{
		sDevice.pTemp->Charge.State = DEVICE_CHARGE_OFF;

		if (sState == STATE_CHARGE)
		{
			StateChargeToDetect();
		}
	}


}


/**
 * @brief   设备数据初始化
 */
static void DeviceDataInit(void)
{
	// 设备，气体指针初始化
	sDevice.pConst = &sDeviceConst;
//	sDevice.pSave = (struct S_Device_Save*)sSaveDevice;
	sDevice.pSave = (struct S_Device_Save*)&(sSave[CONFIG_SAVE_GAS_SIZE]);
	sDevice.pTemp = &sDeviceTemp;

	// 设备初始化
	sDevice.pTemp->Relay = TURN_OFF;
	sDevice.pTemp->Charge.State = DEVICE_CHARGE_OFF;
	sDevice.pTemp->Blink = TURN_ON;
	sDevice.pTemp->Error = DEVICE_ERR_NONE;
	sDevice.pTemp->Fan.State = TURN_ON;
	sDevice.pTemp->Disp.Count = 0x00;
	sDevice.pTemp->Disp.Fresh = TURN_ON;
	sDevice.pTemp->Bat.Point.Adc = 0x00;
	sDevice.pTemp->Bat.Point.Value = 0x00;
	sDevice.pTemp->Group.Authority = DEVICE_AUTHORITY_ROOT;
	sDevice.pTemp->Group.Pwd = DEVICE_PWD_ROOT;
//	sDevice.pTemp->Usr.Group = DEVICE_USR_USR;
//	sDevice.pTemp->Usr.Pwd = DEVICE_PWD_USR;
}


/**
 * @brief   气体数据初始化
 */
static void GasDataInit(void)
{
	sGas.pConst = &sGasConst;
//	sGas.pSave = (struct S_Gas_Save*)sSaveGas;
	sGas.pSave = (struct S_Gas_Save*)sSave;
	sGas.pTemp = &sGasTemp;

	// 气体初始化
	sGas.pTemp->Point.Adc = 0x00;
	sGas.pTemp->Point.Value = 0x00;
	sGas.pTemp->Alarm = GAS_ALARM_NORMAL;
	sGas.pTemp->State = GAS_STATE_NORMAL;
	sGas.pTemp->FullBlink = TURN_OFF;
	sGas.pTemp->Error = GAS_ERROR_NONE;
}



#include "state_input.h"
#include "menu_param_lower.h"
#include "font_chinese.h"
/**
 * @brief   状态转换
 */
void StateTrans(void)
{
	SourceOn();
	PumpOn();

	DeviceDataInit();
	GasDataInit();

	// 获取存储的数据
	SaveReadInit();

	// 获取存储的设置
	Lcd__LangSet(sDevice.pSave->Language);

	StateSelfCheck();

	ChargeOn();

	while (1)
	{
		// 获取信号量 20mS
		rt_sem_take(&sSemSystemTime, RT_WAITING_FOREVER);

		/* Reload IWDG counter */
		IWDG_ReloadCounter();

		KEY_Get();

		DeviceDispCount();
		DeviceTimeCount();


		switch (sState)
		{
			case STATE_SELF_CHECK:
				StateLedBzVbrCheck();
				SelfCheckJumpCheck();
				break;

			case STATE_DETECT:
				StateDetect(&sGas, &sDevice);
//				DisRecSet(0, 0, 127, 63);
				break;
			case STATE_MENU:
				MenuKey(gKeyShort);
				MenuNoOperateCountdown();
				// 闪烁
//				MenuBlink(&sDevice);

				break;

			case STATE_INPUT:
				StateInputKey(gKeyShort);
				// 闪烁
				if (sDevice.pTemp->Disp.Fresh == TURN_ON)
				{
					DisBlink();
				}
				break;

			case STATE_COUNTDOWN:
				StateCountdownKey(gKeyShort);
				StateCountdownSecond();
				break;

			case STATE_RESULT:
				StateResultKey(gKeyShort);
				break;

			case STATE_SHUTDOWN:
				StateShutdownKey(gKeyLong);
				StateShutdownSecond();
				break;

			case STATE_POWER_OFF:
				break;

			case STATE_INFO:
				StateInfoKey(gKeyShort);
				StateInfoSecond();
				break;

			case STATE_CHARGE:
//				PumpOff();
//				sDevice.pTemp->Fan.State = TURN_OFF;
				break;

			default:
				break;
		}

		if (sState != STATE_SELF_CHECK)
		{
			if (gKeyTrg)
			{
				S_Buzzer lBz;

				lBz.Src = BUZZER_KEY;
				lBz.Time = BUZZER_KEY_TIME;
				BuzzerOn(&lBz);
			}
		}

		if (sState != STATE_POWER_OFF)
		{
			if (gKeyTrg || gKeyLong)
			{
				PowerSaveBglFresh();
			}
		}

		if (gKeyTrg || gKeyLong)
		{
			MenuNoOperateFresh();
		}


		// 设备倒计时
		PowerSaveBglCountdown();
		LedCountdown();
		BuzzerCountdown();
		VibrationCountdown();
		StateBatCheck();
		StateChargeCheck();

	}
}


/**
 * @brief   获得气体结构体的指针
 *
 * @param   lpGas 气体结构体指针的地址
 */
void StateGasPointGet(S_Gas** lpGas)
{
	*lpGas = &sGas;
}


/**
 * @brief   获得设备结构体的指针
 *
 * @param   lpDev 设备结构体指针的地址
 */
void StateDevicePointGet(S_Device** lpDev)
{
	*lpDev = &sDevice;
}


/**
 * @brief   status handler
 */
void StateHandler(void)
{
//	gStatusFlag = TRUE;

	// 保证信号量最多就为1，是一个二值信号量
	if (sSemSystemTime.value == 0)
	{
		rt_sem_release(&sSemSystemTime);
	}

}


/**
 * @brief   state init
 */
void StateInit(void)
{
	// 初始化信号量
	rt_sem_init(&sSemSystemTime, "sem_system_time", 0, RT_IPC_FLAG_FIFO);
}
