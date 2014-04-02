/**
 * @file    menu_cali.c
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

#include "menu_cali_in.h"

// 菜单的菜单项 英文
const char *sMenuCaliTxtItemEn[] =
{
		"Zero",
		"Coeff",
};

// 菜单的菜单项 中文
const char *sMenuCaliTxtItemCn[] =
{
//		"zero",
//		"coeff",
			"零点校准",
			"系数校准",
};

// 菜单的菜单项 指针数组
const char **sMenuCaliTxtItem[] =
{
		sMenuCaliTxtItemEn,
		sMenuCaliTxtItemCn,
};

// 菜单自身名字 英文
const char sMenuCaliTxtSelfEn[] = "Cali";

// 菜单自身名字 中文
const char sMenuCaliTxtSelfCn[] = "校准";

// 菜单自身名字
const char *sMenuCaliTxtSelf[] =
{
		sMenuCaliTxtSelfEn,
		sMenuCaliTxtSelfCn,
};

// 菜单的子菜单索引
const menu_t sMenuCaliChild[] =
{
//		MENU_CALI_ZERO_INDEX,
//		MENU_CALI_COEFF_INDEX,
		MENU_CALI_INDEX,
};

// 菜单的子菜单资源
const struct S_MenuResource *sMenuRsrCaliChild[] =
{
//		&gMenuRsrCaliZero,
//		&gMenuRsrCaliCoeff,
		&gMenuRsrCali,
};

// 菜单 资源，包括自身字符串，菜单项字符串，菜单项的数目
const struct S_MenuResource gMenuRsrCali =
{
	MENU_RESOURCE(sMenuCaliTxtItemEn,
					sMenuCaliChild,
					sMenuRsrCaliChild,
					sMenuCaliTxtSelf,
					sMenuCaliTxtItem)
};


///**
// * @brief   菜单初始化
// */
//void MenuCaliPreInit(void)
//{
//}
//
//
///**
// * @brief   菜单初始化
// */
//void MenuCaliInit(void)
//{
//}
//
//
///**
// * @brief   进入子菜单
// */
//void MenuCaliChild(void)
//{
//	MenuKeyChild();
//	MenuDisp();
//}


/**
 * @brief   菜单初始化
 */
void MenuCaliPreInit(void)
{
}


/**
 * @brief   菜单初始化
 */
void MenuCaliInit(void)
{
//	struct S_Device* lpDev;
//	StateDevicePointGet(&lpDev);
//
//	// 让第一行正常显示
//	Lcd__MenuItemRev(0);
//
//	E_Language lLang;
//
//	// 获得当前显示的语言
//	lLang = Lcd__LangGet();
//
//	S_Lcd__Item_Mid lTrig;
//
//	lTrig.Item.Pos = 0;
//	if (lpDev->pSave->Vibration == TURN_OFF)
//	{
////		lTrig.Item.Char = *(gInputOnOff[lLang] + 1);
//		lTrig.Item.Char = *(*(*(gInputBinary + BINARY_ONOFF) + lLang) + 1);
//	}
//	else
//	{
////		lTrig.Item.Char = *(gInputOnOff[lLang]);
//		lTrig.Item.Char = *(*(*(gInputBinary + BINARY_ONOFF) + lLang));
//	}
//
//	// 注意右有滚动条
//	lTrig.Len = 16;
//
//	Lcd__MenuItemMidDisp(&lTrig);
//	// 反显第一行
//	Lcd__MenuItemRev(0);
}

// 标零字符串 英文
const char *sCaliZeroEn[] =
{
		"Cali Zero",
};

// 标零字符串 中文
const char *sCaliZeroCn[] =
{
		"校准零点",
};

// 标零字符串 指针数组
const char **sCaliZeroTxt[] =
{
		sCaliZeroEn,
		sCaliZeroCn,
};

// 标气字符串 英文
const char *sCaliCoeffEn[] =
{
		"Cali Coeff",
};

// 标气字符串 中文
const char *sCaliCoeffCn[] =
{
		"校准系数",
};

