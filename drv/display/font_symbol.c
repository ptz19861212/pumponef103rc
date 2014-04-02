/**
 * @file    font_symbol.c
 * @brief   符号
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-08-21 13:10:00 星期三 
 * @history (1).2013-08-21 13:10:00 星期三 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#include "font_symbol_in.h"
//// 显示左上角风扇状态
//#define DIS_SYM_FAN_FONT				cFontSymFan9x9
//#define DIS_SYM_FAN_SIZE_X				9
//#define DIS_SYM_FAN_SIZE_Y				9
//#define DIS_SYM_FAN_SIZE					18
//
//// 显示左上角充电状态
//#define DIS_SYM_CHAR_FONT				cFontSymChar4x8
//#define DIS_SYM_CHAR_SIZE_X				4
//#define DIS_SYM_CHAR_SIZE_Y				8
//
//// 显示大号充电状态
//#define DIS_SYM_CHAR_LAR_FONT				cFontSymChar33x16
//#define DIS_SYM_CHAR_LAR_SIZE_X				33
//#define DIS_SYM_CHAR_LAR_SIZE_Y				16
//
//// 显示大号充满状态
//#define DIS_SYM_FULL_FONT				cFontSymFul18x23
//#define DIS_SYM_FULL_SIZE_X				18
//#define DIS_SYM_FULL_SIZE_Y				23
//
//// 显示电池状态
//#define DIS_SYM_BAT_FONT				cFontSymBat16x8
//#define DIS_SYM_BAT_SIZE_X				16
//#define DIS_SYM_BAT_SIZE_Y				8
//#define DIS_SYM_BAT_SIZE				16


// 风扇
const S_Lcd_Txt gLcdSymbolFan =
{
		cFontSymFan9x9,
		9,
		9,
		9,
		9,
		18,

//		cFontSymFan14x14,
//		14,
//		14,
//		14,
//		14,
//		28,
};

// 充电符号 小充电符号，在电池符号旁边
const S_Lcd_Txt gLcdSymbolCharge =
{
		cFontSymChar4x8,
		4,
		8,
		4,
		8,
		8,
};

// 充电符号 大充电符号，在屏幕中间使用
const S_Lcd_Txt gLcdSymbolChargeLarge =
{
		cFontSymChar33x16,
		33,
		16,
		33,
		16,
		80,
};

// 充电符号 充电满符号，在屏幕中间使用
const S_Lcd_Txt gLcdSymbolChargeFullLarge =
{
		cFontSymFul18x23,
		18,
		23,
		18,
		23,
		69,
};

// 电池符号
const S_Lcd_Txt gLcdSymbolBat =
{
		cFontSymBat16x8,
		16,
		8,
		16,
		8,
		16,
};



//// correct
//const uint8_t cFontSymCor12x9[] =
//{
//	/* %MATRIXCODE_HEAD_FONT%*/
//	/* 图像 D:\development\tool\matrix\CharacterMatrix\20130821104115394_easyicon_net_16.jpg   12x9   */
//	0x00,0x30,0x00,0x70,0x00,0xE0,0x01,0xC0,0xC3,0x80,0xE7,0x00,0x7E,0x00,0x3C,0x00,
//	0x18,0x00,
//};
//
//// wrong
//const uint8_t cFontSymWron9x9[] =
//{
//	/* %MATRIXCODE_HEAD_FONT%*/
//	/* 图像 D:\development\tool\matrix\CharacterMatrix\20130821104555696_easyicon_net_16.jpg    9x9   */
//	0x41,0x80,0xE3,0x80,0x77,0x00,0x3E,0x00,0x1C,0x00,0x3E,0x00,0x77,0x00,0xE3,0x80,
//	0x41,0x80,
//};

