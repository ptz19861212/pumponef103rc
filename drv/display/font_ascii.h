/**
 * @file    font_ascii.h
 * @brief   ascii
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-08-09 16:57:09 ������ 
 * @history (1).2013-08-09 16:57:09 ������ create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __FONT_ASCII_H__
#define __FONT_ASCII_H__

#include <stdint.h>
#include "my_display.h"

// ASCII 
extern const uint8_t cFontAscii5x10[];
extern const uint8_t cFontAscii8x16[];
extern const uint8_t cFontAscii12x24[];
extern const uint8_t cFontAscii15x30[];
extern const uint8_t cFontAscii16x32[];

extern const S_Lcd_Txt gLcdTxt5x10;
extern const S_Lcd_Txt gLcdTxt8x16;
extern const S_Lcd_Txt gLcdTxt16x32;

// font ascii mode
// ascii ǰ����Ե������ַ�ĸ���
#define FONT_ASCII_OMIT							0x20

//// ascii
//#define FONT_ASCII_5X10							cFontAscii5x10
//// ascii X�����С
//#define FONT_ASCII_5X10_SIZE_X					5
//// ascii Y�����С
//#define FONT_ASCII_5X10_SIZE_Y					10
//// ascii �ֿ�ÿ���ֿռ�
//#define FONT_ASCII_5X10_SIZE					10

//// ascii
//#define FONT_ASCII_8X16							cFontAscii8x16
//// ascii X�����С
//#define FONT_ASCII_8X16_SIZE_X					8
//// ascii Y�����С
//#define FONT_ASCII_8X16_SIZE_Y					16
//// ascii �ֿ�ÿ���ֿռ�
//#define FONT_ASCII_8X16_SIZE					16

// ascii
#define FONT_ASCII_12X24						cFontAscii12x24
// ascii X�����С
#define FONT_ASCII_12X24_SIZE_X					12
// ascii Y�����С
#define FONT_ASCII_12X24_SIZE_Y					24
// ascii �ֿ�ÿ���ֿռ�
#define FONT_ASCII_12X24_SIZE					36

// ascii
#define FONT_ASCII_15X30						cFontAscii15x30
// ascii X�����С
#define FONT_ASCII_15X30_SIZE_X					15
// ascii Y�����С
#define FONT_ASCII_15X30_SIZE_Y					32
// ascii �ֿ�ÿ���ֿռ�
#define FONT_ASCII_15X30_SIZE					60

//// ascii
//#define FONT_ASCII_16X32						cFontAscii16x32
//// ascii X�����С
//#define FONT_ASCII_16X32_SIZE_X					16
//// ascii Y�����С
//#define FONT_ASCII_16X32_SIZE_Y					32
//// ascii �ֿ�ÿ���ֿռ�
//#define FONT_ASCII_16X32_SIZE					64

#endif
