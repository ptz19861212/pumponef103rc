/**
 * @file    bit_get.c
 * @brief   求被置位的位所在
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-12-17 21:20:07 星期二 
 * @history (1).2013-12-17 21:20:07 星期二 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#include "bit_get_in.h"


/**
 * @brief   求数字的最右边的被置位的位
 *
 * @param   lpData 数字的地址
 * @param   lpBit 置位的位的地址
 * @param   lBitNum 数字的位数，如果是字节那么就是8,其他以此类推
 *
 * @return  是否出错
 */
int8_t BitGet(uint8_t* lpData, uint8_t* lpBit, uint8_t lBitNum)
{
	uint8_t lTmp, lNum;
	uint8_t lI, lJ;

	// 确定是几个字节
	lNum = lBitNum >> 3;

	for (lI = 0; lI < lNum; lI++)
	{
		lTmp = *(lpData + lI);

		for (lJ = 0; lJ < 8; lJ++)
		{
			if (lTmp & (1 << lJ))
			{
				break;
			}
		}

		// 说明前面匹配到了，所以直接跳出
		if (lJ != 8)
		{
			break;
		}
	}

	*lpBit = (lI << 3) + lJ;

	// 说明一直没有匹配到，所以返回错误
	if ((lI == lNum) && (lJ == 8))
	{
		return -EPERM;
	}
	else
	{
//		*lpBit = (lI << 3) + lJ;
		return ESUC;
	}

}
