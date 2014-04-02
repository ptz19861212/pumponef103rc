/**
 * @file    state_countdown.c
 * @brief   倒计时
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2014-01-14 16:43:00 星期二 
 * @history (1).2014-01-14 16:43:00 星期二 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#include "state_countdown_in.h"


// 取消字符串 英文
const char *sCountdownCancelEn[] =
{
		"",
		"",
		"Cancel",
};

// 取消字符串 中文
const char *sCountdownCancelCn[] =
{
		"",
		"",
		"取消",
	//		"取消",
};

// 退出字符串 指针数组
const char **sCountdownCancel[] =
{
		sCountdownCancelEn,
		sCountdownCancelCn,
};


S_StateCountdown sCountdown;

// 用于按键表
S_Countdown_Tab sCountdownNow;


/**
 * @brief   获得倒计时外部输入结构体指针
 *
 * @return
 */
S_Countdown* StateCountdownPointGet(void)
{
	return &(sCountdown.Out);
}


/**
 * @brief   倒计时秒数值的那一行的正常显示
 */
static void StateCountdownSecDisp(void)
{
	S_Lcd__Item_Mid lTrig;

	char lData[GAS_VALUE_ARRAY_SIZE];
	S_Value_Array_U16 lArray;

	lArray.Char = lData;
	lArray.Value.Num = sCountdown.Out.Time;
	lArray.Value.Point = POINT_HHHHH;

	DecToStrU16(&lArray);
	lTrig.Item.Pos = CONFIG_COUNTDOWN_POS + 2;
	lTrig.Item.Char = lData;
	lTrig.Len = CONFIG_COUNTDOWN_LEN;
	Lcd__FrameItemMidDispHalf(&lTrig);
}


/**
 * @brief   倒计时ADC或气体数值的那一行的正常显示
 */
static void StateCountdownValueDisp(S_Value_U16* lpValue)
{
	S_Lcd__Item_Mid lTrig;

	char lData[GAS_VALUE_ARRAY_SIZE];
	S_Value_Array_U16 lArray;

	lArray.Char = lData;

	// 获取数值
//	(*sCountdown.Out.Func.ValueGet)(&(lArray.Value));
	lArray.Value.Num = lpValue->Num;
	lArray.Value.Point = lpValue->Point;

	DecToStrU16(&lArray);
	lTrig.Item.Pos = CONFIG_COUNTDOWN_POS;
	lTrig.Item.Char = lData;
	lTrig.Len = CONFIG_COUNTDOWN_LEN;
	Lcd__FrameItemMidDispHalf(&lTrig);
}

// 秒
static my_second_t sCountdownSecond;
// 秒内的计数，这个是为了整秒，不然第一秒长短不一
static uint8_t sCountdownCount;

/**
 * @brief   菜单项倒计时的初始显示，包括数值本身的显示
 *
 * @param   lpCountdown
 */