// fan
const uint8_t cFontSymFan9x9[] =
{

	/* %MATRIXCODE_HEAD_FONT%*/ // 全
	/* 图像 D:\development\tool\matrix\CharacterMatrix\correct\20130821104115394_easyicon_net_16.jpg    9x9   */
	0x87,0x80,0xC7,0x00,0xE6,0x00,0xF4,0x00,0x08,0x00,0x17,0x80,0x33,0x80,0x71,0x80,
	0xF0,0x80,

	/* %MATRIXCODE_HEAD_FONT%*/ // 反全
	/*  1[0x0031]   9x9   */
	0xF0,0x80,0x71,0x80,0x33,0x80,0x17,0x80,0x08,0x00,0xF4,0x00,0xE6,0x00,0xC7,0x00,
	0x87,0x80,

	/* %MATRIXCODE_HEAD_FONT%*/ // 半边
	/* 图像 D:\development\tool\matrix\CharacterMatrix\battery\20.jpg    9x9   */
	0x80,0x00,0xC0,0x00,0xE0,0x00,0xF0,0x00,0x08,0x00,0x07,0x80,0x03,0x80,0x01,0x80,
	0x00,0x80,

	/* %MATRIXCODE_HEAD_FONT%*/ //半边
	/* 图像 D:\development\tool\matrix\CharacterMatrix\correct\20130821104555696_easyicon_net_16.jpg    9x9   */
	0x07,0x80,0x07,0x00,0x06,0x00,0x04,0x00,0x08,0x00,0x10,0x00,0x30,0x00,0x70,0x00,
	0xF0,0x00,

	/* %MATRIXCODE_HEAD_FONT%*/ // 椭圆
	/*  4[0x0034]   9x9   */
	0x03,0x80,0x07,0x80,0x07,0x80,0x07,0x00,0x08,0x00,0x70,0x00,0xF0,0x00,0xF0,0x00,
	0xE0,0x00,
	/* %MATRIXCODE_HEAD_FONT%*/ // 椭圆
	/*  5[0x0035]   9x9   */
	0xE0,0x00,0xF0,0x00,0xF0,0x00,0x70,0x00,0x08,0x00,0x07,0x00,0x07,0x80,0x07,0x80,
	0x03,0x80,

	/* %MATRIXCODE_HEAD_FONT%*/ //45度
	/*  2[0x0032]   9x9   */
	0x10,0x00,0x71,0x00,0x33,0x00,0x17,0x80,0x08,0x00,0xF4,0x00,0x66,0x00,0x47,0x00,
	0x04,0x00,


	/* %MATRIXCODE_HEAD_FONT%*/ // 45度第二种
	/*  3[0x0033]   9x9   */
	0x10,0x00,0x32,0x00,0x73,0x00,0x17,0x80,0x08,0x00,0xF4,0x00,0x67,0x00,0x26,0x00,
	0x04,0x00,
};


// fan
const uint8_t cFontSymFan14x14[] =
{
		/* %MATRIXCODE_HEAD_FONT%*/ // 全
		/*  1[0x0031]  14x14  */
		0x00,0x00,0x70,0x38,0x78,0x78,0x7C,0xF8,0x3C,0xF0,0x1C,0xE0,0x03,0x00,0x03,0x00,
		0x1C,0xE0,0x3C,0xF0,0x7C,0xF8,0x78,0x78,0x70,0x38,0x00,0x00,

		/* %MATRIXCODE_HEAD_FONT%*/ //半边
		/*  1[0x0031]  14x14  */
		0x00,0x00,0x00,0x38,0x00,0x78,0x00,0xF8,0x00,0xF0,0x00,0xE0,0x03,0x00,0x03,0x00,
		0x1C,0x00,0x3C,0x00,0x7C,0x00,0x78,0x00,0x70,0x00,0x00,0x00,

		/* %MATRIXCODE_HEAD_FONT%*/ //半边
		/*  1[0x0031]  14x14  */
		0x00,0x00,0x70,0x00,0x78,0x00,0x7C,0x00,0x3C,0x00,0x1C,0x00,0x03,0x00,0x03,0x00,
		0x00,0xE0,0x00,0xF0,0x00,0xF8,0x00,0x78,0x00,0x38,0x00,0x00,

};

// Charge 4x8 小充电符号，在电池符号旁边
const uint8_t cFontSymChar4x8[] =
{
	/* %MATRIXCODE_HEAD_FONT%*/
	/* 图像 D:\development\tool\matrix\CharacterMatrix\battery\charge.jpg    4x8   */
	0x90,0x90,0x90,0xF0,0xF0,0x60,0x60,0x60,
};

