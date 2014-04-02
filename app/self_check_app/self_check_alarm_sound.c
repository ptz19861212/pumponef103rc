/**
 * @file    self_check_alarm_sound.c
 * @brief   报警蜂鸣器自检
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

#include "self_check_alarm_sound_in.h"

// 报警蜂鸣器自检的自检项 英文
const char *sSelfCheckAlarmSoundTxtEn[] =
{
		"Alarm Sound",
		"",
};

// 报警蜂鸣器自检的自检项 中文
const char *sSelfCheckAlarmSoundTxtCn[] =
{
		"报警声音",
		"",
};

// 报警蜂鸣器自检的自检项 指针数组
const char **sSelfCheckAlarmSoundTxt[] =
{
		sSelfCheckAlarmSoundTxtEn,
		sSelfCheckAlarmSoundTxtCn,
};


// 报警蜂鸣器自检的下一个自检资源
const struct S_SelfCheckResource* sSelfCheckRsrAlarmSoundNext =
											&gSelfCheckRsrAlarmSound;

// 报警蜂鸣器自检 资源，包括自身字符串，自检项字符串，自检项的数目
const struct S_SelfCheckResource gSelfCheckRsrAlarmSound =
{
		SELF_CHECK_RESOURCE(ALARM_SOUND, AlarmSound, AlarmVibration)
};


/**
 * @brief   自检初始化
 */
void SelfCheckAlarmSoundInit(void)
{
	// 报警蜂鸣器自检资源初始化
//
//	S_Device* lpDev;
//	StateDevicePointGet(&lpDev);
//
//	S_Lcd__Item_Mid lTrig;
//
//	lTrig.Item.Pos = CONFIG_ALARM_SOUND_POS;
//	lTrig.Item.Char = lpDev->pConst->Version.Date;
//	lTrig.Len = CONFIG_ALARM_SOUND_LEN;
//	Lcd__FrameItemMidDisp(&lTrig);


	S_Device* lpDev;
	StateDevicePointGet(&lpDev);

	E_Language lLang;

	// 获得当前显示的语言
	lLang = Lcd__LangGet();

	S_Lcd__Item_Mid lTrig;

	lTrig.Item.Pos = CONFIG_ALARM_SOUND_POS;
	if (lpDev->pSave->Sound == TURN_OFF)
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
	lTrig.Len = CONFIG_ALARM_SOUND_LEN;

	Lcd__MenuItemMidDisp(&lTrig);
}

