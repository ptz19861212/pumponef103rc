/**
 * @file    state_result.c
 * @brief   结果
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2014-01-16 07:28:30 星期四 
 * @history (1).2014-01-16 07:28:30 星期四 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#include "state_result_in.h"

// 退出字符串 英文
const char *sResultExitSucEn[] =
{
		"",
		"Exit",
};

// 退出字符串 中文
const char *sResultExitSucCn[] =
{
		"",
		"退出",
};

// 退出字符串 指针数组
const char **sResultExitSuccess[] =
{
		sResultExitSucEn,
		sResultExitSucCn,
};


// 成功字符串 英文
const char *sResultSucEn[] =
{
		"Success",
};

// 成功字符串 中文
const char *sResultSucCn[] =
{
		"成功",
};

// 成功字符串 指针数组
const char **sResultSucTxt[] =
{
		sResultSucEn,
		sResultSucCn,
};



// 退出字符串 英文
const char *sResultExitErrEn[] =
{
		"",
		"",
		"Exit",
};

// 退出字符串 中文
const char *sResultExitErrCn[] =
{
		"",
		"",
//		"exit",
		"退出",
};

// 退出字符串 指针数组
const char **sResultExitError[] =
{
		sResultExitErrEn,
		sResultExitErrCn,
};

// 出错字符串 英文
const char *sResultErrEn[] =
{
		"Error",
};

// 出错字符串 中文
const char *sResultErrCn[] =
{
		"出错",
};

// 出错字符串 指针数组
const char **sResultErrTxt[] =
{
		sResultErrEn,
		sResultErrCn,
};


// 出错
S_StateResultError sResultError;
// 成功
S_StateResultSuccess sResultSuccess;

// 用于按键表
S_Result_Tab sResultNow;


/**
 * @brief   获得出错外部输入结构体指针
 *
 * @return
 */
S_ResultError* StateResultErrorPointGet(void)
{
	return &(sResultError.Out);
}


/**
 * @brief   错误号的正常显示
 */
static void StateResultErrNumDisp(void)
{
	S_Lcd__Item_Mid lTrig;

	char lData[GAS_VALUE_ARRAY_SIZE];
	S_Value_Array_U16 lArray;

	lArray.Char = lData;
	lArray.Value.Num = sResultError.Out.ErrNum;
	lArray.Value.Point = POINT_HHHHH;

	DecToStrU16(&lArray);
	lTrig.Item.Pos = CONFIG_RESULT_ERROR_POS + 2;
	lTrig.Item.Char = lData;
	lTrig.Len = CONFIG_RESULT_LEN;
	Lcd__FrameItemMidDispHalf(&lTrig);
}


/**
 * @brief   ADC数值的显示
 */
static void StateResultErrorValueDisp(S_Value_U16* lpValue)
{
	S_Lcd__Item_Mid lTrig;

	char lData[GAS_VALUE_ARRAY_SIZE];
	S_Value_Array_U16 lArray;

	lArray.Char = lData;

	// 获取数值
//	(*sResult.Out.Func.ValueGet)(&(lArray.Value));
	lArray.Value.Num = lpValue->Num;
	lArray.Value.Point = lpValue->Point;

	DecToStrU16(&lArray);
	lTrig.Item.Pos = CONFIG_RESULT_ERROR_POS;
	lTrig.Item.Char = lData;
	lTrig.Len = CONFIG_RESULT_LEN;
	Lcd__FrameItemMidDispHalf(&lTrig);
}

// 秒
//static my_second_t sResultSecond;
// 秒内的计数，这个是为了整秒，不然第一秒长短不一
//static uint8_t sResultCount;

/**
 * @brief   菜单项倒计时的初始显示，包括数值本身的显示
 *
 * @param   lpResult
 */
