/**
 * @file    num_to_str.c
 * @brief   数字转换字符串
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-12-06 15:00:49 星期五 
 * @history (1).2013-12-06 15:00:49 星期五 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#include "num_to_str_in.h"


/**
 * @brief   添加小数点,
 * 				例如，2.1，如果原来使用的是8位数字进行保存的，
 * 				那么 lBitsNum就是 TYPE_U8_LEN，lPoint就是 POINT_HHHHXH
 *
 * @param   lpData 需要添加小数点的 数字 字符数组
 * @param   lBitsNum 十进制数字有多少位，如8位数字这个就是3,16位数字就是5,32位数字就是10
 * @param   lPoint 需要添加的小数点所在的位置
 */
static void NumInsertPoint(uint8_t *lpData, uint8_t lBitsNum, 
							uint8_t lPoint)
{
	uint8_t lI;

	// 移出小数点的位置
	if (lPoint != POINT_HHHHH)
	{
		for (lI = 0; lI < (lBitsNum - lPoint); lI++)
			*(lpData + lBitsNum - lI) = *(lpData + lBitsNum - lI - 1);
	}
	else
		lI = 0;

	if (lI > 0)
	{
		// 添加小数点
		*(lpData + lPoint) = '.';

		if (*(lpData + lPoint + 1) == 0)
		{
			// 有需要的在小数点前面补0
			*(lpData + lPoint + 1) = '0';

			for (lI = 1; lI < lPoint; lI++)
			{
				// 如果小数点后面有补0的
				if (*(lpData + lPoint - lI) == 0)
					*(lpData + lPoint - lI) = '0';
				else
					break;
			}
		}
	}
}

/**
 * @brief   8位数字转换为字符串
 * 				例如：3.2， 那么lNum = 32，lPoint = POINT_HHHHXH
 *
 * @param   lpData 十进制数字字符数组的首地址
 * @param   lNum 需要转换的数字（不含小数点）
 * @param   lPoint 需要添加的小数点所在的位置
 */
//void DecToStrU8(uint8_t *lpData, uint8_t lNum, uint8_t lPoint)
void DecToStrU8(S_Value_Array_U8* lpValue)
{
	uint8_t lI;
	uint8_t lDiv1, lDiv2, lDiv3;
	lDiv1 = lDiv2 = lDiv3 = 0;

	uint8_t lNum;
	uint8_t lPoint;

	char* lpData = lpValue->Char;
	lNum = lpValue->Value.Num;
	lPoint = lpValue->Value.Point;

	for (lI = 0; lI < (TYPE_U8_LEN + 1); lI++)
		*(lpData + lI) = 0;

	lDiv1 = DIV_U8_10(lNum);
	*lpData = lNum - 10 * lDiv1 + '0';

	if (lNum >= 10)
	{
		lDiv2 = DIV_U8_10(lDiv1);
		*(lpData + 1) = lDiv1 - 10 * lDiv2 + '0';
	}
	if (lNum >= 100)
	{
		lDiv3 = DIV_U8_10(lDiv2);
		*(lpData + 2) = lDiv2 - 10 * lDiv3 + '0';
	}

	// 补充小数点
	NumInsertPoint(lpData, TYPE_U8_LEN, lPoint);

	// 字符串交换变成正序。
	CharSwap(lpData, TYPE_U8_LEN + 1);
	// 字符串结束附。
	*(lpData + TYPE_U8_LEN + 1) = 0;

	// 左移字符串
	FlushLeftStr(lpData, TYPE_U8_LEN + 1, 0);
}

/**
 * @brief   16位数字转换为字符串
 * 				例如：1234.2， 那么lNum = 12342，lPoint = POINT_HHHHXH
 *
 * @param   lpData 十进制数字字符数组的首地址
 * @param   lNum 需要转换的数字（不含小数点）
 * @param   lPoint 需要添加的小数点所在的位置
 */
