/**
 * @file    menu_param_alarm_vibration.c
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

#include "menu_param_alarm_vibration_in.h"

// 菜单的菜单项 英文
const char *sMenuParamAlarmVibrationTxtItemEn[] =
{
		"",
};

// 菜单的菜单项 中文
const char *sMenuParamAlarmVibrationTxtItemCn[] =
{
		"",
};

// 菜单的菜单项 指针数组
const char **sMenuParamAlarmVibrationTxtItem[] =
{
		sMenuParamAlarmVibrationTxtItemEn,
		sMenuParamAlarmVibrationTxtItemCn,
};

// 菜单自身名字 英文
const char sMenuParamAlarmVibrationTxtSelfEn[] = "Vibr";

// 菜单自身名字 中文
const char sMenuParamAlarmVibrationTxtSelfCn[] = "振动";

// 菜单自身名字
const char *sMenuParamAlarmVibrationTxtSelf[] =
{
		sMenuParamAlarmVibrationTxtSelfEn,
		sMenuParamAlarmVibrationTxtSelfCn,
};

// 菜单的子菜单索引
const menu_t sMenuParamAlarmVibrationChild[] =
{
		MENU_PARAM_ALARM_INDEX,
};

// 菜单的子菜单资源
const struct S_MenuResource *sMenuRsrParamAlarmVibrationChild[] =
{
		&gMenuRsrParamAlarmVibration,
};

// 菜单 资源，包括自身字符串，菜单项字符串，菜单项的数目
const struct S_MenuResource gMenuRsrParamAlarmVibration =
{
	MENU_RESOURCE(sMenuParamAlarmVibrationTxtItemEn,
					sMenuParamAlarmVibrationChild,
					sMenuRsrParamAlarmVibrationChild,
					sMenuParamAlarmVibrationTxtSelf,
					sMenuParamAlarmVibrationTxtItem)
};


/**
 * @brief   菜单初始化
 */
void MenuParamAlarmVibrationPreInit(void)
{
}


/**
 * @brief   菜单初始化
 */
void MenuParamAlarmVibrationInit(void)
{
	S_Device* lpDev;
	StateDevicePointGet(&lpDev);

	// 让第一行正常显示
	Lcd__MenuItemRev(0);

	E_Language lLang;

	// 获得当前显示的语言
	lLang = Lcd__LangGet();

	S_Lcd__Item_Mid lTrig;

	lTrig.Item.Pos = 0;
	if (lpDev->pSave->Vibration == TURN_OFF)
	{
//		lTrig.Item.Char = *(gInputOnOff[lLang] + 1);
		lTrig.Item.Char = *(*(*(gInputBinary + BINARY_ONOFF) + lLang) + 1);
	}
	else
	{
//		lTrig.Item.Char = *(gInputOnOff[lLang]);
		lTrig.Item.Char = *(*(*(gInputBinary + BINARY_ONOFF) + lLang));
	}

	// 注意右有滚动条
	lTrig.Len = 15;

	Lcd__MenuItemMidDisp(&lTrig);
	// 反显第一行
	Lcd__MenuItemRev(0);
}


/**
 * @brief   输入函数保存的数值提取获得，用于初次进入的数值显示
 */
void MenuParamAlarmVibrationBinaryGet(E_TurnState* lpState)
{
	S_Device* lpDev;
	StateDevicePointGet(&lpDev);

	*lpState = lpDev->pSave->Vibration;
}


/**
 * @brief   输入函数数值保存
 */
void MenuParamAlarmVibrationSave(E_TurnState lTurn)
{
	S_Device* lpDev;
	StateDevicePointGet(&lpDev);

	lpDev->pSave->Vibration = lTurn;
	lpDev->pSave->Save_Bits.Vbr = FLASH_SAVE_TRUE;

//	StateInputToMenu();
}


/**
 * @brief   输入函数数值保存
 */
void MenuParamAlarmVibrationConfirm(E_TurnState lTurn)
{
	StateInputToMenu();
}


/**
 * @brief   进入子菜单
 */
void MenuParamAlarmVibrationChild(void)
{
	S_InputBinary lInput;

	lInput.Func.BinaryGet = MenuParamAlarmVibrationBinaryGet;
	lInput.Func.Save = MenuParamAlarmVibrationSave;
	lInput.Func.Confirm = MenuParamAlarmVibrationConfirm;
	lInput.State = BINARY_ONOFF;
	StateInputBinaryInit(&lInput);
	StateMenuToInput();
}


/**
 * @brief   进入父菜单
 */
void MenuParamAlarmVibrationParent(void)
{
	MenuKeyParent();
	MenuDisp();
}


/**
 * @brief   下一条菜单项
 */
void MenuParamAlarmVibrationNext(void)
{
	MenuKeyNext();

}


/**
 * @brief   上一条菜单项
 */
void MenuParamAlarmVibrationPrev(void)
{
	MenuKeyPrev();
}
