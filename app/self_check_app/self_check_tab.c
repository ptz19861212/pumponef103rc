/**
 * @file    self_check_tab.c
 * @brief   自检表
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

#include "self_check_tab_in.h"



// 自检对应的函数
const S_SelfCheckTab gSelfCheckTab[] =
{
		SELF_CHECK_KEY_TAB(ROOT, Root),
		SELF_CHECK_KEY_TAB(SAMPLE, Sample),
		SELF_CHECK_KEY_TAB(VERSION, Version),
		SELF_CHECK_KEY_TAB(BUILD_DATE, BuildDate),
		SELF_CHECK_KEY_TAB(BUILD_TIME, BuildTime),
		SELF_CHECK_KEY_TAB(MANF_DATE, ManfDate),
		SELF_CHECK_KEY_TAB(WARRANTY_DATE, WarrantyDate),
		SELF_CHECK_KEY_TAB(GAS_NAME, GasName),
		SELF_CHECK_KEY_TAB(CALI_DATE, CaliDate),
		SELF_CHECK_KEY_TAB(CALI_TIME, CaliTime),
		SELF_CHECK_KEY_TAB(ALARM_UPPER, AlarmUpper),
		SELF_CHECK_KEY_TAB(ALARM_LOWER, AlarmLower),
		SELF_CHECK_KEY_TAB(ALARM_STEL, AlarmStel),
		SELF_CHECK_KEY_TAB(ALARM_TWA, AlarmTwa),
		SELF_CHECK_KEY_TAB(ALARM_SOUND, AlarmSound),
		SELF_CHECK_KEY_TAB(ALARM_VIBRATION, AlarmVibration),
		SELF_CHECK_KEY_TAB(USR_GROUP, UsrGroup),
		SELF_CHECK_KEY_TAB(END, End),
		SELF_CHECK_KEY_TAB(GAS_RANGE, GasRange),
};
