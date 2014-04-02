/**
 * @file    num_limit.c
 * @brief   
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2014-01-16 10:25:08 星期四 
 * @history (1).2014-01-16 10:25:08 星期四 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#include "num_limit_in.h"



/**
 * @brief   两个16位数字组成的字符串进行上限的限制，注意因为是字符串
 * 				所以有可能溢出，所以才有了这个函数，函数内部作为32位数
 * 				进行处理
 *
 * @param   lpNow
 * @param   lpUp
 */
void DecStrLimitUpperU16(char* lpNow, char* lpUp)
{
	S_Value_Array_U32 lNow, lUp;

	lNow.Char = lpNow;
	lUp.Char = lpUp;

	StrToDecU32(&lNow);
	StrToDecU32(&lUp);

	if (lNow.Value.Num > lUp.Value.Num)
	{
		uint8_t lI, lLen;

		lLen = strlen(lpUp);

		// 赋值为上限
		for (lI = 0; lI < lLen; lI++)
		{
			*(lpNow + lI) = *(lpUp + lI);
		}
		// 结束符
		*(lpNow + lI) = 0;
	}
}


/**
 * @brief   两个16位数字组成的字符串进行上限的限制，注意因为是字符串
 * 				所以有可能溢出，所以才有了这个函数，函数内部作为32位数
 * 				进行处理
 *
 * @param   lpNow
 * @param   lpUp
 */
void DecStrLimitLowerU16(char* lpNow, char* lpLow)
{
	S_Value_Array_U32 lNow, lLow;

	lNow.Char = lpNow;
	lLow.Char = lpLow;

	StrToDecU32(&lNow);
	StrToDecU32(&lLow);

	if (lNow.Value.Num < lLow.Value.Num)
	{
		uint8_t lI, lLen;

		lLen = strlen(lpLow);

		// 赋值为上限
		for (lI = 0; lI < lLen; lI++)
		{
			*(lpNow + lI) = *(lpLow + lI);
		}
		// 结束符
		*(lpNow + lI) = 0;
	}
}
