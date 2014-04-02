/**
 * @file    flush_right.c
 * @brief   右移
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-08-13 17:26:07 星期二 
 * @history (1).2013-08-13 17:26:07 星期二 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#include "flush_right_in.h"


/**
 * @brief   右移，主要用于字符数组的右移，移动指定的数组，把前面的标志性字符去除，
 * 				其他的右移，在后面在添加上标志性字符。
 * 				例如 原来[b][c][d][a][a]，那么lLength就是5,lFlag就是[a]，转换结束
 * 				就是[a][a][b][c][d]
 *
 * @param   lData[]
 * @param   lLength 只针对这个长度的数组进行操作
 * @param   lFlag 前面需要清除的标志性字符
 */
void FlushRight(uint8_t lData[], uint8_t lLength, uint8_t lFlag)
{
	uint8_t lI, lJ;

	if (lData[lLength - 1] != lFlag)
		return;

	for (lI = lLength - 1; lI > 0; lI--)
	{
		// 右边数第二个开始
		if (lData[lI - 1] != lFlag)
		{
			for (lJ = 0; lJ < lI; lJ++)
			{
				/*lData[lLength - 1 - lJ] = */
					/*lData[lLength - 1 - (lLength - lI) - lJ];*/
				// 简化一下就是下面这个
				lData[lLength - 1 - lJ] = lData[lI - 1 - lJ];
			}

			for (; lJ < lLength; lJ++)
			{
				lData[lLength - 1 - lJ] = lFlag;
			}

			break;
		}
	}

}


/**
 * @brief   右移，主要用于字符串的右移。移动指定字符数组，把前面的标志性字符去除，
 * 				其他的右移，在后面加上'\0'结束。
 * 				例如原来是[b][c][d][\0]，那么lLength是5,lFlag就是[a]，转换结束
 * 				就是[a][a][b][c][d][\0]，这样的字符串。
 *
 * @param   lData[]
 * @param   lLength 只针对这个长度的数组进行操作，这个长度不包换'\0'，类似于 strlen 求出
 * 				的字符串长度，如果这个长度中的字符都是标志字符，那么将在[0]这个起始位置放入
 * 				'\0'
 * @param   lFlag 前面需要清除的标志性字符
 */
void FlushRightStr(uint8_t *lData, uint8_t lLength, uint8_t lFlag)
{
	uint8_t lI, lJ;
	uint8_t lLen;

	lLen = strlen(lData);

	if (lLen > lLength)
		return;

	for (lI = 0; lI < lLen; lI++)
	{
		lData[lLength - 1 - lI] = lData[lLen - 1 - lI];
	}

	for (; lI < lLength; lI++)
	{
		lData[lLength - 1 - lI] = lFlag;
	}

	lData[lLength] = 0;

}
