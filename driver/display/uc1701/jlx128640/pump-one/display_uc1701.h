/**
 * @file    display_uc1701.h
 * @brief   显示驱动
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-08-13 15:21:13 星期二 
 * @history (1).2013-08-13 15:21:13 星期二 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __DISPLAY_UC1701_H__
#define __DISPLAY_UC1701_H__

#include "uc1701.h"
#include "font_ascii.h"

/**
 * @brief   数字转换为字符串
 *
 * @param   lpData
 * @param   lNum
 * @param   lPoint
 */
static void NumTurn16(uint8_t *lpData, uint16_t lNum, uint8_t lPoint);

/**
 * @brief   显示大小一致的字符串
 *
 * @param   lpUnit
 * @param   lX
 * @param   lY
 * @param   lpFont
 * @param   lXSize
 * @param   lYSize
 * @param   lFSize
 */
void DisStr(uint8_t *lpStr, uint8_t lX, uint8_t lY, const uint8_t *lpFont, 
			uint8_t lXSize, uint8_t lYSize, uint8_t lFSize);

/**
 * @brief   显示特殊的字符串，英文是一个大小，数字是另一个大小
 *
 * @param   lpStr
 * @param   lX
 * @param   lY
 * @param   lpFont1
 * @param   lXSize1
 * @param   lYSize1
 * @param   lFSize1
 * @param   lpFont2
 * @param   lXSize2
 * @param   lYSize2
 * @param   lFSize2
 */
void DisStrEx(uint8_t *lpStr, uint8_t lX, uint8_t lY, 
				const uint8_t *lpFont1, uint8_t lXSize1, uint8_t lYSize1, 
				uint8_t lFSize1, const uint8_t *lpFont2, uint8_t lXSize2, 
				uint8_t lYSize2, uint8_t lFSize2);

/**
 * @brief   显示数字 数字区域都受影响
 *
 * @param   lNum
 * @param   lPoint
 * @param   lX
 * @param   lY
 * @param   lpFont
 * @param   lXSize
 * @param   lYSize
 * @param   lFSize
 */
void DisNum(uint16_t lNum, uint8_t lPoint, uint8_t lX, uint8_t lY, 
			const uint8_t *lpFont, uint8_t lXSize, uint8_t lYSize, 
			uint8_t lFSize);

/**
 * @brief   显示16x32的数字
 *
 * @param   lNum
 * @param   lPoint
 * @param   lX
 * @param   lY
 */
void DisNum16x32(uint16_t lNum, uint8_t lPoint, uint8_t lX, uint8_t lY);

/**
 * @brief   显示8x16的数字
 *
 * @param   lNum
 * @param   lPoint
 * @param   lX
 * @param   lY
 */
void DisNum8x16(uint16_t lNum, uint8_t lPoint, uint8_t lX, uint8_t lY);

/**
 * @brief   显示单位
 *
 * @param   lpUnit
 * @param   lX
 * @param   lY
 */
void DisUnit(uint8_t *lpUnit, uint8_t lX, uint8_t lY);

/**
 * @brief   显示气体名称
 *
 * @param   lpName
 * @param   lX
 * @param   lY
 */
void DisGasName(uint8_t *lpName, uint8_t lX, uint8_t lY);

/**
 * @brief   显示状态 检测，高报，低报
 *
 * @param   lpStat
 * @param   lX
 * @param   lY
 */
void DisStat(uint8_t *lpStat, uint8_t lX, uint8_t lY);

/**
 * @brief   显示正确状态
 *
 * @param   lX
 * @param   lY
 */
void DisSymCor(uint8_t lX, uint8_t lY);

/**
 * @brief   显示错误状态
 *
 * @param   lX
 * @param   lY
 */
void DisSymWron(uint8_t lX, uint8_t lY);

/**
 * @brief   显示报警状态
 *
 * @param   lpAlar
 * @param   lX
 * @param   lY
 */
void DisSymAlar(uint8_t *lpAlar, uint8_t lX, uint8_t lY);

/**
 * @brief   反显报警状态
 *
 * @param   lX
 * @param   lY
 */
void DisSymAlarRev(uint8_t lX, uint8_t lY);

/**
 * @brief   显示风扇
 *
 * @param   lX
 * @param   lY
 */
void DisSymFan(uint8_t lX, uint8_t lY);

