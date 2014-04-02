/**
 * @file    str_to_num.h
 * @brief   字符串转数字
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-12-31 17:25:38 星期二 
 * @history (1).2013-12-31 17:25:38 星期二 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __STR_TO_NUM_H__
#define __STR_TO_NUM_H__


#include "my_num.h"


/**
 * @brief   16位字符串转换数字
 * 				例如：654321.2， 那么lNum = 6543212，lPoint = POINT_HHHHXH
 *
 * @param   lpValue
 */
void StrToDecU16(S_Value_Array_U16* lpValue);


/**
 * @brief   32位字符串转换数字
 * 				例如：654321.2， 那么lNum = 6543212，
 * 				lPoint = POINT_HHHHXH
 *
 * @param   lpValue
 */
void StrToDecU32(S_Value_Array_U32* lpValue);


#endif
