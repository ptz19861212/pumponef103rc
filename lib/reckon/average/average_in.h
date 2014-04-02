/**
 * @file    average_in.h
 * @brief   求平均数
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-12-11 13:02:15 星期三 
 * @history (1).2013-12-11 13:02:15 星期三 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __AVERAGE_IN_H__
#define __AVERAGE_IN_H__

#include <stdint.h>
#include "average.h"


// 滑动窗口求平均，16位无符号数
struct S_AverageMoveU16
{
	uint16_t Average;
	uint32_t Sum;
	uint8_t Num;
	uint8_t Index;
	uint16_t *Array;
};

#endif