// 标气字符串 指针数组
const char **sCaliCoeffTxt[] =
{
		sCaliCoeffEn,
		sCaliCoeffCn,
};

/****************************** 标零 **********************************/

/**
 * @brief   输入函数保存的数值提取获得，用于初次进入的数值显示
 */
void MenuCaliBinaryGet(E_TurnState* lpState)
{
//	struct S_Device* lpDev;
//	StateDevicePointGet(&lpDev);
//
//	*lpState = lpDev->pSave->Vibration;
	*lpState = E_TRUE;
}


/**
 * @brief   获得倒计时时间中的ADC数值
 */
void MenuCaliCountdownValueGetZero(S_Value_U16* lpValue)
{
	S_Gas* lpGas;
	StateGasPointGet(&lpGas);

//	lpValue->Num = lpGas->pSave->Alarm.Lower;
	lpValue->Num = lpGas->pTemp->Point.Adc;
	lpValue->Point = POINT_HHHHH;
}

static uint32_t sCaliAdcSum;

/**
 * @brief   倒计时时间中的ADC数值存储相加
 */
void MenuCaliCountdownValueSetZero(S_Value_U16* lpValue)
{
	sCaliAdcSum += lpValue->Num;
//	rt_kprintf("adc = %d\n", lpValue->Num);
}


/**
 * @brief   倒计时结束的ADC数值计算求平均
 */
void MenuCaliCountdownValueCalcuZero(void)
{
	S_Gas* lpGas;
	StateGasPointGet(&lpGas);

//	S_Gas_Cali_Coeff lCali;
//
//	// 加上10是因为要除20,能够四舍五入
//	sCaliAdcSum += 10;
//	lCali.AdcNow = sCaliAdcSum / 20;
//
////	rt_kprintf("adccalcu = %d\n", lCali.AdcNow);
//
//	lCali.AdcZero = lpGas->pConst->AdcZero;
//	lCali.Threshold = lpGas->pConst->CaliCoeffThrs;
//
//	if (lpGas->pConst->Direct == GAS_DIRECT_POSITIVE)
//	{
//		GasCaliCoeffGetPositive(&lCali, &(lpGas->pSave->Ref1));
//	}
//	else if (lpGas->pConst->Direct == GAS_DIRECT_NEGATIVE)
//	{
//		GasCaliCoeffGetNegative(&lCali, &(lpGas->pSave->Ref3));
//	}
//	else
//	{
//		GasCaliCoeffGetBoth(&lCali, &(lpGas->pSave->Ref3));
//	}


	S_Gas_Cali_Zero lCali;

	// 加上10是因为要除20,能够四舍五入
	sCaliAdcSum += 10;
	lCali.AdcNow = sCaliAdcSum / 20;
	sCaliAdcSum = 0x00;

//	rt_kprintf("adccalcu = %d\n", lCali.AdcNow);

	lCali.AdcZero = lpGas->pConst->ZeroAdc;
	lCali.ZeroRange = lpGas->pConst->ZeroAdcRange;

//	if (lpGas->pConst->Direct == GAS_DIRECT_POSITIVE)
//	{
////		GasCaliZeroGet(&lCali, &(lpGas->pSave->Ref1));
//		(*(FUNC_GAS_CALI_ZERO_GET)
//				lpGas->pConst->vFuncGasCaliZeroGet)
//						(&lCali, &(lpGas->pSave->Ref1));
//	}
//	else
//	{
////		GasCaliZeroGet(&lCali, &(lpGas->pSave->Ref3));
//		(*(FUNC_GAS_CALI_ZERO_GET)
//				lpGas->pConst->vFuncGasCaliZeroGet)
//						(&lCali, &(lpGas->pSave->Ref3));
//	}

	(*(FUNC_GAS_CALI_ZERO_GET)
			lpGas->pConst->vFunc.GasCaliZeroGet)
					(&lCali, lpGas);

	if (lCali.CaliSuc == E_FALSE)
	{
		S_ResultError* lpResultError;

		lpResultError = StateResultErrorPointGet();

		lpResultError->AD = E_FALSE;

//		lpResultError->AD = E_TRUE;

//		lpResultError->Func.ValueGet = MenuCaliValueGetZero;
		lpResultError->Value.Num = lCali.AdcNow;
		lpResultError->Value.Point = POINT_HHHHH;
		lpResultError->ErrNum = lCali.ErrNum;

		StateResultErrorInit();
		StateCountdownToResult();
	}
	else
	{
		S_ResultSuccess* lpResultSuccess;

		lpResultSuccess = StateResultSuccessPointGet();

		lpResultSuccess->AD = E_FALSE;

//		lpResultSuccess->AD = E_TRUE;

//		lpResultSuccess->Func.ValueGet = MenuCaliValueGetZero;
		lpResultSuccess->Value.Num = lCali.AdcNow;
		lpResultSuccess->Value.Point = POINT_HHHHH;

		StateResultSuccessInit();
		StateCountdownToResult();
	}
}


