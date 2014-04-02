/**
 * @file    font_chinese.h
 * @brief   中文
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-08-13 17:07:32 星期二 
 * @history (1).2013-08-13 17:07:32 星期二 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __FONT_CHINESE_H__
#define __FONT_CHINESE_H__

#include <stdint.h>
#include "my_language.h"
#include "my_display.h"

extern const uint8_t cFontChineseCompany[];


// 横向取模，左高右低
extern const S_Dual_Byte_Character_16x16 cFontChinese[];
extern const S_Lcd_Txt gLcdTxt16x16;


/**
 * @brief   字库里面的字符数目，因为sizeof使用有局限性，所以才有这个
 */
uint16_t FontChineseSizeGet(void);

#endif
