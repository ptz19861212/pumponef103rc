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
#include "my_display.h"


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
//void DisStr(const uint8_t *lpStr, uint8_t lX, uint8_t lY, const uint8_t *lpFont,
//			uint8_t lXSize, uint8_t lYSize, uint8_t lFSize);
void DisStr(S_Lcd_String* lpStr);


/**
 * @brief   显示大小一致的字符串，靠右显示
 *
 * @param   lpStr
 */
void DisStrRight(S_Lcd_String_Right* lpStr);


/**
 * @brief   显示大小一致的字符串，居中显示
 *
 * @param   lpStr
 */
void DisStrMiddle(S_Lcd_String_Middle* lpStr);


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
//void DisStrEx(const uint8_t *lpStr, uint8_t lX, uint8_t lY,
//				const uint8_t *lpFont1, uint8_t lXSize1, uint8_t lYSize1,
//				uint8_t lFSize1, const uint8_t *lpFont2, uint8_t lXSize2,
//				uint8_t lYSize2, uint8_t lFSize2);
void DisStrDual(S_Lcd_String_Dual* lStr);

/**
 * @brief   显示数字 数字区域都受影响，左对齐
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
//void DisNum(uint16_t lNum, uint8_t lPoint, uint8_t lX, uint8_t lY,
//			const uint8_t *lpFont, uint8_t lXSize, uint8_t lYSize,
//			uint8_t lFSize);
void DisNum(S_Lcd_Value_U16* lpValue);


/**
 * @brief   显示数字 数字区域都受影响，右对齐
 *
 * @param   lNum
 * @param   lPoint
 * @param   lX
 * @param   lY
 * @param   lLen 右对齐的位数
 * @param   lpFont
 * @param   lXSize
 * @param   lYSize
 * @param   lFSize
 */
//void DisNumRight(uint16_t lNum, uint8_t lPoint, uint8_t lX, uint8_t lY,
//					uint8_t lLen, const uint8_t *lpFont,
//					uint8_t lXSize, uint8_t lYSize, uint8_t lFSize);
void DisNumRight(S_Lcd_Value_Right_U16* lpValue);


/**
 * @brief   获得多个字符之间的等分间隔
 *
 * @param   lLenSum
 * @param   lLenChar
 * @param   lNum
 *
 * @return  
 */
//uint8_t DisGapGet(uint8_t lLenSum, uint8_t lLenChar, uint8_t lNum);

/**
 * @brief   画点
 *
 * @param   lX
 * @param   lY
 */
//void DisDotSet(uint8_t lX, uint8_t lY);
void DisDotSet(S_Lcd_Point* lpPoint);

/**
 * @brief   清除点
 *
 * @param   lX
 * @param   lY
 */
//void DisDotClr(uint8_t lX, uint8_t lY);
void DisDotClr(S_Lcd_Point* lpPoint);

/**
 * @brief   画水平线
 *
 * @param   lX1
 * @param   lY
 * @param   lX2
 */
//void DisHorLinSet(uint8_t lX1, uint8_t lY, uint8_t lX2);
void DisHorLinSet(S_Lcd_Line_Horizon* lpHor);

/**
 * @brief   清除水平线
 *
 * @param   lX1
 * @param   lY
 * @param   lX2
 */
//void DisHorLinClr(uint8_t lX1, uint8_t lY, uint8_t lX2);
void DisHorLinClr(S_Lcd_Line_Horizon* lpHor);

/**
 * @brief   画水平虚线
 *
 * @param   lX1
 * @param   lY
 * @param   lX2
 */
//void DisHorDotLinSet(uint8_t lX1, uint8_t lY, uint8_t lX2);
void DisHorDotLinSet(S_Lcd_Line_Horizon* lpHor);

/**
 * @brief   清除水平虚线
 *
 * @param   lX1
 * @param   lY
 * @param   lX2
 */
//void DisHorDotLinClr(uint8_t lX1, uint8_t lY, uint8_t lX2);
void DisHorDotLinClr(S_Lcd_Line_Horizon* lpHor);

/**
 * @brief   画垂直线
 *
 * @param   lX1
 * @param   lY
 * @param   lX2
 */
//void DisVerLinSet(uint8_t lX1, uint8_t lY, uint8_t lX2);
void DisVerLinSet(S_Lcd_Line_Vertical* lpVer);

/**
 * @brief   清除垂直线
 *
 * @param   lX1
 * @param   lY
 * @param   lX2
 */
//void DisVerLinClr(uint8_t lX1, uint8_t lY, uint8_t lX2);
void DisVerLinClr(S_Lcd_Line_Vertical* lpVer);

/**
 * @brief   画垂直虚线
 *
 * @param   lX1
 * @param   lY
 * @param   lX2
 */
//void DisVerDotLinSet(uint8_t lX1, uint8_t lY, uint8_t lX2);
void DisVerDotLinSet(S_Lcd_Line_Vertical* lpVer);

/**
 * @brief   清除垂直虚线
 *
 * @param   lX1
 * @param   lY
 * @param   lX2
 */
//void DisVerDotLinClr(uint8_t lX1, uint8_t lY, uint8_t lX2);
void DisVerDotLinClr(S_Lcd_Line_Vertical* lpVer);

/**
 * @brief   画斜线
 *
 * @param   lX
 * @param   lY
 * @param   lQuad
 * @param   lLen
 */
