/**
 * @file    key_in.h
 * @brief   按键
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-12-03 09:15:15 星期二 
 * @history (1).2013-12-03 09:15:15 星期二 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __KEY_IN_H__
#define __KEY_IN_H__

#include "stm32f10x_gpio.h"
#include "bit_get.h"
#include "my_define.h"
#include "my_errno.h"
#include "key.h"

// 按键的数目
#define CONFIG_KEYS_NUMBER					4
// 计数多少次算长按
#define CONFIG_KEYS_LONG						50
// 计数多少次算长按导致的快速按键
#define CONFIG_KEYS_CONTINUE					5
// 计算出来的快速按键推导出的长按的时间
#define CONFIG_KEYS_CONT_COUNT				(CONFIG_KEYS_LONG /\
													CONFIG_KEYS_CONTINUE)

#endif