void StateResultErrorInit(void)
{
	// 初始的
	sResultError.Line.Index = 0;
	// 数值输入一共三行
	sResultError.Line.Num = 3;

	// 按键列表索引
	sResultNow.Index = STATE_RESULT_ERROR_INDEX;

	E_Language lLang;
	// 获得当前显示的语言
	lLang = Lcd__LangGet();

	DisClr();

	// 画框架
	S_Lcd_Area_RectangleShade lRec;
	lRec.Ex.X = CONFIG_RESULT_ERROR_FRAME_EX_X;
	lRec.Ex.Y = CONFIG_RESULT_ERROR_FRAME_EX_Y;
	lRec.PS.X = CONFIG_RESULT_ERROR_FRAME_X_START;
	lRec.PS.Y = CONFIG_RESULT_ERROR_FRAME_Y_START;
	lRec.PE.X = CONFIG_RESULT_ERROR_FRAME_X_END;
	lRec.PE.Y = CONFIG_RESULT_ERROR_FRAME_Y_END;
	DisRecFramSet(&lRec);

	uint8_t lI;
	S_Lcd__Item_Mid lTrig;

	// 显示全部的标签
	for (lI = 0; lI < STR_NUM(sResultExitErrEn); lI++)
	{
		lTrig.Item.Pos = CONFIG_RESULT_ERROR_POS + 2 * lI;
		lTrig.Item.Char = *(sResultExitError[lLang] + lI);
		lTrig.Len = CONFIG_RESULT_LEN;
		Lcd__FrameItemMidDispHalf(&lTrig);
	}

	// 反显 cancel
	Lcd__FrameItemRevHalf(CONFIG_RESULT_ERROR_POS + 2 * 2);

	// 如果不显示AD数值
	if (sResultError.Out.AD == E_FALSE)
	{
		lTrig.Item.Pos = CONFIG_RESULT_ERROR_POS;
//		lTrig.Item.Char = sResultError.Out.Label;
		lTrig.Item.Char = *(sResultErrTxt[lLang]);
		lTrig.Len = CONFIG_RESULT_LEN;
		Lcd__FrameItemMidDispHalf(&lTrig);
	}
	// 显示数值
	else
	{
//		char lData[GAS_VALUE_ARRAY_SIZE];
//		S_Value_Array_U16 lArray;
//
//		lArray.Char = lData;
//
//		// 获取数值
//		(*sResult.Out.Func.ValueGet)(&(lArray.Value));
//
//		DecToStrU16(&lArray);
//		lTrig.Item.Pos = CONFIG_RESULT_POS;
//		lTrig.Item.Char = lData;
//		lTrig.Len = CONFIG_RESULT_LEN;
//		Lcd__FrameItemMidDispHalf(&lTrig);

//		S_Value_U16 lValue;
//		(*sResultError.Out.Func.ValueGet)(&lValue);
//		StateResultErrorValueDisp(&lValue);
		StateResultErrorValueDisp(&(sResultError.Out.Value));
	}

	// 显示秒数
	StateResultErrNumDisp();

//	S_Device* lpDev;
//	StateDevicePointGet(&lpDev);

//	sResultSecond = lpDev->pTemp->Time.Sec;
//	sResultCount = lpDev->pTemp->Time.Count;
}


///**
// * @brief   倒计时处理
// */
//void StateResultSecond(void)
//{
//	S_Device* lpDev;
//	StateDevicePointGet(&lpDev);
//
//	// 为了整秒
//	if (lpDev->pTemp->Time.Count != sResultCount)
//	{
//		return;
//	}
//
//	if (lpDev->pTemp->Time.Sec > sResultSecond)
//	{
//		sResult.Out.Time--;
//	}
//	else
//	{
//		return;
//	}
//	sResultSecond = lpDev->pTemp->Time.Sec;
//
//	S_Value_U16 lValue;
//	sResult.Out.Func.ValueGet(&lValue);
//
//	if (sResult.Out.AD == E_TRUE)
//	{
//		StateResultValueDisp(&lValue);
//	}
//
//	sResult.Out.Func.ValueSet(&lValue);
//
//	if (sResult.Out.Time == 0)
//	{
//		sResult.Out.Func.ValueCalcu();
//	}
//	else
//	{
//		// 显示秒数
//		StateResultSecDisp();
//	}
//}


/**
 * @brief   菜单项最终处理确认
 */
static void StateResultErrorConfirm(void)
{
//	StateResultToMenu();
	StateResultToDetect();
}


/***************************** 成功 **********************************/
/**
 * @brief   获得成功外部输入结构体指针
 *
 * @return
 */
