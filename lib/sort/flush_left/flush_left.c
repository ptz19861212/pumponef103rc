/**
 * @file    flush_left.c
 * @brief   左移
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

#include "flush_left_in.h"


/**
 * @brief   左移
 *
 * @param   lData[]
 * @param   lLength
 * @param   lFlag
 */
void FlushLeft(uint8_t lData[], uint8_t lLength, uint8_t lFlag)
{
	uint8_t lI, lJ;

	if (lData[0] != lFlag)
		return;

	for (lI = 1; lI < lLength; lI++)
	{
		if (lData[lI] != lFlag)
		{
			for (lJ = 0; lJ < (lLength - lI); lJ++)
				lData[lJ] = lData[lJ + lI];

			for (; lJ < lLength; lJ++)
				lData[lJ] = lFlag;

			break;
		}
	}
}
