/**
 * @file    menu_param_alarm.c
 * @brief   根菜单
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

#include "menu_param_alarm_in.h"

// 菜单的菜单项 英文
const char *sMenuParamAlarmTxtItemEn[] =
{
		"Sound",
		"Vibration",
};

// 菜单的菜单项 中文
const char *sMenuParamAlarmTxtItemCn[] =
{
//		"sound",
//		"vibration",
			"声音设置",
			"振动设置",
};

// 菜单的菜单项 指针数组
const char **sMenuParamAlarmTxtItem[] =
{
		sMenuParamAlarmTxtItemEn,
		sMenuParamAlarmTxtItemCn,
};

// 菜单自身名字 英文
const char sMenuParamAlarmTxtSelfEn[] = "Alarm";

// 菜单自身名字 中文
const char sMenuParamAlarmTxtSelfCn[] = "报警";

// 菜单自身名字
const char *sMenuParamAlarmTxtSelf[] =
{
		sMenuParamAlarmTxtSelfEn,
		sMenuParamAlarmTxtSelfCn,
};

// 菜单的子菜单索引
const menu_t sMenuParamAlarmChild[] =
{
		MENU_PARAM_ALARM_SOUND_INDEX,
		MENU_PARAM_ALARM_VIBRATION_INDEX,
};

// 菜单的子菜单资源
const struct S_MenuResource *sMenuRsrParamAlarmChild[] =
{
//		(const struct S_MenuResource*)&gMenuRsrParamAlarmSound,
//		(const struct S_MenuResource*)&gMenuRsrParamAlarmVibration,
		&gMenuRsrParamAlarmSound,
		&gMenuRsrParamAlarmVibration,
};

// 菜单 资源，包括自身字符串，菜单项字符串，菜单项的数目
const struct S_MenuResource gMenuRsrParamAlarm =
{
	MENU_RESOURCE(sMenuParamAlarmTxtItemEn,
					sMenuParamAlarmChild,
					sMenuRsrParamAlarmChild,
					sMenuParamAlarmTxtSelf,
					sMenuParamAlarmTxtItem)
};


/**
 * @brief   菜单初始化
 */
void MenuParamAlarmPreInit(void)
{
}


/**
 * @brief   菜单初始化
 */
void MenuParamAlarmInit(void)
{
}


/**
 * @brief   进入子菜单
 */
void MenuParamAlarmChild(void)
{
	MenuKeyChild();
	MenuDisp();
	// 这个是为了进入设置模式
	MenuLoadInit();
//	MenuDisposeEntry();
//	MenuDisposeDisp();
}


/**
 * @brief   进入父菜单
 */
void MenuParamAlarmParent(void)
{
	MenuKeyParent();
	MenuDisp();
}


/**
 * @brief   下一条菜单项
 */
void MenuParamAlarmNext(void)
{
	MenuKeyNext();

}


/**
 * @brief   上一条菜单项
 */
void MenuParamAlarmPrev(void)
{
	MenuKeyPrev();
}