/**
 * @brief   输入函数数值保存
 */
void MenuCaliSaveZero(E_TurnState lTurn)
{
	if (lTurn == TURN_ON)
	{
		S_Countdown* lpCountdown;

		lpCountdown = StateCountdownPointGet();

		E_Language lLang;

		lLang = Lcd__LangGet();

		lpCountdown->AD = E_FALSE;
//		lpCountdown->Label = "Cali Zero";
		lpCountdown->Label = *(sCaliZeroTxt[lLang]);

//		lpCountdown->AD = E_TRUE;

		lpCountdown->Time = 20;
		lpCountdown->Func.ValueGet =
								MenuCaliCountdownValueGetZero;
		lpCountdown->Func.ValueSet =
								MenuCaliCountdownValueSetZero;
		lpCountdown->Func.ValueCalcu =
								MenuCaliCountdownValueCalcuZero;

//		StateCountdownInit();
//		StateInputToCountdown();
	}
	else
	{
//		StateInputToMenu();
	}
}


/**
 * @brief   输入函数数值保存
 */
void MenuCaliConfirmZero(E_TurnState lTurn)
{
	if (lTurn == TURN_ON)
	{
		StateCountdownInit();
		StateInputToCountdown();
	}
	else
	{
		StateInputToMenu();
	}
}


/**
 * @brief   进入子菜单
 */
void MenuCaliChildZero(void)
{
	S_InputBinary lInput;

	lInput.Func.BinaryGet = MenuCaliBinaryGet;
	lInput.Func.Save = MenuCaliSaveZero;
	lInput.Func.Confirm = MenuCaliConfirmZero;
	lInput.State = BINARY_YESNO;
//	lInput.Call = E_TRUE;
	StateInputBinaryInit(&lInput);
	StateMenuToInput();
}

/****************************** 标气 **********************************/
/**
 * @brief   输入函数数值获得
 */
void MenuCaliInputLimitGetCoeff(void)
{
	S_Gas* lpGas;
	StateGasPointGet(&lpGas);

	S_Value_Input_Gas lValueInput;


	// 获取一级报警的上下限
	(*(FUNC_GAS_VALUE_LIMIT_GET)
						lpGas->pConst->vFunc.GasValueLimitGet)
										(lpGas, &lValueInput);
	lValueInput.Point = lpGas->pConst->Point;
	ValueInputSetU16(&lValueInput);
}


// 标气专用的一个点
static S_Gas_Point sCaliCoeff;


/**
 * @brief   获得倒计时时间中的气体数值
 */
void MenuCaliInputValueGetCoeff(S_Value_U16* lpValue)
{
	S_Gas* lpGas;
	StateGasPointGet(&lpGas);

	// 开启这个有可能使得设定标气数值的时候，
	// 在YES的时候，显示数值不是想要的
//	StateDetectValueGet(lpGas);

//	lpValue->Num = lpGas->pSave->Alarm.Lower;
//	lpValue->Num = lpGas->pTemp->Point.Value;
//	lpValue->Point = lpGas->pConst->Point;

	lpValue->Num = sCaliCoeff.Value;
	lpValue->Point = lpGas->pConst->Point;

//	lpValue->Num = lpGas->pTemp->Point.Adc;
//	lpValue->Point = POINT_HHHHH;
}

