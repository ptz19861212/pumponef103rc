/**
 * @file    font_number.h
 * @brief   数字
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-08-13 17:47:20 星期二 
 * @history (1).2013-08-13 17:47:20 星期二 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __FONT_NUMBER_H__
#define __FONT_NUMBER_H__

#include <stdint.h>

extern const uint8_t cFontNumber32x18[];

// 数字 X方向大小
#define FONT_NUMBER_32X18_X						18
// 数字 Y方向大小
#define FONT_NUMBER_32X18_Y						32
// 用来替代数字的空格
#define FONT_NUMBER_32X18_SPACE					0x10
// 数字中的小数点在字库当中的位置
#define FONT_NUMBER_32X18_DOT					0x11
#define FONT_NUMBER_32X18_DOT_X					8
#define FONT_NUMBER_32X18_DOT_Y					32
// 数字中替代小数点的空格
#define FONT_NUMBER_32X18_DOT_SPACE				0x12

#endif
