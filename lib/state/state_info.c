/**
 * @file    state_info.c
 * @brief   提示
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

#include "state_info_in.h"


//// 提示字符串 英文
//const char *sInfoEn[] =
//{
//		"Shut Down",
//		"",
//};
//
//// 提示字符串 中文
//const char *sInfoCn[] =
//{
//		"提示",
//		"",
//};
//
//// 提示字符串 指针数组
//const char **sInfoTxt[] =
//{
//		sInfoEn,
//		sInfoCn,
//};


S_StateInfo sInfo;

// 用于按键表
S_Info_Tab sInfoNow;


/**
 * @brief   获得提示外部输入结构体指针
 *
 * @return
 */
S_Info* StateInfoPointGet(void)
{
	return &(sInfo.Out);
}


/**
 * @brief   提示秒数值的那一行的正常显示
 */
//static void StateInfoSecDisp(void)
//{
//	S_Lcd__Item_Mid lTrig;
//
//	char lData[GAS_VALUE_ARRAY_SIZE];
//	S_Value_Array_U16 lArray;
//
//	lArray.Char = lData;
//	lArray.Value.Num = sInfo.Out.Time;
//	lArray.Value.Point = POINT_HHHHH;
//
//	DecToStrU16(&lArray);
//	lTrig.Item.Pos = CONFIG_INFO_POS + 1;
//	lTrig.Item.Char = lData;
//	lTrig.Len = CONFIG_INFO_LEN;
//	Lcd__FrameItemMidDisp(&lTrig);
//}


/**
 * @brief   提示ADC或气体数值的那一行的正常显示
 */
//static void StateInfoValueDisp(S_Value_U16* lpValue)
//{
//	S_Lcd__Item_Mid lTrig;
//
//	char lData[GAS_VALUE_ARRAY_SIZE];
//	S_Value_Array_U16 lArray;
//
//	lArray.Char = lData;
//
//	// 获取数值
////	(*sInfo.Out.Func.ValueGet)(&(lArray.Value));
//	lArray.Value.Num = lpValue->Num;
//	lArray.Value.Point = lpValue->Point;
//
//	DecToStrU16(&lArray);
//	lTrig.Item.Pos = CONFIG_INFO_POS;
//	lTrig.Item.Char = lData;
//	lTrig.Len = CONFIG_INFO_LEN;
//	Lcd__FrameItemMidDispHalf(&lTrig);
//}


/**
 * @brief   显示提示
 */
//void StateInfoDisp(void)
//{

	// 画框架
//	S_Lcd_Area_RectangleShade lRec;
//	lRec.Ex.X = CONFIG_INFO_FRAME_EX_X;
//	lRec.Ex.Y = CONFIG_INFO_FRAME_EX_Y;
//	lRec.PS.X = CONFIG_INFO_FRAME_X_START;
//	lRec.PS.Y = CONFIG_INFO_FRAME_Y_START;
//	lRec.PE.X = CONFIG_INFO_FRAME_X_END;
//	lRec.PE.Y = CONFIG_INFO_FRAME_Y_END;
//	DisRecFramSet(&lRec);

//	S_Lcd__Item_Mid lTrig;
//
//	lTrig.Item.Pos = CONFIG_INFO_POS;
//	lTrig.Item.Char = sInfo.Out.Info;
//	lTrig.Len = CONFIG_INFO_LEN;
//	Lcd__FrameItemMidDispHalf(&lTrig);
//}


//// 秒
//static my_second_t sInfoSecond;
//// 秒内的计数，这个是为了整秒，不然第一秒长短不一
//static uint8_t sInfoCount;

/**
 * @brief   菜单项提示的初始显示，包括数值本身的显示
 *
 * @param   lpInfo
 */
