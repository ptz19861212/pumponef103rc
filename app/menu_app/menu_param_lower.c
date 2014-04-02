/**
 * @file    menu_param_lower.c
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

#include "menu_param_lower_in.h"

// 菜单的菜单项 英文
const char *sMenuParamLowerTxtItemEn[] =
{
		"",
};

// 菜单的菜单项 中文
const char *sMenuParamLowerTxtItemCn[] =
{
		"",
};

// 菜单的菜单项 指针数组
const char **sMenuParamLowerTxtItem[] =
{
		sMenuParamLowerTxtItemEn,
		sMenuParamLowerTxtItemCn,
};

// 菜单自身名字 英文
const char sMenuParamLowerTxtSelfEn[] = "Lower";

// 菜单自身名字 中文
const char sMenuParamLowerTxtSelfCn[] = "低报";

// 菜单自身名字
const char *sMenuParamLowerTxtSelf[] =
{
		sMenuParamLowerTxtSelfEn,
		sMenuParamLowerTxtSelfCn,
};

// 菜单的子菜单索引
const menu_t sMenuParamLowerChild[] =
{
		MENU_PARAM_ALARM_INDEX,
};

// 菜单的子菜单资源
const struct S_MenuResource *sMenuRsrParamLowerChild[] =
{
		&gMenuRsrParamLower,
};

// 菜单 资源，包括自身字符串，菜单项字符串，菜单项的数目
const struct S_MenuResource gMenuRsrParamLower =
{
	MENU_RESOURCE(sMenuParamLowerTxtItemEn,
					sMenuParamLowerChild,
					sMenuRsrParamLowerChild,
					sMenuParamLowerTxtSelf,
					sMenuParamLowerTxtItem)
};

/**
 * @brief   菜单初始化
 */
void MenuParamLowerPreInit(void)
{
}


/**
 * @brief   菜单初始化
 */
void MenuParamLowerInit(void)
{
	S_Gas* lpGas;
	StateGasPointGet(&lpGas);
	// 临时数值初始化
	lpGas->pTemp->AlarmSave.Lower = lpGas->pSave->Alarm.Lower;

	// 让第一行正常显示
	Lcd__MenuItemRev(0);

	S_Lcd__Unit lUnit;

	lUnit.Pos = 0;
	lUnit.Char = lpGas->pConst->Unit;
	Lcd__MenuUnitDisp(&lUnit);

	S_Value_Array_gas lValue;
	char lData[GAS_VALUE_ARRAY_SIZE];

	lValue.Char = lData;
	lValue.Value.Num = lpGas->pSave->Alarm.Lower;
//	lValue.Value.Num = lpGas->pTemp->AlarmSave.Lower;
	lValue.Value.Point = lpGas->pConst->Point;
	DecToStrU16(&lValue);

	S_Lcd__Item_Mid lTrig;

	lTrig.Item.Pos = 0;
	lTrig.Item.Char = lValue.Char;
	lTrig.Len = 11;

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
void MenuParamLowerGet(void)
{
	S_Gas* lpGas;
	StateGasPointGet(&lpGas);

	S_Value_Input_Gas lValueInput;

	// 获取一级报警的上下限
	(*(FUNC_GAS_ALARM_LIMIT_GET)lpGas->pConst->vFunc.AlarmLowerLimitGet)
							(lpGas, &lValueInput);
	lValueInput.Point = lpGas->pConst->Point;
	ValueInputSetU16(&lValueInput);
}


/**
 * @brief   输入函数数值设置
 */
void MenuParamLowerSet(void)
{
	S_Gas* lpGas;
	StateGasPointGet(&lpGas);

	S_Value_Array_U16 lArray;

	ValueInputGetU16(&lArray);
	lpGas->pTemp->AlarmSave.Lower = lArray.Value.Num;
//	lpGas->pSave->Alarm.Lower = lArray.Value.Num;
//	lpGas->pSave->Save_Bits.Lower = FLASH_SAVE_TRUE;
}

/**
 * @brief   输入函数保存的数值提取获得，用于初次进入的数值显示
 */
void MenuParamLowerValueGet(S_Value_U16* lpValue)
{
	S_Gas* lpGas;
	StateGasPointGet(&lpGas);

//	lpValue->Num = lpGas->pSave->Alarm.Lower;
	lpValue->Num = lpGas->pTemp->AlarmSave.Lower;
	lpValue->Point = lpGas->pConst->Point;
}


/**
 * @brief   输入函数数值保存
 */
void MenuParamLowerSave(void)
{
	S_Gas* lpGas;
	StateGasPointGet(&lpGas);

	lpGas->pSave->Alarm.Lower = lpGas->pTemp->AlarmSave.Lower;
	lpGas->pSave->Save_Bits.Lower = FLASH_SAVE_TRUE;
}


/**
 * @brief   输入函数数值保存
 */
void MenuParamLowerConfirm(E_TrueState lTrue)
{
	StateInputToMenu();
}


/**
 * @brief   进入子菜单
 */
void MenuParamLowerChild(void)
{
//	MenuKeyChild();
//	MenuDisp();
	S_InputValue lInput;

//	struct S_Gas* lpGas;
//	StateGasPointGet(&lpGas);

//	lInput.Value.Num = lpGas->pTemp->AlarmSave.Lower;
//	lInput.Value.Num = lpGas->pSave->Alarm.Lower;
//	lInput.Value.Point = lpGas->pConst->Point;
	lInput.Func.LimitGet = MenuParamLowerGet;
	lInput.Func.Set = MenuParamLowerSet;
//	lInput.Func.ValueGet = (MY_FUNC)MenuParamLowerValueGet;
	lInput.Func.ValueGet = MenuParamLowerValueGet;
	lInput.Func.Save = MenuParamLowerSave;
	lInput.Func.Confirm = MenuParamLowerConfirm;
	StateInputValueInit(&lInput);
	StateMenuToInput();
}


/**
 * @brief   进入父菜单
 */
void MenuParamLowerParent(void)
{
	MenuKeyParent();
	MenuDisp();
}


/**
 * @brief   下一条菜单项
 */
void MenuParamLowerNext(void)
{
	MenuKeyNext();

}


/**
 * @brief   上一条菜单项
 */
void MenuParamLowerPrev(void)
{
	MenuKeyPrev();
}