// charge 大充电符号，在屏幕中间使用
const uint8_t cFontSymChar33x16[] =
{
	/* %MATRIXCODE_HEAD_FONT%*/
	/* 图像 D:\development\tool\matrix\CharacterMatrix\20130821100225364_easyicon_net_96.jpg   33x16  */
	0x00,0x07,0xFF,0x80,0x00,0x00,0x0F,0xFF,0x80,0x00,0x00,0x1F,0xFF,0x80,0x00,0x00,
	0x3F,0xFF,0xFF,0x80,0x00,0x7F,0xFF,0xFF,0x80,0x00,0xFF,0xFF,0x80,0x00,0xFF,0xFF,
	0xFF,0x80,0x00,0xFF,0xFF,0xFF,0x80,0x00,0xFF,0xFF,0xFF,0x80,0x00,0xFF,0xFF,0xFF,
	0x80,0x00,0x00,0xFF,0xFF,0x80,0x00,0x00,0x7F,0xFF,0xFF,0x80,0x00,0x3F,0xFF,0xFF,
	0x80,0x00,0x1F,0xFF,0x80,0x00,0x00,0x0F,0xFF,0x80,0x00,0x00,0x07,0xFF,0x80,0x00,
};

// full 充电满符号，在屏幕中间使用
const uint8_t cFontSymFul18x23[] =
{
	/* %MATRIXCODE_HEAD_FONT%*/
	/* 图像 D:\development\tool\matrix\CharacterMatrix\20130821091933874_easyicon_net_96.jpg   18x23  */
	0x00,0x08,0x00,0x00,0x10,0x00,0x00,0x30,0x00,0x00,0x60,0x00,0x00,0xE0,0x00,0x01,
	0xC0,0x00,0x03,0xC0,0x00,0x07,0x80,0x00,0x0F,0x80,0x00,0x1F,0x00,0x00,0x3F,0xFF,
	0xC0,0x7F,0xFF,0x80,0xFF,0xFF,0x00,0x00,0x3E,0x00,0x00,0x7C,0x00,0x00,0x78,0x00,
	0x00,0xF0,0x00,0x00,0xE0,0x00,0x01,0xC0,0x00,0x01,0x80,0x00,0x03,0x00,0x00,0x02,
	0x00,0x00,0x04,0x00,0x00,
};

// bat 电池符号
const uint8_t cFontSymBat16x8[] =
{
	/* %MATRIXCODE_HEAD_FONT%*/
	/* 图像 D:\development\tool\matrix\CharacterMatrix\battery\none.jpg   16x8   */
	0x3F,0xFF,0x20,0x01,0xE3,0x31,0xE1,0xE1,0xE1,0xE1,0xE3,0x31,0x20,0x01,0x3F,0xFF,
	/* %MATRIXCODE_HEAD_FONT%*/
	/* 图像 D:\development\tool\matrix\CharacterMatrix\battery\20.jpg   16x8   */
	0x3F,0xFF,0x20,0x01,0xE0,0x0D,0xE0,0x0D,0xE0,0x0D,0xE0,0x0D,0x20,0x01,0x3F,0xFF,
	/* %MATRIXCODE_HEAD_FONT%*/
	/* 图像 D:\development\tool\matrix\CharacterMatrix\battery\40.jpg   16x8   */
	0x3F,0xFF,0x20,0x01,0xE0,0x3D,0xE0,0x3D,0xE0,0x3D,0xE0,0x3D,0x20,0x01,0x3F,0xFF,
	/* %MATRIXCODE_HEAD_FONT%*/
	/* 图像 D:\development\tool\matrix\CharacterMatrix\battery\60.jpg   16x8   */
	0x3F,0xFF,0x20,0x01,0xE0,0xFD,0xE0,0xFD,0xE0,0xFD,0xE0,0xFD,0x20,0x01,0x3F,0xFF,
	/* %MATRIXCODE_HEAD_FONT%*/
	/* 图像 D:\development\tool\matrix\CharacterMatrix\battery\80.jpg   16x8   */
	0x3F,0xFF,0x20,0x01,0xE3,0xFD,0xE3,0xFD,0xE3,0xFD,0xE3,0xFD,0x20,0x01,0x3F,0xFF,
	/* %MATRIXCODE_HEAD_FONT%*/
	/* 图像 D:\development\tool\matrix\CharacterMatrix\battery\100.jpg   16x8   */
	0x3F,0xFF,0x20,0x01,0xEF,0xFD,0xEF,0xFD,0xEF,0xFD,0xEF,0xFD,0x20,0x01,0x3F,0xFF,
	/* %MATRIXCODE_HEAD_FONT%*/
	/* 图像 D:\development\tool\matrix\CharacterMatrix\battery\full.jpg   16x8   */
	0x3F,0xFF,0x21,0x21,0xEE,0x3D,0xEC,0x3D,0xEF,0x0D,0xEF,0x1D,0x21,0x21,0x3F,0xFF,
};