/**
 * @brief   显示充电状态
 *
 * @param   lX
 * @param   lY
 */
void DisSymChar(uint8_t lX, uint8_t lY);

/**
 * @brief   显示大号充电状态
 *
 * @param   lX
 * @param   lY
 */
void DisSymCharLar(uint8_t lX, uint8_t lY);

/**
 * @brief   显示大号充满状态
 *
 * @param   lX
 * @param   lY
 */
void DisSymFull(uint8_t lX, uint8_t lY);

/**
 * @brief   显示电池状态
 *
 * @param   lBat
 * @param   lX
 * @param   lY
 */
void DisSymBat(uint8_t lBat, uint8_t lX, uint8_t lY);

/**
 * @brief   获得多个字符之间的等分间隔
 *
 * @param   lLenSum
 * @param   lLenChar
 * @param   lNum
 *
 * @return  
 */
uint8_t DisGapGet(uint8_t lLenSum, uint8_t lLenChar, uint8_t lNum);

/**
 * @brief   画点
 *
 * @param   lX
 * @param   lY
 */
void DisDotSet(uint8_t lX, uint8_t lY);

/**
 * @brief   清除点
 *
 * @param   lX
 * @param   lY
 */
void DisDotClr(uint8_t lX, uint8_t lY);

/**
 * @brief   画水平线
 *
 * @param   lX1
 * @param   lY
 * @param   lX2
 */
void DisHorLinSet(uint8_t lX1, uint8_t lY, uint8_t lX2);

/**
 * @brief   清除水平线
 *
 * @param   lX1
 * @param   lY
 * @param   lX2
 */
void DisHorLinClr(uint8_t lX1, uint8_t lY, uint8_t lX2);

/**
 * @brief   画斜线
 *
 * @param   lX
 * @param   lY
 * @param   lQuad
 * @param   lLen
 */
void DisDiagSet(uint8_t lX, uint8_t lY, uint8_t lQuad, uint8_t lLen);

/**
 * @brief   清除斜线
 *
 * @param   lX
 * @param   lY
 * @param   lQuad
 * @param   lLen
 */
void DisDiagClr(uint8_t lX, uint8_t lY, uint8_t lQuad, uint8_t lLen);

/**
 * @brief   画矩形
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
void DisRecSet(uint8_t lX1, uint8_t lY1, uint8_t lX2, uint8_t lY2);

/**
 * @brief   清除矩形
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
void DisRecClr(uint8_t lX1, uint8_t lY1, uint8_t lX2, uint8_t lY2);

/**
 * @brief   画矩形区域
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
void DisRecFillSet(uint8_t lX1, uint8_t lY1, uint8_t lX2, uint8_t lY2);

/**
 * @brief   清除矩形区域
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
void DisRecFillClr(uint8_t lX1, uint8_t lY1, uint8_t lX2, uint8_t lY2);

/**
 * @brief   反转矩形区域
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
void DisRecRev(uint8_t lX1, uint8_t lY1, uint8_t lX2, uint8_t lY2);

/**
 * @brief   普通画圆
 *
 * @param   lXc
 * @param   lYc
 * @param   lRad
 */
void DisCycSet(uint8_t lXc, uint8_t lYc, uint8_t lRad);

/**
 * @brief   普通清除圆
 *
 * @param   lXc
 * @param   lYc
 * @param   lRad
 */
void DisCycClr(uint8_t lXc, uint8_t lYc, uint8_t lRad);

/**
 * @brief   快速画圆
 *
 * @param   lXc
 * @param   lYc
 * @param   lRad
 */
void DisCycFastSet(uint8_t lXc, uint8_t lYc, uint8_t lRad);

/**
 * @brief   快速清除圆
 *
 * @param   lXc
 * @param   lYc
 * @param   lRad
 */
void DisCycFastClr(uint8_t lXc, uint8_t lYc, uint8_t lRad);

