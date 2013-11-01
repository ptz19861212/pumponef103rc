/**
 * @file    char_swap.c
 * @brief   字符数组颠倒
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-08-14 13:08:12 星期三 
 * @history (1).2013-08-14 13:08:12 星期三 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#include "char_swap_in.h"

/**
 * @brief   字符数组中的字符对调
 *
 * @param   lpStr
 * @param   lLen
 */
void CharSwap(char *lpStr, uint8_t lLen)
{
	uint8_t lI, lNum, lTemp;

	lNum = lLen >> 1;

	for (lI = 0; lI < lNum; lI++)
		SWAP((*(lpStr + lI)), (*(lpStr + lLen - lI - 1)));
}
