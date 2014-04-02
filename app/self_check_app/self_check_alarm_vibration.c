/**
 * @file    self_check_alarm_vibration.c
 * @brief   报警震动自检
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-12-02 13:34:47 星期一 
 * @history (1).2013-12-02 13:34:47 星期一 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#include "self_check_alarm_vibration_in.h"

// 报警震动自检的自检项 英文
const char *sSelfCheckAlarmVibrationTxtEn[] =
{
		"Alarm Vibration",
		"",
};

// 报警震动自检的自检项 中文
const char *sSelfCheckAlarmVibrationTxtCn[] =
{
		"报警振动",
		"",
};

// 报警震动自检的自检项 指针数组
const char **sSelfCheckAlarmVibrationTxt[] =
{
		sSelfCheckAlarmVibrationTxtEn,
		sSelfCheckAlarmVibrationTxtCn,
};


// 报警震动自检的下一个自检资源
const struct S_SelfCheckResource* sSelfCheckRsrAlarmVibrationNext =
											&gSelfCheckRsrAlarmVibration;

// 报警震动自检 资源，包括自身字符串，自检项字符串，自检项的数目
const struct S_SelfCheckResource gSelfCheckRsrAlarmVibration =
{
		SELF_CHECK_RESOURCE(ALARM_VIBRATION, AlarmVibration,
//								UsrGroup)
								End)
};


/**
 * @brief   自检初始化
 */
void SelfCheckAlarmVibrationInit(void)
{
	// 报警震动自检资源初始化

	S_Device* lpDev;
	StateDevicePointGet(&lpDev);

	E_Language lLang;

	// 获得当前显示的语言
	lLang = Lcd__LangGet();

	S_Lcd__Item_Mid lTrig;

	lTrig.Item.Pos = CONFIG_ALARM_VIBRATION_POS;
	if (lpDev->pSave->Vibration == TURN_OFF)
	{
//		lTrig.Item.Char = *(gInputOnOff[lLang] + 1);
		lTrig.Item.Char = *(*(*(gInputBinary + BINARY_ONOFF) +
								lLang) + 1);
	}
	else
	{
//		lTrig.Item.Char = *(gInputOnOff[lLang]);
		lTrig.Item.Char = *(*(*(gInputBinary + BINARY_ONOFF) +
								lLang));
	}

	// 注意右有滚动条
	lTrig.Len = CONFIG_ALARM_VIBRATION_LEN;

	Lcd__MenuItemMidDisp(&lTrig);
}

