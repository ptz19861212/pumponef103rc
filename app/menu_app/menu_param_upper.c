/**
 * @file    menu_param_upper.c
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

#include "menu_param_upper_in.h"

// 菜单的菜单项 英文
const char *sMenuParamUpperTxtItemEn[] =
{
		"",
};

// 菜单的菜单项 中文
const char *sMenuParamUpperTxtItemCn[] =
{
		"",
};

// 菜单的菜单项 指针数组
const char **sMenuParamUpperTxtItem[] =
{
		sMenuParamUpperTxtItemEn,
		sMenuParamUpperTxtItemCn,
};

// 菜单自身名字 英文
const char sMenuParamUpperTxtSelfEn[] = "Upper";

// 菜单自身名字 中文
const char sMenuParamUpperTxtSelfCn[] = "高报";

// 菜单自身名字
const char *sMenuParamUpperTxtSelf[] =
{
		sMenuParamUpperTxtSelfEn,
		sMenuParamUpperTxtSelfCn,
};

// 菜单的子菜单索引
const menu_t sMenuParamUpperChild[] =
{
		MENU_PARAM_ALARM_INDEX,
};

// 菜单的子菜单资源
const struct S_MenuResource *sMenuRsrParamUpperChild[] =
{
		&gMenuRsrParamUpper,
};

// 菜单 资源，包括自身字符串，菜单项字符串，菜单项的数目
const struct S_MenuResource gMenuRsrParamUpper =
{
	MENU_RESOURCE(sMenuParamUpperTxtItemEn,
					sMenuParamUpperChild,
					sMenuRsrParamUpperChild,
					sMenuParamUpperTxtSelf,
					sMenuParamUpperTxtItem)
};

/**
 * @brief   菜单初始化
 */
void MenuParamUpperPreInit(void)
{
}


/**
 * @brief   菜单初始化
 */
void MenuParamUpperInit(void)
{
	S_Gas* lpGas;
	StateGasPointGet(&lpGas);
	// 临时数值初始化
	lpGas->pTemp->AlarmSave.Upper = lpGas->pSave->Alarm.Upper;

	// 让第一行正常显示
	Lcd__MenuItemRev(0);

	S_Lcd__Unit lUnit;

	lUnit.Pos = 0;
	lUnit.Char = lpGas->pConst->Unit;
	Lcd__MenuUnitDisp(&lUnit);

	S_Value_Array_gas lValue;
	char lData[GAS_VALUE_ARRAY_SIZE];

	lValue.Char = lData;
	lValue.Value.Num = lpGas->pSave->Alarm.Upper;
	lValue.Value.Point = lpGas->pConst->Point;
	DecToStrU16(&lValue);

	S_Lcd__Item_Mid lTrig;

	lTrig.Item.Pos = 0;
	lTrig.Item.Char = lValue.Char;
	lTrig.Len = 11;

	Lcd__MenuItemMidDisp(&lTrig);
	// 反显第一行
	Lcd__MenuItemRev(0);
}


/**
 * @brief   输入函数数值获得
 */
void MenuParamUpperGet(void)
{
	S_Gas* lpGas;
	StateGasPointGet(&lpGas);

	S_Value_Input_Gas lValueInput;

	// 获取一级报警的上下限
	(*(FUNC_GAS_ALARM_LIMIT_GET)lpGas->pConst->vFunc.AlarmUpperLimitGet)
							(lpGas, &lValueInput);
	lValueInput.Point = lpGas->pConst->Point;
	ValueInputSetU16(&lValueInput);
}


/**
 * @brief   输入函数数值设置
 */
void MenuParamUpperSet(void)
{
	S_Gas* lpGas;
	StateGasPointGet(&lpGas);

	S_Value_Array_U16 lArray;

	ValueInputGetU16(&lArray);
	lpGas->pTemp->AlarmSave.Upper = lArray.Value.Num;
}

/**
 * @brief   输入函数保存的数值提取获得，用于初次进入的数值显示
 */
void MenuParamUpperValueGet(S_Value_U16* lpValue)
{
	S_Gas* lpGas;
	StateGasPointGet(&lpGas);

	lpValue->Num = lpGas->pTemp->AlarmSave.Upper;
	lpValue->Point = lpGas->pConst->Point;
}

/**
 * @brief   输入函数数值保存
 */
void MenuParamUpperSave(void)
{
	S_Gas* lpGas;
	StateGasPointGet(&lpGas);

	lpGas->pSave->Alarm.Upper = lpGas->pTemp->AlarmSave.Upper;
	lpGas->pSave->Save_Bits.Upper = FLASH_SAVE_TRUE;
}


/**
 * @brief   输入函数数值保存
 */
void MenuParamUpperConfirm(E_TrueState lTrue)
{
	StateInputToMenu();
}


/**
 * @brief   进入子菜单
 */
void MenuParamUpperChild(void)
{
	S_InputValue lInput;

//	struct S_Gas* lpGas;
//	StateGasPointGet(&lpGas);

//	lInput.Value.Num = lpGas->pSave->Alarm.Upper;
//	lInput.Value.Point = lpGas->pConst->Point;
	lInput.Func.LimitGet = MenuParamUpperGet;
	lInput.Func.Set = MenuParamUpperSet;
//	lInput.Func.ValueGet = (MY_FUNC)MenuParamUpperValueGet;
	lInput.Func.ValueGet = MenuParamUpperValueGet;
	lInput.Func.Save = MenuParamUpperSave;
	lInput.Func.Confirm = MenuParamUpperConfirm;
	StateInputValueInit(&lInput);
	StateMenuToInput();
}


/**
 * @brief   进入父菜单
 */
void MenuParamUpperParent(void)
{
	MenuKeyParent();
	MenuDisp();
}


/**
 * @brief   下一条菜单项
 */
void MenuParamUpperNext(void)
{
	MenuKeyNext();

}


/**
 * @brief   上一条菜单项
 */
void MenuParamUpperPrev(void)
{
	MenuKeyPrev();
}


