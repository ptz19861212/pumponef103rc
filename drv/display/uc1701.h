/**
 * @file    uc1701.h
 * @brief   UC1701驱动
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-08-08 14:22:23 星期四 
 * @history (1).2013-08-08 14:22:23 星期四 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#ifndef __UC1701_H__
#define __UC1701_H__

#include <stdint.h>
#include "my_display.h"

/**
 * @brief    画点
 *
 * @param   lX
 * @param   lY
 */
void UC1701_DrawDotSet(S_Lcd_Point* lpPoint);

/**
 * @brief   点清除
 *
 * @param   lX
 * @param   lY
 */
void UC1701_DrawDotClr(S_Lcd_Point* lpPoint);

/**
 * @brief   画水平线
 *
 * @param   lX1
 * @param   lY
 * @param   lX2
 */
void UC1701_DrawHorLinSet(S_Lcd_Line_Horizon* lpLin);

/**
 * @brief   清除水平线
 *
 * @param   lX1
 * @param   lY
 * @param   lX2
 */
void UC1701_DrawHorLinClr(S_Lcd_Line_Horizon* lpLin);

/**
 * @brief   画水平虚线
 *
 * @param   lX1
 * @param   lY
 * @param   lX2
 */
void UC1701_DrawHorDotLinSet(S_Lcd_Line_Horizon* lpLin);

/**
 * @brief   清除水平虚线
 *
 * @param   lX1
 * @param   lY
 * @param   lX2
 */
void UC1701_DrawHorDotLinClr(S_Lcd_Line_Horizon* lpLin);

/**
 * @brief   画垂直线
 *
 * @param   lX1
 * @param   lY1
 * @param   lY2
 */
void UC1701_DrawVerLinSet(S_Lcd_Line_Vertical* lpLin);

/**
 * @brief   清除垂直线
 *
 * @param   lX1
 * @param   lY1
 * @param   lY2
 */
void UC1701_DrawVerLinClr(S_Lcd_Line_Vertical* lpLin);

/**
 * @brief   画垂直虚线
 *
 * @param   lX1
 * @param   lY1
 * @param   lY2
 */
void UC1701_DrawVerDotLinSet(S_Lcd_Line_Vertical* lpLin);

/**
 * @brief   清除垂直虚线
 *
 * @param   lX1
 * @param   lY1
 * @param   lY2
 */
void UC1701_DrawVerDotLinClr(S_Lcd_Line_Vertical* lpLin);

/**
 * @brief   画45度斜线
 *
 * @param   lX
 * @param   lY
 * @param   lQuad 第几象限
 * @param   lLen
 */
void UC1701_DrawDiagSet(S_Lcd_Line_Diagonal* lLin);

/**
 * @brief   清除45度线
 *
 * @param   lX
 * @param   lY
 * @param   lQuad
 * @param   lLen
 */
void UC1701_DrawDiagClr(S_Lcd_Line_Diagonal* lLin);

/**
 * @brief   画矩形
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
void UC1701_DrawRecSet(S_Lcd_Area_Rectangle* lRec);

/**
 * @brief   清除矩形
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
void UC1701_DrawRecClr(S_Lcd_Area_Rectangle* lRec);

/**
 * @brief   填充矩形
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
void UC1701_FillRecSet(S_Lcd_Area_Rectangle* lpRec);

/**
 * @brief   清除矩形
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
void UC1701_FillRecClr(S_Lcd_Area_Rectangle* lpRec);

/**
 * @brief   反转矩形
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
void UC1701_RevRec(S_Lcd_Area_Rectangle* lpRec);

/**
 * @brief   画滚动条
 *
 * @param   lLen 滚动条滑块的长度
 * @param   lEx 滚动条一边比线多出来的宽度
 * @param   lX1 滚动条长线的起始X
 * @param   lY1 滚动条长线的起始y
 * @param   lY2 滚动条长线的结束y
 * @param   lY3 滚动条滑块的起始y
 */
//void UC1701_ScrollBar(uint8_t lLen, uint8_t lEx, uint8_t lX1, uint8_t lY1,
//							uint8_t lY2, uint8_t lY3);
void UC1701_ScrollBar(S_Lcd_Bar_Scroll* lpBar);

