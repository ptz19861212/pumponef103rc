/**
 * @file    average.c
 * @brief   求平均数
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-12-11 13:00:06 星期三 
 * @history (1).2013-12-11 13:00:06 星期三 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#include "average_in.h"


/**
 * @brief   数组求平均数，8位无符号数
 */
uint8_t AverageU8(uint8_t *lpBuf, uint16_t lNum)
{
	uint32_t lSum;
	uint16_t lI;

	if (lNum == 0)
	{
		return 0;
	}

	lSum = 0;

	for (lI = 0; lI < lNum; lI++)
	{
		lSum+= *(lpBuf + lI);
	}

	return lSum / lNum;
}


/**
 * @brief   数组求平均数，16位无符号数
 */
uint16_t AverageU16(uint16_t *lpBuf, uint16_t lNum)
{
	uint32_t lSum;
	uint16_t lI;

	if (lNum == 0)
	{
		return 0;
	}

	lSum = 0;

	for (lI = 0; lI < lNum; lI++)
	{
		lSum+= *(lpBuf + lI);
	}

	return lSum / lNum;
}


/**
 * @brief   数组求平均数，32位无符号数
 */
uint32_t AverageU32(uint32_t *lpBuf, uint16_t lNum)
{
	uint64_t lSum;
	uint16_t lI;

	if (lNum == 0)
	{
		return 0;
	}

	lSum = 0;

	for (lI = 0; lI < lNum; lI++)
	{
		lSum+= *(lpBuf + lI);
	}

	return lSum / lNum;
}


// 滑动窗口求平均
static struct S_AverageMoveU16 sAvgMovU16;


/**
 * @brief   设置数组地址，位数求滑动平均数，16位无符号数值
 */
void AverageMoveSetU16(uint16_t *lpBuf, uint8_t lNum)
{
	sAvgMovU16.Array = lpBuf;
	sAvgMovU16.Num = lNum;
}


/**
 * @brief   数组求滑动平均数，16位无符号数
 */
uint16_t AverageMoveU16(uint16_t lData)
{
	uint16_t lI;

	sAvgMovU16.Sum -= sAvgMovU16.Array[sAvgMovU16.Index];
	sAvgMovU16.Sum += lData;
	sAvgMovU16.Array[sAvgMovU16.Index] = lData;
	sAvgMovU16.Index++;

	if (sAvgMovU16.Index >= sAvgMovU16.Num)
	{
		sAvgMovU16.Index = 0;
	}

	sAvgMovU16.Average = sAvgMovU16.Sum / sAvgMovU16.Num;

	return sAvgMovU16.Average;
}
