/**
 * @file    str_to_num.c
 * @brief   字符串转数字
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-12-31 17:25:06 星期二 
 * @history (1).2013-12-31 17:25:06 星期二 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#include "str_to_num_in.h"



/**
 * @brief   16位字符串转换数字
 * 				例如：654321.2， 那么lNum = 6543212，lPoint = POINT_HHHHXH
 *
 * @param   lpValue
 */
void StrToDecU16(S_Value_Array_U16* lpValue)
{
	uint8_t lI;
	uint8_t lLen;

	lpValue->Value.Num = 0;
	lpValue->Value.Point = 0;

	for (lI = 0; lI < 6; lI++)
	{
		if ((lpValue->Char[lI] >= '0') && (lpValue->Char[lI] <= '9'))
		{
			lpValue->Value.Num *= 10;
			lpValue->Value.Num += lpValue->Char[lI] - '0';
		}
		// 小数点位置
		else if (lpValue->Char[lI] == '.')
		{
			lpValue->Value.Point = strlen(lpValue->Char) - 1 -lI;
		}
		// 结束符
		else if (lpValue->Char[lI] == 0)
		{
			break;
		}
	}
}


/**
 * @brief   32位字符串转换数字
 * 				例如：654321.2， 那么lNum = 6543212，
 * 				lPoint = POINT_HHHHXH
 *
 * @param   lpValue
 */
void StrToDecU32(S_Value_Array_U32* lpValue)
{
	uint8_t lI;
	uint8_t lLen;

	lpValue->Value.Num = 0;
	lpValue->Value.Point = 0;

	// 10位数字和一位小数点
	for (lI = 0; lI < 11; lI++)
	{
		if ((lpValue->Char[lI] >= '0') && (lpValue->Char[lI] <= '9'))
		{
			lpValue->Value.Num *= 10;
			lpValue->Value.Num += lpValue->Char[lI] - '0';
		}
		// 小数点位置
		else if (lpValue->Char[lI] == '.')
		{
			lpValue->Value.Point = strlen(lpValue->Char) - 1 -lI;
		}
		// 结束符
		else if (lpValue->Char[lI] == 0)
		{
			break;
		}
	}
}