/**
 * @brief   输入气体系数数值确认
 */
void MenuCaliInputSetCoeff(void)
{
//	S_Gas* lpGas;
//	StateGasPointGet(&lpGas);

	S_Value_Array_U16 lArray;

	ValueInputGetU16(&lArray);
	sCaliCoeff.Value = lArray.Value.Num;
//	lpGas->pTemp->Point.Value = lArray.Value.Num;
}

//static uint32_t sCaliCoeffSum;

/**
 * @brief   获得倒计时时间中的ADC数值
 */
void MenuCaliCountdownValueGetCoeff(S_Value_U16* lpValue)
{
	MenuCaliCountdownValueGetZero(lpValue);
}

/**
 * @brief   倒计时时间中的AD数值存储相加
 */
void MenuCaliCountdownValueSetCoeff(S_Value_U16* lpValue)
{
	MenuCaliCountdownValueSetZero(lpValue);
}


/**
 * @brief   倒计时结束的气体数值计算求平均
 */
void MenuCaliCountdownValueCalcuCoeff(void)
{
	S_Gas* lpGas;
	StateGasPointGet(&lpGas);

//	S_Gas_Cali_Zero lCali;
//
//	lCali.AdcNow = sCaliAdcSum / 20;
//
//	rt_kprintf("adccalcu = %d\n", lCali.AdcNow);
//
//	lCali.AdcZero = lpGas->pConst->AdcZero;
//	lCali.ZeroRange = lpGas->pConst->AdcRange;
//
//	if (lpGas->pConst->Direct == GAS_DIRECT_POSITIVE)
//	{
//		GasCaliZeroGet(&lCali, &(lpGas->pSave->Ref1));
//	}
//	else
//	{
//		GasCaliZeroGet(&lCali, &(lpGas->pSave->Ref3));
//	}


	S_Gas_Cali_Coeff lCali;

	// 加上10是因为要除20,能够四舍五入
	sCaliAdcSum += 10;
	lCali.AdcNow = sCaliAdcSum / 20;
	sCaliAdcSum = 0x00;

//	rt_kprintf("adccalcu = %d\n", lCali.AdcNow);

//	lCali.AdcZero = lpGas->pConst->ZeroAdc;
	lCali.Threshold = lpGas->pConst->CaliCoeffThrs;
	lCali.Value = sCaliCoeff.Value;

//	if (lpGas->pConst->Direct == GAS_DIRECT_POSITIVE)
//	{
////		GasCaliCoeffGetPositive(&lCali, &(lpGas->pSave->Ref3));
//		(*(FUNC_GAS_CALI_COEFF_GET)
//				lpGas->pConst->vFuncGasCaliCoeffGet)
//						(&lCali, &(lpGas->pSave->Ref3));
//	}
//	else if (lpGas->pConst->Direct == GAS_DIRECT_NEGATIVE)
//	{
////		GasCaliCoeffGetNegative(&lCali, &(lpGas->pSave->Ref1));
//		(*(FUNC_GAS_CALI_COEFF_GET)
//				lpGas->pConst->vFuncGasCaliCoeffGet)
//						(&lCali, &(lpGas->pSave->Ref1));
//	}
//	else
//	{
////		GasCaliCoeffGetBoth(&lCali, &(lpGas->pSave->Ref1));
//		(*(FUNC_GAS_CALI_COEFF_GET)
//				lpGas->pConst->vFuncGasCaliCoeffGet)
//						(&lCali, &(lpGas->pSave->Ref1));
//	}

	(*(FUNC_GAS_CALI_COEFF_GET)
			lpGas->pConst->vFunc.GasCaliCoeffGet)
					(&lCali, lpGas);

	if (lCali.CaliSuc == E_FALSE)
	{
		S_ResultError* lpResultError;

		lpResultError = StateResultErrorPointGet();

		lpResultError->AD = E_FALSE;

//		lpResultError->AD = E_TRUE;

//		lpResultError->Func.ValueGet = MenuCaliValueGetZero;
		lpResultError->Value.Num = lCali.AdcNow;
		lpResultError->Value.Point = POINT_HHHHH;
		lpResultError->ErrNum = lCali.ErrNum;

		StateResultErrorInit();
		StateCountdownToResult();
	}
	else
	{
		S_ResultSuccess* lpResultSuccess;

		lpResultSuccess = StateResultSuccessPointGet();

		lpResultSuccess->AD = E_FALSE;

//		lpResultSuccess->AD = E_TRUE;

//		lpResultSuccess->Func.ValueGet = MenuCaliValueGetZero;
		lpResultSuccess->Value.Num = lCali.AdcNow;
		lpResultSuccess->Value.Point = POINT_HHHHH;

		StateResultSuccessInit();
		StateCountdownToResult();
	}
}


