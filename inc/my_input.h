/**
 * @file    my_input.h
 * @brief   输入
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-12-31 15:19:47 星期二 
 * @history (1).2013-12-31 15:19:47 星期二 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __MY_INPUT_H__
#define __MY_INPUT_H__

#include <stdint.h>
// 为了16位和32位数字的预编译
#include "config_bsp.h"

typedef struct
{
	// 初始值
	uint16_t Init;
	// 当前值
	uint16_t Now;
	// 上限
	uint16_t Up;
	// 下限
	uint16_t Low;
	// 小数点
	uint8_t Point;
}S_Value_Input_U16;


#if (CONFIG_GAS_VALUE_BITS == 16)
		typedef S_Value_Input_U16 	S_Value_Input_Gas;
#endif


#endif