void StateCountdownInit(void)
{
	// 初始的
	sCountdown.Line.Index = 0;
	// 非锁定状态
//	sValue.Line.Lock = LOCK_OFF;
	// 数值输入一共三行
	sCountdown.Line.Num = 3;

	// 按键列表索引
	sCountdownNow.Index = STATE_COUNTDOWN_ZERO_INDEX;

	E_Language lLang;
	// 获得当前显示的语言
	lLang = Lcd__LangGet();

	DisClr();

	// 画框架
	S_Lcd_Area_RectangleShade lRec;
	lRec.Ex.X = CONFIG_COUNTDOWN_FRAME_EX_X;
	lRec.Ex.Y = CONFIG_COUNTDOWN_FRAME_EX_Y;
	lRec.PS.X = CONFIG_COUNTDOWN_FRAME_X_START;
	lRec.PS.Y = CONFIG_COUNTDOWN_FRAME_Y_START;
	lRec.PE.X = CONFIG_COUNTDOWN_FRAME_X_END;
	lRec.PE.Y = CONFIG_COUNTDOWN_FRAME_Y_END;
	DisRecFramSet(&lRec);

	uint8_t lI;
	S_Lcd__Item_Mid lTrig;

	// 显示全部的标签
	for (lI = 0; lI < STR_NUM(sCountdownCancelEn); lI++)
	{
		lTrig.Item.Pos = CONFIG_COUNTDOWN_POS + 2 * lI;
		lTrig.Item.Char = *(sCountdownCancel[lLang] + lI);
		lTrig.Len = CONFIG_COUNTDOWN_LEN;
		Lcd__FrameItemMidDispHalf(&lTrig);
	}

	// 反显 cancel
	Lcd__FrameItemRevHalf(CONFIG_COUNTDOWN_POS + 2 * 2);

	// 如果不显示AD数值
	if (sCountdown.Out.AD == E_FALSE)
	{
		lTrig.Item.Pos = CONFIG_COUNTDOWN_POS;
		lTrig.Item.Char = sCountdown.Out.Label;
		lTrig.Len = CONFIG_COUNTDOWN_LEN;
		Lcd__FrameItemMidDispHalf(&lTrig);
	}
	// 显示AD数值
	else
	{
//		char lData[GAS_VALUE_ARRAY_SIZE];
//		S_Value_Array_U16 lArray;
//
//		lArray.Char = lData;
//
//		// 获取数值
//		(*sCountdown.Out.Func.ValueGet)(&(lArray.Value));
//
//		DecToStrU16(&lArray);
//		lTrig.Item.Pos = CONFIG_COUNTDOWN_POS;
//		lTrig.Item.Char = lData;
//		lTrig.Len = CONFIG_COUNTDOWN_LEN;
//		Lcd__FrameItemMidDispHalf(&lTrig);

		S_Value_U16 lValue;
		(*sCountdown.Out.Func.ValueGet)(&lValue);
		StateCountdownValueDisp(&lValue);
	}

	// 显示秒数
	StateCountdownSecDisp();

	S_Device* lpDev;
	StateDevicePointGet(&lpDev);

	sCountdownSecond = lpDev->pTemp->Time.Sec;
	sCountdownCount = lpDev->pTemp->Time.Count;
}


/**
 * @brief   倒计时处理
 */
void StateCountdownSecond(void)
{
	S_Device* lpDev;
	StateDevicePointGet(&lpDev);

	// 为了整秒
	if (lpDev->pTemp->Time.Count != sCountdownCount)
	{
		return;
	}

	if (lpDev->pTemp->Time.Sec > sCountdownSecond)
	{
		if (sCountdown.Out.Time > 0)
		{
			sCountdown.Out.Time--;
		}
		PowerSaveBglFresh();
	}
	else
	{
		return;
	}
	sCountdownSecond = lpDev->pTemp->Time.Sec;

	S_Value_U16 lValue;
	sCountdown.Out.Func.ValueGet(&lValue);

	if (sCountdown.Out.AD == E_TRUE)
	{
		StateCountdownValueDisp(&lValue);
	}

	sCountdown.Out.Func.ValueSet(&lValue);

	if (sCountdown.Out.Time == 0)
	{
		sCountdown.Out.Func.ValueCalcu();
	}
	else
	{
		// 显示秒数
		StateCountdownSecDisp();
	}
}


/**
 * @brief   菜单项最终处理确认
 */
static void StateCountdownConfirm(void)
{
	StateCountdownToMenu();
}


// 菜单对应的按键函数
static const S_Countdown_Tab sStateCountdownTab[] =
{
//		STATE_COUNTDOWN_KEY_TAB(,),
		STATE_COUNTDOWN_INDEX,
		StateCountdownConfirm,

};


/**
 * @brief   按键 调用函数
 */
void StateCountdownKey(uint8_t lKey)
{
	switch (lKey)
	{
		case KEY_ENTER:
			sStateCountdownTab[sCountdownNow.Index].Confirm();
			break;

		default:
			break;
	}
}