/**
 * @brief   普通画圆法
 *
 * @param   lX
 * @param   lY
 * @param   lRad
 */
void UC1701_DrawCycSet(S_Lcd_Area_Cycle* lCyc);

/**
 * @brief   普通清除圆形法
 *
 * @param   lX
 * @param   lY
 * @param   lRad
 */
void UC1701_DrawCycClr(S_Lcd_Area_Cycle* lCyc);

/**
 * @brief   快速画圆法
 *
 * @param   lXc
 * @param   lYc
 * @param   lRad
 */
void UC1701_DrawCycFastSet(S_Lcd_Area_Cycle* lCyc);

/**
 * @brief   快速清除圆法
 *
 * @param   lXc
 * @param   lYc
 * @param   lRad
 */
void UC1701_DrawCycFastClr(S_Lcd_Area_Cycle* lCyc);

/**
 * @brief   画矩形带阴影外框
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
void UC1701_DrawRecFramSet(S_Lcd_Area_RectangleShade* lpFrame);

/**
 * @brief   清除矩形阴影
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
void UC1701_DrawRecFramClr(S_Lcd_Area_RectangleShade* lpFrame);

/**
 * @brief   画折边矩形
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
void UC1701_DrawRecDiagSet(uint8_t lX1, uint8_t lY1, uint8_t lX2, 
							uint8_t lY2);

/**
 * @brief   清除折边矩形
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
void UC1701_DrawRecDiagClr(uint8_t lX1, uint8_t lY1, uint8_t lX2, 
							uint8_t lY2);

/**
 * @brief   画折边矩形带阴影
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
void UC1701_DrawRecDiagFramSet(uint8_t lX1, uint8_t lY1, uint8_t lX2, 
								uint8_t lY2);

/**
 * @brief   清除折边矩形阴影
 *
 * @param   lX1
 * @param   lY1
 * @param   lX2
 * @param   lY2
 */
void UC1701_DrawRecDiagFramClr(uint8_t lX1, uint8_t lY1, uint8_t lX2, 
								uint8_t lY2);

/**
 * @brief   显示字符
 *
 * @param   lX
 * @param   lY
 * @param   lpBuffer
 * @param   lXSize
 * @param   lYSize
 */
void UC1701_CharSet(S_Lcd_Char* lpChar);

/**
 * @brief   清除字符
 *
 * @param   lX
 * @param   lY
 * @param   lpBuffer
 * @param   lXSize
 * @param   lYSize
 */
void UC1701_CharClr(S_Lcd_Char* lpChar);

/**
 * @brief   uc1701 显示所有，注意没有改变DRAM数值
 */
void UC1701_DisAll(void);

/**
 * @brief   uc1701 反显当前内容
 */
void UC1701_DisRev(void);

/**
 * @brief   uc1701 清除所有内容
 */
void UC1701_DisClr(void);

/**
 * @brief   uc1701 软件坐标到硬件坐标的转换
 *
 * @param   lX
 */
inline void UC1701_CorCvt_X(my_lcd_t* lX);

/**
 * @brief   uc1701 软件坐标到硬件坐标的转换
 *
 * @param   lY
 */
inline void UC1701_CorCvt_Y(my_lcd_t* lY);


/**
 * @brief   uc1701 软件坐标到硬件坐标的转换
 *
 * @param   lpPoint
 */
inline void UC1701_CorCvt(S_Lcd_Point* lpPoint);


/**
 * @brief   uc1701 正常持有的显示方式
 */
void UC1701_MirUp(void);

/**
 * @brief   uc1701 倒着持有的显示方式
 */
void UC1701_MirDown(void);

/**
 * @brief   uc1701 初始化
 */
void UC1701_Init(void);


/**
 * @brief   uc1701 打开背光
 */
inline void UC1701_BgOn(void);


/**
 * @brief   uc1701 关闭背光
 */
inline void UC1701_BgOff(void);


/**
 * @brief   uc1701 进入休眠模式
 */
void UC1701_SleepIN(void);


/**
 * @brief   uc1701 退出休眠模式
 */
void UC1701_SleepOut(void);



/**
 * @brief   uc1701 断电
 */
void UC1701_PwrDown(void);

#endif
