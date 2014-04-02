/**
 * @file    font_symbol.h
 * @brief   符号
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-08-21 13:10:45 星期三 
 * @history (1).2013-08-21 13:10:45 星期三 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __FONT_SYMBOL_H__
#define __FONT_SYMBOL_H__

#include <stdint.h>
#include "my_display.h"

// correct
extern const uint8_t cFontSymCor12x9[];

// wrong
extern const uint8_t cFontSymWron9x9[];

// fan
extern const uint8_t cFontSymFan9x9[];
// fan
extern const uint8_t cFontSymFan14x14[];

// Charge 4x8 小充电符号，在电池符号旁边
extern const uint8_t cFontSymChar4x8[];

// charge 大充电符号，在屏幕中间使用
extern const uint8_t cFontSymChar33x16[];

// full 充电满符号，在屏幕中间使用
extern const uint8_t cFontSymFul18x23[];

// bat 电池符号
extern const uint8_t cFontSymBat16x8[];

// 风扇
extern const S_Lcd_Txt gLcdSymbolFan;

// 充电符号 小充电符号，在电池符号旁边
extern const S_Lcd_Txt gLcdSymbolCharge;

// 充电符号 大充电符号，在屏幕中间使用
extern const S_Lcd_Txt gLcdSymbolChargeLarge;

// 充电符号 充电满符号，在屏幕中间使用
extern const S_Lcd_Txt gLcdSymbolChargeFullLarge;

// 电池符号
extern const S_Lcd_Txt gLcdSymbolBat;

#define FONT_SYMBOL_BAT_NONE			0
#define FONT_SYMBOL_BAT_20				1
#define FONT_SYMBOL_BAT_40				2
#define FONT_SYMBOL_BAT_60				3
#define FONT_SYMBOL_BAT_80				4
#define FONT_SYMBOL_BAT_100				5
#define FONT_SYMBOL_BAT_FULL			6

#endif
