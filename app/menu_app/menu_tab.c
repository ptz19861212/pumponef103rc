/**
 * @file    menu_tab.c
 * @brief   菜单表
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

#include "menu_tab_in.h"



// 菜单对应的按键函数
const S_MenuTab gMenuTab[] =
{
		MENU_KEY_TAB(ROOT, Root),
		MENU_KEY_TAB(PARAM, Param),
		MENU_KEY_TAB(CALI, Cali),
		MENU_KEY_TAB(TIME, Time),
		MENU_KEY_TAB(RESTORE, Restore),
		MENU_KEY_TAB(MANUF, Manuf),
		MENU_KEY_TAB(DEBUG, Debug),
		MENU_KEY_TAB(USER, User),
		MENU_KEY_TAB(PARAM_ALARM, ParamAlarm),
		MENU_KEY_TAB(PARAM_UPPER, ParamUpper),
		MENU_KEY_TAB(PARAM_LOWER, ParamLower),
		MENU_KEY_TAB(PARAM_STEL, ParamStel),
		MENU_KEY_TAB(PARAM_TWA, ParamTwa),
		MENU_KEY_TAB(PARAM_PUMP, ParamPump),
		MENU_KEY_TAB(PARAM_BAK, ParamBak),
//		MENU_KEY_TAB(CALI_ZERO, CaliZero),
//		MENU_KEY_TAB(CALI_COEFF, CaliCoeff),
		MENU_KEY_TAB(ROOT, Root),
		MENU_KEY_TAB(ROOT, Root),
		MENU_KEY_TAB(RST_PARAM, RestoreParam),
		MENU_KEY_TAB(RST_CALI, RestoreCali),
		MENU_KEY_TAB(DEBUG_ZERO, DebugZero),
		MENU_KEY_TAB(DEBUG_COEFF, DebugCoeff),
		MENU_KEY_TAB(DEBUG_REF1, DebugRef1),
		MENU_KEY_TAB(DEBUG_REF2, DebugRef2),
		MENU_KEY_TAB(DEBUG_BUILD, DebugBuild),
		MENU_KEY_TAB(USER_GROUP, UserGroup),
		MENU_KEY_TAB(USER_UPGRADE, UserUpgrade),
		MENU_KEY_TAB(USER_DEGRADE, UserDegrade),
		MENU_KEY_TAB(PARAM_ALARM_SOUND, ParamAlarmSound),
		MENU_KEY_TAB(PARAM_ALARM_VIBRATION, ParamAlarmVibration),
		MENU_KEY_TAB(PARAM_LANGUAGE, ParamLanguage),
};
