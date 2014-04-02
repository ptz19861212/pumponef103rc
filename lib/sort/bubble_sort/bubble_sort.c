/**
 * @file    bubble.c
 * @brief   冒泡排序
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-12-11 11:09:20 星期三 
 * @history (1).2013-12-11 11:09:20 星期三 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#include "bubble_sort_in.h"


/**
 * @brief   冒泡排序 8位数值
 */
void BubbleSortU8(uint8_t lArray[], uint16_t lNumber)
{
	uint8_t lTemp;
	uint16_t lI, lJ;
	uint8_t lFlag;

	for (lI = 0; lI < (lNumber - 1); lI++)
	{
		lFlag = 1;

		for (lJ = 0; lJ < (lNumber - lI - 1); lJ++)
		{
			if (lArray[lJ] > lArray[lJ + 1])
			{
				lTemp = lArray[lJ];
				lArray[lJ] = lArray[lJ + 1];
				lArray[lJ + 1] = lTemp;
				lFlag = 0;
			}
		}

		if (lFlag == 1)
			break;
	}
	return;
}


/**
 * @brief   冒泡排序 16位数值
 */
void BubbleSortU16(uint16_t lArray[], uint16_t lNumber)
{
	uint16_t lTemp;
	uint16_t lI, lJ;
	uint8_t lFlag;

	for (lI = 0; lI < (lNumber - 1); lI++)
	{
		lFlag = 1;

		for (lJ = 0; lJ < (lNumber - lI - 1); lJ++)
		{
			if (lArray[lJ] > lArray[lJ + 1])
			{
				lTemp = lArray[lJ];
				lArray[lJ] = lArray[lJ + 1];
				lArray[lJ + 1] = lTemp;
				lFlag = 0;
			}
		}

		if (lFlag == 1)
			break;
	}
	return;
}


/**
 * @brief   冒泡排序 32位数值
 */
void BubbleSortU32(uint32_t lArray[], uint16_t lNumber)
{
	uint32_t lTemp;
	uint16_t lI, lJ;
	uint8_t lFlag;

	for (lI = 0; lI < (lNumber - 1); lI++)
	{
		lFlag = 1;

		for (lJ = 0; lJ < (lNumber - lI - 1); lJ++)
		{
			if (lArray[lJ] > lArray[lJ + 1])
			{
				lTemp = lArray[lJ];
				lArray[lJ] = lArray[lJ + 1];
				lArray[lJ + 1] = lTemp;
				lFlag = 0;
			}
		}

		if (lFlag == 1)
			break;
	}
	return;
}

