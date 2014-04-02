/**
 * @file    calendar_lang.c
 * @brief   日历语言转换
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2014-01-22 15:36:38 星期三 
 * @history (1).2014-01-22 15:36:38 星期三 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#include "calendar_lang_in.h"

static const char* sCalMonthAbEn[] =
{
		"Jan",
		"Feb",
		"Mar",
		"Apr",
		"May",
		"Jun",
		"Jul",
		"Aug",
		"Sep",
		"Oct",
		"Nov",
		"Dec",
};


//static const char* sCalMonthCn[] =
//{
//		"一月",
//		"二月",
//		"三月",
//		"四月",
//		"五月",
//		"六月",
//		"七月",
//		"八月",
//		"九月",
//		"十月",
//		"十一月",
//		"十二月",
//};



/**
 * @brief   把英文的日期转换为数字
 *
 * @param   lpEn 英文的日历地址
 * @param   lpDate 数字的日历地址
 */
void CalDateEnToNum(const char* lpEn, S_Calendar_Date* lpDate)
{
	uint8_t lI;
	char* lpBuf;

	lpBuf = (char*)lpEn;

	// 清除前面的空格
	while(*lpBuf == ' ')
	{
		lpBuf++;
	}

	// 转换月份
	for (lI = 0; lI < 12; lI++)
	{
		if (memcmp(sCalMonthAbEn[lI], lpBuf, 3) == 0)
		{
			break;
		}
	}

	lpDate->Mon = lI;

	// 因为月份的英文缩写是3个
	lpBuf+= 3;

	// 跳过空格
	while(*lpBuf == ' ')
	{
		lpBuf++;
	}

	char lArray[5];

	// 转换日
	for (lI = 0; lI < 2; lI++)
	{
		if (*lpBuf == ' ')
		{
			break;
		}

		lArray[lI] = *lpBuf;
		lpBuf++;
	}
	lArray[lI] = 0;

	S_Value_Array_U16 lValue;
	lValue.Char = lArray;

	StrToDecU16(&lValue);
	lpDate->Day = lValue.Value.Num;

	while(*lpBuf == ' ')
	{
		lpBuf++;
	}

	// 转换年
	for (lI = 0; lI < 4; lI++)
	{
		if ((*lpBuf == ' ') || (*lpBuf == 0))
		{
			break;
		}

		lArray[lI] = *lpBuf;
		lpBuf++;
	}
	lArray[lI] = 0;

	lValue.Char = lArray;

	StrToDecU16(&lValue);
	lpDate->Year = lValue.Value.Num;
}


/**
 * @brief   把日期转换为中文
 *
 * @param   lpCn 中文的日历地址
 * @param   lpDate 数字的日历地址
 */
void CalDateNumToCn(char* lpCn, S_Calendar_Date* lpDate)
{
	S_Value_Array_U16 lValue;
	uint8_t lLen;

	lValue.Char = lpCn;
	lValue.Value.Num = lpDate->Year;
	lValue.Value.Point = POINT_HHHHH;
	DecToStrU16(&lValue);

	lLen = strlen(lpCn);
	strcpy(lpCn + lLen, "年");

	lLen = strlen(lpCn);
	lValue.Char = lpCn + lLen;
	lValue.Value.Num = lpDate->Mon + 1;
	lValue.Value.Point = POINT_HHHHH;
	DecToStrU16(&lValue);

	lLen = strlen(lpCn);
	strcpy(lpCn + lLen, "月");
//	strcpy(lpCn + lLen, sCalMonthCn[lpDate->Mon]);

	lLen = strlen(lpCn);

	lValue.Char = lpCn + lLen;
	lValue.Value.Num = lpDate->Day;
	lValue.Value.Point = POINT_HHHHH;
	DecToStrU16(&lValue);

	lLen = strlen(lpCn);
	strcpy(lpCn + lLen, "日");
}