S_ResultSuccess* StateResultSuccessPointGet(void)
{
	return &(sResultSuccess.Out);
}


/**
 * @brief   ADC数值的显示
 */
static void StateResultSuccessValueDisp(S_Value_U16* lpValue)
{
	S_Lcd__Item_Mid lTrig;

	char lData[GAS_VALUE_ARRAY_SIZE];
	S_Value_Array_U16 lArray;

	lArray.Char = lData;

	// 获取数值
	lArray.Value.Num = lpValue->Num;
	lArray.Value.Point = lpValue->Point;

	DecToStrU16(&lArray);
	lTrig.Item.Pos = CONFIG_RESULT_SUCCESS_POS;
	lTrig.Item.Char = lData;
	lTrig.Len = CONFIG_RESULT_LEN;
	Lcd__FrameItemMidDisp(&lTrig);
}


/**
 * @brief   菜单项倒计时的初始显示，包括数值本身的显示
 *
 * @param   lpResult
 */
void StateResultSuccessInit(void)
{
	// 初始的
	sResultError.Line.Index = 0;
	// 数值输入一共三行
	sResultError.Line.Num = 2;

	// 按键列表索引
	sResultNow.Index = STATE_RESULT_SUCCESS_INDEX;

	E_Language lLang;
	// 获得当前显示的语言
	lLang = Lcd__LangGet();

	DisClr();

	// 画框架
	S_Lcd_Area_RectangleShade lRec;
	lRec.Ex.X = CONFIG_RESULT_SUCCESS_FRAME_EX_X;
	lRec.Ex.Y = CONFIG_RESULT_SUCCESS_FRAME_EX_Y;
	lRec.PS.X = CONFIG_RESULT_SUCCESS_FRAME_X_START;
	lRec.PS.Y = CONFIG_RESULT_SUCCESS_FRAME_Y_START;
	lRec.PE.X = CONFIG_RESULT_SUCCESS_FRAME_X_END;
	lRec.PE.Y = CONFIG_RESULT_SUCCESS_FRAME_Y_END;
	DisRecFramSet(&lRec);

	uint8_t lI;
	S_Lcd__Item_Mid lTrig;

	// 显示全部的标签
	for (lI = 0; lI < STR_NUM(sResultExitSucEn); lI++)
	{
		lTrig.Item.Pos = CONFIG_RESULT_SUCCESS_POS + lI;
		lTrig.Item.Char = *(sResultExitSuccess[lLang] + lI);
		lTrig.Len = CONFIG_RESULT_LEN;
		Lcd__FrameItemMidDisp(&lTrig);
	}

	// 反显 exit
	Lcd__FrameItemRev(CONFIG_RESULT_SUCCESS_POS + 1);

	// 如果不显示AD数值
	if (sResultSuccess.Out.AD == E_FALSE)
	{
		lTrig.Item.Pos = CONFIG_RESULT_SUCCESS_POS;
		lTrig.Item.Char = *(sResultSucTxt[lLang]);
		lTrig.Len = CONFIG_RESULT_LEN;
		Lcd__FrameItemMidDisp(&lTrig);
	}
	// 显示数值
	else
	{
//		S_Value_U16 lValue;
//		(*sResultError.Out.Func.ValueGet)(&lValue);
//		StateResultSuccessValueDisp(&lValue);
		StateResultSuccessValueDisp(&(sResultSuccess.Out.Value));
	}
}


/**
 * @brief   菜单项最终处理确认
 */
static void StateResultSuccessConfirm(void)
{
//	StateResultToMenu();
	SaveWrite();
	StateResultToDetect();
}


// 菜单对应的按键函数
static const S_Result_Tab sStateResultTab[] =
{
//		STATE_RESULT_KEY_TAB(,),
		STATE_RESULT_KEY_TAB(ERROR, Error),
		STATE_RESULT_KEY_TAB(SUCCESS, Success),

};


/**
 * @brief   按键 调用函数
 */
void StateResultKey(uint8_t lKey)
{
	switch (lKey)
	{
		case KEY_ENTER:
			sStateResultTab[sResultNow.Index].Confirm();
			break;

		default:
			break;
	}
}
