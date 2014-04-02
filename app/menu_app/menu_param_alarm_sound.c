/**
 * @file    menu_param_alarm_sound.c
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

#include "menu_param_alarm_sound_in.h"

// 菜单的菜单项 英文
const char *sMenuParamAlarmSoundTxtItemEn[] =
{
		"",
};

// 菜单的菜单项 中文
const char *sMenuParamAlarmSoundTxtItemCn[] =
{
		"",
};

// 菜单的菜单项 指针数组
const char **sMenuParamAlarmSoundTxtItem[] =
{
		sMenuParamAlarmSoundTxtItemEn,
		sMenuParamAlarmSoundTxtItemCn,
};

// 菜单自身名字 英文
const char sMenuParamAlarmSoundTxtSelfEn[] = "Sound";

// 菜单自身名字 中文
const char sMenuParamAlarmSoundTxtSelfCn[] = "声音";

// 菜单自身名字
const char *sMenuParamAlarmSoundTxtSelf[] =
{
		sMenuParamAlarmSoundTxtSelfEn,
		sMenuParamAlarmSoundTxtSelfCn,
};

// 菜单的子菜单索引
const menu_t sMenuParamAlarmSoundChild[] =
{
		MENU_PARAM_ALARM_INDEX,
};

// 菜单的子菜单资源
const struct S_MenuResource *sMenuRsrParamAlarmSoundChild[] =
{
		&gMenuRsrParamAlarmSound,
};

// 菜单 资源，包括自身字符串，菜单项字符串，菜单项的数目
const struct S_MenuResource gMenuRsrParamAlarmSound =
{
	MENU_RESOURCE(sMenuParamAlarmSoundTxtItemEn,
					sMenuParamAlarmSoundChild,
					sMenuRsrParamAlarmSoundChild,
					sMenuParamAlarmSoundTxtSelf,
					sMenuParamAlarmSoundTxtItem)
};


/**
 * @brief   菜单初始化
 */
void MenuParamAlarmSoundPreInit(void)
{
}


/**
 * @brief   菜单初始化
 */
void MenuParamAlarmSoundInit(void)
{
//	struct S_Gas* lpGas;
//	StateGasPointGet(&lpGas);
	S_Device* lpDev;
	StateDevicePointGet(&lpDev);

	// 临时数值初始化
//	lpGas->pTemp->AlarmSave.AlarmSound = lpGas->pSave->Alarm.AlarmSound;

	// 让第一行正常显示
	Lcd__MenuItemRev(0);

//	S_Lcd__Unit lUnit;

//	lUnit.Pos = 0;
//	lUnit.Char = lpGas->pConst->Unit;
//	Lcd__MenuUnitDisp(&lUnit);

//	S_Value_Array_gas lValue;
//	char lData[GAS_VALUE_ARRAY_SIZE];

//	lValue.Char = lData;
//	lValue.Value.Num = lpGas->pSave->Alarm.AlarmSound;
//	lValue.Value.Num = lpGas->pTemp->AlarmSave.Lower;
//	lValue.Value.Point = lpGas->pConst->Point;
//	DecToStrU16(&lValue);

	E_Language lLang;

	// 获得当前显示的语言
	lLang = Lcd__LangGet();

	S_Lcd__Item_Mid lTrig;

	lTrig.Item.Pos = 0;
//	lTrig.Item.Char = lValue.Char;
	if (lpDev->pSave->Sound == TURN_OFF)
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
//	MenuDisposeValueDisp16(lpGas->pSave->Alarm.Lower, lpGas->pConst->Point,
//								CONFIG_PARAM_LOWER_ENTER_LINE_INIT);
//	rt_kprintf("x = %d\ty = %d\n", gLcdScreen.PE.X, gLcdScreen.PE.Y);
}


/**
 * @brief   输入函数数值获得
 */
//void MenuParamAlarmSoundGet(void)
//{
//	struct S_Gas* lpGas;
//	StateGasPointGet(&lpGas);
//
//	S_Value_Input_Gas lValueInput;
//
//	// 获取一级报警的上下限
//	(*(FUNC_GAS_ALARM_LIMIT_GET)lpGas->pConst->vFuncAlarmLowerLimitGet)
//							(lpGas, &lValueInput);
//	lValueInput.Point = lpGas->pConst->Point;
//	ValueInputSetU16(&lValueInput);
//}


/**
 * @brief   输入函数数值设置
 */
//void MenuParamAlarmSoundSet(void)
//{
//	struct S_Gas* lpGas;
//	StateGasPointGet(&lpGas);
//
//	S_Value_Array_U16 lArray;
//
//	ValueInputGetU16(&lArray);
//	lpGas->pTemp->AlarmSave.Lower = lArray.Value.Num;
////	lpGas->pSave->Alarm.Lower = lArray.Value.Num;
////	lpGas->pSave->Save_Bits.Lower = FLASH_SAVE_TRUE;
//}

/**
 * @brief   输入函数保存的数值提取获得，用于初次进入的数值显示
 */
void MenuParamAlarmSoundBinaryGet(E_TurnState* lpState)
{
	S_Device* lpDev;
	StateDevicePointGet(&lpDev);

	*lpState = lpDev->pSave->Sound;
}

/**
 * @brief   输入函数数值保存
 */
void MenuParamAlarmSoundSave(E_TurnState lTurn)
{
	S_Device* lpDev;
	StateDevicePointGet(&lpDev);

	lpDev->pSave->Sound = lTurn;
	lpDev->pSave->Save_Bits.Snd = FLASH_SAVE_TRUE;

//	StateInputToMenu();
}


/**
 * @brief   输入函数数值保存
 */
void MenuParamAlarmSoundConfirm(E_TurnState lTurn)
{
	StateInputToMenu();
}


/**
 * @brief   进入子菜单
 */
void MenuParamAlarmSoundChild(void)
{
//	MenuKeyChild();
//	MenuDisp();
//	S_InputValue lInput;
	S_InputBinary lInput;

//	struct S_Gas* lpGas;
//	StateGasPointGet(&lpGas);

//	struct S_Device* lpDev;
//	StateDevicePointGet(&lpDev);

//	lInput.Value.Num = lpGas->pTemp->AlarmSave.Lower;
//	lInput.Value.Num = lpGas->pSave->Alarm.Lower;
//	lInput.Value.Point = lpGas->pConst->Point;
//	lInput.Func.Get = MenuParamLowerGet;
//	lInput.Func.Set = MenuParamLowerSet;
//	lInput.Func.ValueGet = (MY_FUNC)MenuParamLowerValueGet;
	lInput.Func.BinaryGet = MenuParamAlarmSoundBinaryGet;
	lInput.Func.Save = MenuParamAlarmSoundSave;
	lInput.Func.Confirm = MenuParamAlarmSoundConfirm;
	lInput.State = BINARY_ONOFF;
//	StateInputValueInit(&lInput);
	StateInputBinaryInit(&lInput);
	StateMenuToInput();
}


/**
 * @brief   进入父菜单
 */
void MenuParamAlarmSoundParent(void)
{
	MenuKeyParent();
	MenuDisp();
}


/**
 * @brief   下一条菜单项
 */
void MenuParamAlarmSoundNext(void)
{
	MenuKeyNext();

}


/**
 * @brief   上一条菜单项
 */
void MenuParamAlarmSoundPrev(void)
{
	MenuKeyPrev();
}