void StateInfoInit(void)
{
	// 初始的
	sInfo.Line.Index = 0;
	//
	sInfo.Line.Num = 1;

//	sInfo.DispEnd = E_FALSE;

	// 按键列表索引
//	sInfoNow.Index = STATE_INFO_INDEX;

//	E_Language lLang;
//	// 获得当前显示的语言
//	lLang = Lcd__LangGet();

	DisClr();

	// 画框架
	S_Lcd_Area_RectangleShade lRec;
	lRec.Ex.X = CONFIG_INFO_FRAME_EX_X;
	lRec.Ex.Y = CONFIG_INFO_FRAME_EX_Y;
	lRec.PS.X = CONFIG_INFO_FRAME_X_START;
	lRec.PS.Y = CONFIG_INFO_FRAME_Y_START;
	lRec.PE.X = CONFIG_INFO_FRAME_X_END;
	lRec.PE.Y = CONFIG_INFO_FRAME_Y_END;
	DisRecFramSet(&lRec);



//	uint8_t lI;
//	S_Lcd__Item_Mid lTrig;
//
//	// 显示全部的标签
//	for (lI = 0; lI < STR_NUM(sInfoEn); lI++)
//	{
//		lTrig.Item.Pos = CONFIG_INFO_POS + lI;
//
//		// 电压不足
//		if (sInfo.Out.BatLow == E_TRUE)
//		{
//			lTrig.Item.Char = *(sBatLowTxt[lLang] + lI);
//		}
//		else
//		{
//			lTrig.Item.Char = *(sInfoTxt[lLang] + lI);
//		}
//
//		lTrig.Len = CONFIG_INFO_LEN;
//		Lcd__FrameItemMidDisp(&lTrig);
//	}

	S_Lcd__Item_Mid lTrig;

	lTrig.Item.Pos = CONFIG_INFO_POS;
	lTrig.Item.Char = sInfo.Out.Info;
	lTrig.Len = CONFIG_INFO_LEN;
	Lcd__FrameItemMidDispHalf(&lTrig);

	// 显示秒数
//	StateInfoSecDisp();

//	// 为了整秒
//	S_Device* lpDev;
//	StateDevicePointGet(&lpDev);
//
//	sInfoSecond = lpDev->pTemp->Time.Sec;
//	sInfoCount = lpDev->pTemp->Time.Count;
}


/**
 * @brief   提示处理
 */
void StateInfoSecond(void)
{
//	if (sInfo.DispEnd == E_TRUE)
//	{
//		return;
//	}

	S_Device* lpDev;
	StateDevicePointGet(&lpDev);

	if (lpDev->pTemp->Disp.Fresh != TURN_ON)
	{
		return;
	}

	if (sInfo.Out.Time > 0)
	{
		sInfo.Out.Time--;
	}

//	StateInfoDisp();

//	// 为了整秒
//	if (lpDev->pTemp->Time.Count != sInfoCount)
//	{
//		return;
//	}
//
//	if (lpDev->pTemp->Time.Sec > sInfoSecond)
//	{
//		sInfo.Out.Time--;
//	}
//	else
//	{
//		return;
//	}
//	sInfoSecond = lpDev->pTemp->Time.Sec;

//	S_Value_U16 lValue;
//	sInfo.Out.Func.ValueGet(&lValue);
//
//	if (sInfo.Out.AD == E_TRUE)
//	{
//		StateInfoValueDisp(&lValue);
//	}
//
//	sInfo.Out.Func.ValueSet(&lValue);

//	S_Buzzer lBz;
//	lBz.Src = BUZZER_SECOND;
//	lBz.Time = BUZZER_SECOND_TIME;
//	BuzzerOn(&lBz);

	if (sInfo.Out.Time == 0)
	{
//		sInfo.DispEnd = E_TRUE;
//		sInfo.Out.Func.Info();
		StateInfoToDetect();
	}
//	else
//	{
//		// 显示秒数
////		StateInfoSecDisp();
//	}
}


///**
// * @brief   菜单项最终处理确认
// */
//static void StateInfoConfirm(void)
//{
//	StateInfoToMenu();
//}


// 菜单对应的按键函数
//static const S_Info_Tab sStateInfoTab[] =
//{
////		STATE_INFO_KEY_TAB(,),
//		STATE_INFO_INDEX,
//		StateInfoConfirm,
//
//};


/**
 * @brief   按键 调用函数
 */
void StateInfoKey(uint8_t lKey)
{
//	if (sInfo.Out.BatLow != E_TRUE)
//	{
//		if (lKey != KEY_ENTER)
//		{
//			StateInfoToDetect();
//		}
//	}
//	switch (lKey)
//	{
//		case KEY_ENTER:
//			sStateInfoTab[sInfoNow.Index].Confirm();
//			break;
//
//		default:
//			break;
//	}
}