//void DisDiagSet(uint8_t lX, uint8_t lY, uint8_t lQuad, uint8_t lLen);
void DisDiagSet(S_Lcd_Line_Diagonal* lpLin);

/**
 * @brief   清除斜线
 *
 * @param   lX
 * @param   lY
 * @param   lQuad
 * @param   lLen
 */
//void DisDiagClr(uint8_t lX, uint8_t lY, uint8_t lQuad, uint8_t lLen);
void DisDiagClr(S_Lcd_Line_Diagonal* lpLin);

/**
 * @brief   画矩形
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
//void DisRecSet(uint8_t lX1, uint8_t lY1, uint8_t lX2, uint8_t lY2);
void DisRecSet(S_Lcd_Area_Rectangle* lpRec);

/**
 * @brief   清除矩形
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
//void DisRecClr(uint8_t lX1, uint8_t lY1, uint8_t lX2, uint8_t lY2);
void DisRecClr(S_Lcd_Area_Rectangle* lpRec);

/**
 * @brief   画矩形区域
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
//void DisRecFillSet(uint8_t lX1, uint8_t lY1, uint8_t lX2, uint8_t lY2);
void DisRecFillSet(S_Lcd_Area_Rectangle* lpRec);

/**
 * @brief   清除矩形区域
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
//void DisRecFillClr(uint8_t lX1, uint8_t lY1, uint8_t lX2, uint8_t lY2);
void DisRecFillClr(S_Lcd_Area_Rectangle* lpRec);

/**
 * @brief   反转矩形区域
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
//void DisRecRev(uint8_t lX1, uint8_t lY1, uint8_t lX2, uint8_t lY2);
void DisRecRev(S_Lcd_Area_Rectangle* lpRec);

/**
 * @brief   画滚动条
 *
 * @param   lLen 滚动条滑块的长度
 * @param   lEx 滚动条一边比线多出来的宽度
 * @param   lXLin 滚动条长线的起始X
 * @param   lYScr 滚动条滑块的起始y
 */
//void DisScrollBar(uint8_t lLen, uint8_t lEx, uint8_t lXLin, uint8_t lYScr);
void DisScrollBar(S_Lcd_Bar_Scroll* lpBar);

/**
 * @brief   普通画圆
 *
 * @param   lXc
 * @param   lYc
 * @param   lRad
 */
//void DisCycSet(uint8_t lXc, uint8_t lYc, uint8_t lRad);
void DisCycSet(S_Lcd_Area_Cycle* lpCyc);

/**
 * @brief   普通清除圆
 *
 * @param   lXc
 * @param   lYc
 * @param   lRad
 */
//void DisCycClr(uint8_t lXc, uint8_t lYc, uint8_t lRad);
void DisCycClr(S_Lcd_Area_Cycle* lpCyc);

/**
 * @brief   快速画圆
 *
 * @param   lXc
 * @param   lYc
 * @param   lRad
 */
//void DisCycFastSet(uint8_t lXc, uint8_t lYc, uint8_t lRad);
void DisCycFastSet(S_Lcd_Area_Cycle* lpCyc);

/**
 * @brief   快速清除圆
 *
 * @param   lXc
 * @param   lYc
 * @param   lRad
 */
//void DisCycFastClr(uint8_t lXc, uint8_t lYc, uint8_t lRad);
void DisCycFastClr(S_Lcd_Area_Cycle* lpCyc);

/**
 * @brief   画矩形带阴影外框
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
void DisRecFramSet(S_Lcd_Area_RectangleShade* lpRec);

/**
 * @brief   清除矩形带阴影外框
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
void DisRecFramClr(S_Lcd_Area_RectangleShade* lpRec);

/**
 * @brief   画折边矩形
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
//void DisRecDiagSet(uint8_t lX1, uint8_t lY1, uint8_t lX2, uint8_t lY2);

/**
 * @brief   清除折边矩形
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
//void DisRecDiagClr(uint8_t lX1, uint8_t lY1, uint8_t lX2, uint8_t lY2);

/**
 * @brief   画折边矩形带阴影
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
//void DisRecDiagFramSet(uint8_t lX1, uint8_t lY1, uint8_t lX2, uint8_t lY2);

/**
 * @brief   清除折边矩形带阴影
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
//void DisRecDiagFramClr(uint8_t lX1, uint8_t lY1, uint8_t lX2, uint8_t lY2);

/**
 * @brief   显示字符
 *
 * @param   lX
 * @param   lY
 * @param   lpBuf
 * @param   lXSize
 * @param   lYSize
 */
void DisCharSet(S_Lcd_Char* lpChar);

/**
 * @brief   清除字符
 *
 * @param   lX
 * @param   lY
 * @param   lpBuf
 * @param   lXSize
 * @param   lYSize
 */
void DisCharClr(S_Lcd_Char* lpChar);

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
 * @brief   打开背光
 */
void DisBgOn(void);


/**
 * @brief   关闭背光
 */
void DisBgOff(void);


/**
 * @brief   进入休眠模式
 */
void DisSleepIN(void);


/**
 * @brief   退出休眠模式
 */
void DisSleepOut(void);


/**
 * @brief   显示断电
 */
void DisPwrDown(void);


extern const S_Lcd_Screen gLcdScreen;










#endif