/**
 * @brief   画矩形带阴影外框
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
void DisRecFramSet(uint8_t lX1, uint8_t lY1, uint8_t lX2, uint8_t lY2);

/**
 * @brief   清除矩形带阴影外框
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
void DisRecFramClr(uint8_t lX1, uint8_t lY1, uint8_t lX2, uint8_t lY2);

/**
 * @brief   画折边矩形
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
void DisRecDiagSet(uint8_t lX1, uint8_t lY1, uint8_t lX2, uint8_t lY2);

/**
 * @brief   清除折边矩形
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
void DisRecDiagClr(uint8_t lX1, uint8_t lY1, uint8_t lX2, uint8_t lY2);

/**
 * @brief   画折边矩形带阴影
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
void DisRecDiagFramSet(uint8_t lX1, uint8_t lY1, uint8_t lX2, uint8_t lY2);

/**
 * @brief   清除折边矩形带阴影
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
void DisRecDiagFramClr(uint8_t lX1, uint8_t lY1, uint8_t lX2, uint8_t lY2);

/**
 * @brief   显示字符
 *
 * @param   lX
 * @param   lY
 * @param   lpBuf
 * @param   lXSize
 * @param   lYSize
 */
void DisCharSet(uint8_t lX, uint8_t lY, const uint8_t *lpBuf, 
				uint8_t lXSize, uint8_t lYSize);

/**
 * @brief   清除字符
 *
 * @param   lX
 * @param   lY
 * @param   lpBuf
 * @param   lXSize
 * @param   lYSize
 */
void DisCharClr(uint8_t lX, uint8_t lY, const uint8_t *lpBuf, 
				uint8_t lXSize, uint8_t lYSize);

/**
 * @brief   全部显示
 */
void DisAll(void);

/**
 * @brief   清除所有
 */
void DisClr(void);

/**
 * @brief   反显所有
 */
void DisRev(void);

/**
 * @brief   正常显示
 */
void DisMirUp(void);

/**
 * @brief   倒着显示
 */
void DisMirDown(void);

/**
 * @brief   显示初始化
 */
void DisInit(void);

/**
 * @brief   显示断电
 */
void DisPwrDown(void);

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

// 显示左上角正确状态
#define DIS_SYM_COR_FONT				cFontSymCor12x9
#define DIS_SYM_COR_SIZE_X				12
#define DIS_SYM_COR_SIZE_Y				9

// 显示左上角错误状态
#define DIS_SYM_WRON_FONT				cFontSymWron9x9
#define DIS_SYM_WRON_SIZE_X				9
#define DIS_SYM_WRON_SIZE_Y				9

// 显示左上角报警状态
#define DIS_SYM_ALAR_FONT				cFontAscii5x10
#define DIS_SYM_ALAR_SIZE_X				5
#define DIS_SYM_ALAR_SIZE_Y				10
#define DIS_SYM_ALAR_SIZE				10

// 显示左上角风扇状态
#define DIS_SYM_FAN_FONT				cFontSymFan9x9
#define DIS_SYM_FAN_SIZE_X				9
#define DIS_SYM_FAN_SIZE_Y				9

// 显示左上角充电状态
#define DIS_SYM_CHAR_FONT				cFontSymChar4x8
#define DIS_SYM_CHAR_SIZE_X				4
#define DIS_SYM_CHAR_SIZE_Y				8

// 显示大号充电状态
#define DIS_SYM_CHAR_LAR_FONT				cFontSymChar33x16
#define DIS_SYM_CHAR_LAR_SIZE_X				33
#define DIS_SYM_CHAR_LAR_SIZE_Y				16

// 显示大号充满状态
#define DIS_SYM_FULL_FONT				cFontSymFul18x23
#define DIS_SYM_FULL_SIZE_X				18
#define DIS_SYM_FULL_SIZE_Y				23

// 显示左上角电池状态
#define DIS_SYM_BAT_FONT				cFontSymBat16x8
#define DIS_SYM_BAT_SIZE_X				16
#define DIS_SYM_BAT_SIZE_Y				8
#define DIS_SYM_BAT_SIZE				16
#define DIS_SYM_BAT_NONE				0
#define DIS_SYM_BAT_20					20
#define DIS_SYM_BAT_40					40
#define DIS_SYM_BAT_60					60
#define DIS_SYM_BAT_80					80
#define DIS_SYM_BAT_100					100
#define DIS_SYM_BAT_FULL				0xFF

// 对齐
#define DIS_JUSTIFY_LEFT			0
#define DIS_JUSTIFY_RIGHT			1

#define DIS_DOT_SET				UC1701_DRAW_DOT_SET
#define DIS_DOT_CLR				UC1701_DRAW_DOT_CLR

#define DIS_X_START					0
#define DIS_Y_START					0
#define DIS_X_END					127
#define DIS_Y_END					63

#endif