/**
 * @brief   输入函数数值保存
 */
void MenuCaliSaveCoeff(void)
{
//	S_Gas* lpGas;
//	StateGasPointGet(&lpGas);

//	lpGas->pSave->Alarm.Upper = lpGas->pTemp->AlarmSave.Upper;
//	lpGas->pSave->Save_Bits.Upper = FLASH_SAVE_TRUE;

//	sCaliCoeff.Value =

	// 这边不能保存，必须要是标气成功才应该保存

	S_Countdown* lpCountdown;

	lpCountdown = StateCountdownPointGet();

	E_Language lLang;

	lLang = Lcd__LangGet();

	lpCountdown->AD = E_FALSE;
	lpCountdown->Label = *(sCaliCoeffTxt[lLang]);

//		lpCountdown->AD = E_TRUE;

	lpCountdown->Time = 20;
	lpCountdown->Func.ValueGet =
							MenuCaliCountdownValueGetCoeff;
	lpCountdown->Func.ValueSet =
							MenuCaliCountdownValueSetCoeff;
	lpCountdown->Func.ValueCalcu =
							MenuCaliCountdownValueCalcuCoeff;

}


/**
 * @brief   输入函数数值保存
 */
void MenuCaliConfirmCoeff(E_TrueState lTrue)
{
	if (lTrue == TURN_ON)
	{
		StateCountdownInit();
		StateInputToCountdown();
	}
	else
	{
		StateInputToMenu();
	}
}


/**
 * @brief   进入子菜单
 */
void MenuCaliChildCoeff(void)
{
//	S_InputBinary lInput;
//
//	lInput.Func.BinaryGet = MenuCaliBinaryGet;
//	lInput.Func.Save = MenuCaliConfirmCoeff;
//	lInput.State = BINARY_YESNO;
////	lInput.Call = E_TRUE;
//	StateInputBinaryInit(&lInput);

	S_Gas* lpGas;
	StateGasPointGet(&lpGas);

	// 先读取当前的数值，不然你闪烁后的数值就不好处理了。
	sCaliCoeff.Value = lpGas->pTemp->Point.Value;

	S_InputValue lValue;
	lValue.Func.LimitGet = MenuCaliInputLimitGetCoeff;
	lValue.Func.ValueGet = MenuCaliInputValueGetCoeff;
	lValue.Func.Set = MenuCaliInputSetCoeff;
	lValue.Func.Save = MenuCaliSaveCoeff;
	lValue.Func.Confirm = MenuCaliConfirmCoeff;
	StateInputValueInit(&lValue);

//	lValue.Func.Get
	StateMenuToInput();
}


/**
 * @brief   进入子菜单
 */
void MenuCaliChild(void)
{
//	MenuKeyChild();
//	MenuDisp();

	menu_t lItem;

	MenuItemGet(&lItem);

	if (lItem == 0)
	{
		MenuCaliChildZero();
	}
	else if (lItem == 1)
	{
		MenuCaliChildCoeff();
	}
}


/**
 * @brief   进入父菜单
 */
void MenuCaliParent(void)
{
	MenuKeyParent();
	MenuDisp();
}


/**
 * @brief   下一条菜单项
 */
void MenuCaliNext(void)
{
	MenuKeyNext();

}


/**
 * @brief   上一条菜单项
 */
void MenuCaliPrev(void)
{
	MenuKeyPrev();
}
