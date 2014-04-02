/**
 * @file    state_shutdown.c
 * @brief   关机
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

#include "state_shutdown_in.h"


// 关机字符串 英文
const char *sShutdownEn[] =
{
		"Shut Down",
		"",
};

// 关机字符串 中文
const char *sShutdownCn[] =
{
		"关机",
		"",
};

// 关机字符串 指针数组
const char **sShutdownTxt[] =
{
		sShutdownEn,
		sShutdownCn,
};


// 欠电字符串 英文
const char *sBatLowEn[] =
{
		"Bat Power Low",
		"",
};

// 欠电字符串 中文
const char *sBatLowCn[] =
{
		"电池电压不足",
		"",
};

// 欠电字符串 指针数组
const char **sBatLowTxt[] =
{
		sBatLowEn,
		sBatLowCn,
};


S_StateShutdown sShutdown;

// 用于按键表
S_Shutdown_Tab sShutdownNow;


/**
 * @brief   获得关机外部输入结构体指针
 *
 * @return
 */
S_Shutdown* StateShutdownPointGet(void)
{
	return &(sShutdown.Out);
}


/**
 * @brief   关机秒数值的那一行的正常显示
 */
static void StateShutdownSecDisp(void)
{
	S_Lcd__Item_Mid lTrig;

	char lData[GAS_VALUE_ARRAY_SIZE];
	S_Value_Array_U16 lArray;

	lArray.Char = lData;
	lArray.Value.Num = sShutdown.Out.Time;
	lArray.Value.Point = POINT_HHHHH;

	DecToStrU16(&lArray);
	lTrig.Item.Pos = CONFIG_SHUTDOWN_POS + 1;
	lTrig.Item.Char = lData;
	lTrig.Len = CONFIG_SHUTDOWN_LEN;
	Lcd__FrameItemMidDisp(&lTrig);
}


/**
 * @brief   关机ADC或气体数值的那一行的正常显示
 */
//static void StateShutdownValueDisp(S_Value_U16* lpValue)
//{
//	S_Lcd__Item_Mid lTrig;
//
//	char lData[GAS_VALUE_ARRAY_SIZE];
//	S_Value_Array_U16 lArray;
//
//	lArray.Char = lData;
//
//	// 获取数值
////	(*sShutdown.Out.Func.ValueGet)(&(lArray.Value));
//	lArray.Value.Num = lpValue->Num;
//	lArray.Value.Point = lpValue->Point;
//
//	DecToStrU16(&lArray);
//	lTrig.Item.Pos = CONFIG_SHUTDOWN_POS;
//	lTrig.Item.Char = lData;
//	lTrig.Len = CONFIG_SHUTDOWN_LEN;
//	Lcd__FrameItemMidDispHalf(&lTrig);
//}

// 秒
static my_second_t sShutdownSecond;
// 秒内的计数，这个是为了整秒，不然第一秒长短不一
static uint8_t sShutdownCount;

/**
 * @brief   菜单项关机的初始显示，包括数值本身的显示
 *
 * @param   lpShutdown
 */
void StateShutdownInit(void)
{
	// 初始的
	sShutdown.Line.Index = 0;
	//
	sShutdown.Line.Num = 2;

	// 按键列表索引
//	sShutdownNow.Index = STATE_SHUTDOWN_INDEX;

	E_Language lLang;
	// 获得当前显示的语言
	lLang = Lcd__LangGet();

	DisClr();

	// 画框架
	S_Lcd_Area_RectangleShade lRec;
	lRec.Ex.X = CONFIG_SHUTDOWN_FRAME_EX_X;
	lRec.Ex.Y = CONFIG_SHUTDOWN_FRAME_EX_Y;
	lRec.PS.X = CONFIG_SHUTDOWN_FRAME_X_START;
	lRec.PS.Y = CONFIG_SHUTDOWN_FRAME_Y_START;
	lRec.PE.X = CONFIG_SHUTDOWN_FRAME_X_END;
	lRec.PE.Y = CONFIG_SHUTDOWN_FRAME_Y_END;
	DisRecFramSet(&lRec);

	uint8_t lI;
	S_Lcd__Item_Mid lTrig;

	// 显示全部的标签
	for (lI = 0; lI < STR_NUM(sShutdownEn); lI++)
	{
		lTrig.Item.Pos = CONFIG_SHUTDOWN_POS + lI;

		// 电压不足
		if (sShutdown.Out.BatLow == E_TRUE)
		{
			lTrig.Item.Char = *(sBatLowTxt[lLang] + lI);
		}
		else
		{
			lTrig.Item.Char = *(sShutdownTxt[lLang] + lI);
		}

		lTrig.Len = CONFIG_SHUTDOWN_LEN;
		Lcd__FrameItemMidDisp(&lTrig);
	}

	// 显示秒数
	StateShutdownSecDisp();

	S_Device* lpDev;
	StateDevicePointGet(&lpDev);

	sShutdownSecond = lpDev->pTemp->Time.Sec;
	sShutdownCount = lpDev->pTemp->Time.Count;
}


/**
 * @brief   关机处理
 */
void StateShutdownSecond(void)
{
	S_Device* lpDev;
	StateDevicePointGet(&lpDev);

	// 为了整秒
	if (lpDev->pTemp->Time.Count != sShutdownCount)
	{
		return;
	}

	if (lpDev->pTemp->Time.Sec > sShutdownSecond)
	{
		if (sShutdown.Out.Time > 0)
		{
			sShutdown.Out.Time--;
		}
		PowerSaveBglFresh();
	}
	else
	{
		return;
	}
	sShutdownSecond = lpDev->pTemp->Time.Sec;

//	S_Value_U16 lValue;
//	sShutdown.Out.Func.ValueGet(&lValue);
//
//	if (sShutdown.Out.AD == E_TRUE)
//	{
//		StateShutdownValueDisp(&lValue);
//	}
//
//	sShutdown.Out.Func.ValueSet(&lValue);

	S_Buzzer lBz;
	lBz.Src = BUZZER_SECOND;
	lBz.Time = BUZZER_SECOND_TIME;
	BuzzerOn(&lBz);

	if (sShutdown.Out.Time == 0)
	{
		sShutdown.Out.Func.Shutdown();
		StateShutdownToPowerOff();
	}
	else
	{
		// 显示秒数
		StateShutdownSecDisp();
	}
}


///**
// * @brief   菜单项最终处理确认
// */
//static void StateShutdownConfirm(void)
//{
//	StateShutdownToMenu();
//}


// 菜单对应的按键函数
//static const S_Shutdown_Tab sStateShutdownTab[] =
//{
////		STATE_SHUTDOWN_KEY_TAB(,),
//		STATE_SHUTDOWN_INDEX,
//		StateShutdownConfirm,
//
//};


/**
 * @brief   按键 调用函数
 */
void StateShutdownKey(uint8_t lKey)
{
	if (sShutdown.Out.BatLow != E_TRUE)
	{
		if (lKey != KEY_ENTER)
		{
			StateShutdownToDetect();
		}
	}
//	switch (lKey)
//	{
//		case KEY_ENTER:
//			sStateShutdownTab[sShutdownNow.Index].Confirm();
//			break;
//
//		default:
//			break;
//	}
}
