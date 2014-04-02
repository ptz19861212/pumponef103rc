/**
 * @file    display_uc1701_in.h
 * @brief   显示驱动
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-08-13 15:22:15 星期二 
 * @history (1).2013-08-13 15:22:15 星期二 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __DISPLAY_UC1701_IN_H__
#define __DISPLAY_UC1701_IN_H__

#include "uc1701.h"
#include "display_uc1701.h"
#include "my_display.h"
#include "my_math.h"
#include "font_ascii.h"
#include "font_symbol.h"
#include "flush_left.h"
#include "char_swap.h"
#include "num_to_str.h"
#include "string.h"
#include "font_chinese.h"


// 滚动条文字占有
#define DIS_SCROLL_BAR_TXT_FONT				cFontAscii5x10
#define DIS_SCROLL_BAR_TXT_SIZE_X			5
#define DIS_SCROLL_BAR_TXT_SIZE_Y			10
#define DIS_SCROLL_BAR_TXT_SIZE				10

// 菜单本身文字占有
#define DIS_MENU_SELF_TXT_FONT				cFontAscii8x16
#define DIS_MENU_SELF_TXT_SIZE_X			8
#define DIS_MENU_SELF_TXT_SIZE_Y			16
#define DIS_MENU_SELF_TXT_SIZE				16

// 单位8x16占有的字节数
#define DIS_UNIT_FONT				cFontAscii8x16
#define DIS_UNIT_SIZE_X				8
#define DIS_UNIT_SIZE_Y				16
#define DIS_UNIT_SIZE				16

// 气体名称字符占有的字节数
#define DIS_GAS_NAME_ASCII_FONT			cFontAscii8x16
#define DIS_GAS_NAME_ASCII_SIZE			16
#define DIS_GAS_NAME_ASCII_SIZE_X		8
#define DIS_GAS_NAME_ASCII_SIZE_Y		16
#define DIS_GAS_NAME_NUM_FONT			cFontAscii5x10
#define DIS_GAS_NAME_NUM_SIZE			10
#define DIS_GAS_NAME_NUM_SIZE_X			5
#define DIS_GAS_NAME_NUM_SIZE_Y			10
// 气体名称最大长度
#define DIS_GAS_NAME_ASCII_LEN			16

// 仪器状态 检测，低报，高报
#define DIS_STAT_FONT				cFontAscii8x16
#define DIS_STAT_SIZE_X				8
#define DIS_STAT_SIZE_Y				16
#define DIS_STAT_SIZE				16

//// 显示左上角正确状态
//#define DIS_SYM_COR_FONT				cFontSymCor12x9
//#define DIS_SYM_COR_SIZE_X				12
//#define DIS_SYM_COR_SIZE_Y				9
//
//// 显示左上角错误状态
//#define DIS_SYM_WRON_FONT				cFontSymWron9x9
//#define DIS_SYM_WRON_SIZE_X				9
//#define DIS_SYM_WRON_SIZE_Y				9
//
//// 显示左上角报警状态
//#define DIS_SYM_ALAR_FONT				cFontAscii5x10
//#define DIS_SYM_ALAR_SIZE_X				5
//#define DIS_SYM_ALAR_SIZE_Y				10
//#define DIS_SYM_ALAR_SIZE				10
//
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

// 显示左上角电池状态
#define DIS_SYM_BAT_NONE				0
#define DIS_SYM_BAT_20					20
#define DIS_SYM_BAT_40					40
#define DIS_SYM_BAT_60					60
#define DIS_SYM_BAT_80					80
#define DIS_SYM_BAT_100					100
#define DIS_SYM_BAT_FULL				0xFF

// 显示风扇状态
#define DIS_SYM_FAN_NONE				0
#define DIS_SYM_FAN_1				1
#define DIS_SYM_FAN_2				2
#define DIS_SYM_FAN_ALL				3

#endif