//void DecToStrU16(uint8_t *lpData, uint16_t lNum, uint8_t lPoint)
void DecToStrU16(S_Value_Array_U16* lpValue)
{
	uint8_t lI;
	uint16_t lDiv1, lDiv2, lDiv3, lDiv4, lDiv5;
	uint16_t lNum;
	uint8_t lPoint;

	char* lpData = lpValue->Char;
	lNum = lpValue->Value.Num;
	lPoint = lpValue->Value.Point;


	lDiv1 = lDiv2 = lDiv3 = lDiv4 = lDiv5 = 0;

	for (lI = 0; lI < (TYPE_U16_LEN + 1); lI++)
		*(lpData + lI) = 0;

	lDiv1 = DIV_U16_10(lNum);
	*lpData = lNum - 10 * lDiv1 + '0';

	if (lNum >= 10)
	{
		lDiv2 = DIV_U16_10(lDiv1);
		*(lpData + 1) = lDiv1 - 10 * lDiv2 + '0';
	}
	if (lNum >= 100)
	{
		lDiv3 = DIV_U16_10(lDiv2);
		*(lpData + 2) = lDiv2 - 10 * lDiv3 + '0';
	}
	if (lNum >= 1000)
	{
		lDiv4 = DIV_U16_10(lDiv3);
		*(lpData + 3) = lDiv3 - 10 * lDiv4 + '0';
	}
	if (lNum >= 10000)
	{
		lDiv5 = DIV_U16_10(lDiv4);
		*(lpData + 4) = lDiv4 - 10 * lDiv5 + '0';
	}

	// 补充小数点
	NumInsertPoint(lpData, TYPE_U16_LEN, lPoint);

	// 字符串交换变成正序。
	CharSwap(lpData, TYPE_U16_LEN + 1);
	// 字符串结束附。
	*(lpData + TYPE_U16_LEN + 1) = 0;

	// 左移字符串
	FlushLeftStr(lpData, TYPE_U16_LEN + 1, 0);
}

/**
 * @brief   32位数字转换为字符串
 * 				例如：654321.2， 那么lNum = 6543212，lPoint = POINT_HHHHXH
 *
 * @param   lpData 十进制数字字符数组的首地址
 * @param   lNum 需要转换的数字（不含小数点）
 * @param   lPoint 需要添加的小数点所在的位置
 */
//void DecToStrU32(uint8_t *lpData, uint32_t lNum, uint8_t lPoint)
void DecToStrU32(S_Value_Array_U32* lpValue)
{
	uint8_t lI;
	uint32_t lDiv1, lDiv2, lDiv3, lDiv4, lDiv5; 
	uint32_t lDiv6, lDiv7, lDiv8, lDiv9, lDiv10;
	lDiv1 = lDiv2 = lDiv3 = lDiv4 = lDiv5 = 0;
	lDiv6 = lDiv7 = lDiv8 = lDiv9 = lDiv10 = 0;

	uint32_t lNum;
	uint8_t lPoint;

	char* lpData = lpValue->Char;
	lNum = lpValue->Value.Num;
	lPoint = lpValue->Value.Point;

	for (lI = 0; lI < (TYPE_U32_LEN + 1); lI++)
		*(lpData + lI) = 0;

	lDiv1 = DIV_U32_10(lNum);
	*lpData = lNum - 10 * lDiv1 + '0';

	if (lNum >= 10)
	{
		lDiv2 = DIV_U32_10(lDiv1);
		*(lpData + 1) = lDiv1 - 10 * lDiv2 + '0';
	}
	if (lNum >= 100)
	{
		lDiv3 = DIV_U32_10(lDiv2);
		*(lpData + 2) = lDiv2 - 10 * lDiv3 + '0';
	}
	if (lNum >= 1000)
	{
		lDiv4 = DIV_U32_10(lDiv3);
		*(lpData + 3) = lDiv3 - 10 * lDiv4 + '0';
	}
	if (lNum >= 10000)
	{
		lDiv5 = DIV_U32_10(lDiv4);
		*(lpData + 4) = lDiv4 - 10 * lDiv5 + '0';
	}
	if (lNum >= 100000)
	{
		lDiv6 = DIV_U32_10(lDiv5);
		*(lpData + 5) = lDiv5 - 10 * lDiv6 + '0';
	}
	if (lNum >= 1000000)
	{
		lDiv7 = DIV_U32_10(lDiv6);
		*(lpData + 6) = lDiv6 - 10 * lDiv7 + '0';
	}
	if (lNum >= 10000000)
	{
		lDiv8 = DIV_U32_10(lDiv7);
		*(lpData + 7) = lDiv7 - 10 * lDiv8 + '0';
	}
	if (lNum >= 100000000)
	{
		lDiv9 = DIV_U32_10(lDiv8);
		*(lpData + 8) = lDiv8 - 10 * lDiv9 + '0';
	}
	if (lNum >= 1000000000)
	{
		lDiv10 = DIV_U32_10(lDiv9);
		*(lpData + 9) = lDiv9 - 10 * lDiv10 + '0';
	}

	// 补充小数点
	NumInsertPoint(lpData, TYPE_U32_LEN, lPoint);

	// 字符串交换变成正序。
	CharSwap(lpData, TYPE_U32_LEN + 1);
	// 字符串结束附。
	*(lpData + TYPE_U32_LEN + 1) = 0;

	// 左移字符串
	FlushLeftStr(lpData, TYPE_U32_LEN + 1, 0);
}
